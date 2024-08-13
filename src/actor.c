#include "actor.h"

Vector2 update_control(void)
{
	Vector2 result;

	result.x = (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)); //A is +x, D is -x
	result.y = (float)(IsKeyDown(KEY_S) - IsKeyDown(KEY_W)); //S is +z, W is -z

	if(Vector2Length(result) > 1.0f)
		result = Vector2Normalize(result);

	return result;
}

void draw_actor(Actor a, Camera c)
{
	Rectangle rect = { 0 };
	Vector3 swizzle = (Vector3){ a.pos.x, 0.0f, a.pos.y }; //vim gets angry when I cast Vector3s inside a function call
	
	rect.width = a.sprite.pixel_offset[0];
	rect.height = a.sprite.pixel_offset[1];

	rect.x = a.sprite.pixel_offset[0] * a.animation; //animation determines offset
	//rect.y = a.sprite.pixel_offset[1] * a.frame;

	DrawBillboardRec(c, a.sprite.tex, rect, swizzle, a.sprite.size, WHITE);
	return;
}

void control_actor(Actor* a)
{
	/* gutted quake movement??? */
	float delta_time = GetFrameTime();
	Vector2 intended_dir = update_control();
	float accel_speed = 0;
	float deaccel_speed = 0;
	float target_speed = Vector2Length(intended_dir) * MAX_SPEED;//ranges from [0, MAX_SPEED]
	float current_speed = Vector2DotProduct(a->vel, intended_dir);//ranges from [-vel,vel]
	float move_speed = Vector2Length(a->vel);

	float add_speed = target_speed - current_speed;

	accel_speed = MAX_ACCEL * delta_time * target_speed;
	if(accel_speed > add_speed)
		accel_speed = add_speed;

	if(move_speed > MIN_SPEED) { 
	
		deaccel_speed = move_speed - delta_time * move_speed * FRICTION;
	
		if(deaccel_speed < 0)
			deaccel_speed = 0;
		deaccel_speed /= move_speed;

	} else if(!target_speed) { //check for no input
		a->vel = Vector2Zero();
		return;//safe to stop character
	}

	if(target_speed)
		a->animation = look_at(Vector2Zero(), intended_dir);

	a->vel = Vector2Scale(a->vel, deaccel_speed); 
	a->vel = Vector2Add(Vector2Scale(intended_dir, accel_speed), a->vel);
	a->pos = Vector2Add(Vector2Scale(a->vel, delta_time), a->pos);

	return;
}

Animation look_at(Vector2 origin, Vector2 target)
{
	Animation result = 0;

	Vector2 v = Vector2Subtract(target, origin);
	
	if(!(v.x || v.y))
		return FACE_FORWARD;

	v = Vector2Normalize(v);

	if(v.y < -0.70710678f)
		result = FACE_BACKWARD;
	if(v.x > 0.5f)
		result += TURN_RIGHT;
	if(v.x < -0.5f)
		result += TURN_LEFT;

	return result;
}

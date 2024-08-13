#include "raylib.h"
#include "raymath.h"
#include "actor.h"

	/////////////////////
	// RAYLIB TEMPLATE //
	/////////////////////

int main(void)
{
	//TODO write a main function to use actor.c library	
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "raylib - bsp parse");
	/* LOAD THINGS */

	Actor player = { 0 };
	// MANUALLY LOADING SPRITE DATA
	player.sprite.pixel_offset[0] = 16;
	player.sprite.pixel_offset[1] = 16;
	player.sprite.size = (Vector2){ 2.0f, 2.0f };
	player.sprite.num_sprites = 6;
	player.sprite.tex = LoadTexture("assets/sprites/dumbsheet.png");
	
	Camera camera = { 0 };
	camera.position = (Vector3){ 0.0f, 4.0f, 5.0f };    // Camera position
	camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };      // Camera looking at point
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	
	SetTargetFPS(60);

	/////////////////////
	// GAME LOOP BEGIN //
	/////////////////////
	
	while(!WindowShouldClose()) {

		control_actor(&player);

		BeginDrawing();
			/* DRAW HERE */
			ClearBackground(RAYWHITE);

			BeginMode3D(camera);
				
				DrawGrid(10, 1);
				draw_actor(player, camera);	

			EndMode3D();

		EndDrawing();

	}

	UnloadTexture(player.sprite.tex);
	return 0;
}

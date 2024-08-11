# maxmakefile 1.3

BUILD_MODE ?= RELEASE

# Compiler Settings
CC	= gcc
LFLAGS	= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
DFLAGS	= -MP -MD
CFLAGS	= $(LFLAGS) -Wall -Wextra -Werror -pedantic $(DFLAGS)

# Directories
SRCDIR	= src
OBJDIR	= obj #i have decided to not use this because i don't understand how to put *.d files in the src folder like intended
BINDIR	= build
GDBDIR	= debug

ifeq ($(BUILD_MODE), RELEASE)
	CFLAGS += -O2
else
	CFLAGS += -g -O0
endif

# Files
# for OBJS, first arg of patsubst i'm purposely not using $(SRCDIR)/%.c to see if it breaks it
SRCS	= $(wildcard $(SRCDIR)/*.c)
OBJS	= $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SRCS))
DEPS	= $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.d, $(SRCS))
BIN	= bin

.phony: clean all

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ $(LFLAGS) -o $(BINDIR)/$@

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -rf $(BIN) $(OBJS) $(DEPS)

# include our dependencies
-include $(DEPS)

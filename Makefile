# Detect OS for platform-specific settings
UNAME_S := $(shell uname -s)
RPATH_GSDK_REL = ../gsdk/build/lib
ifeq ($(UNAME_S),Darwin)
	SHARED_EXT = dylib
	RPATH_FLAGS = -Wl,-rpath,@loader_path -Wl,-rpath,@loader_path/$(RPATH_GSDK_REL)
else
	SHARED_EXT = so
	RPATH_FLAGS = -Wl,-rpath,'$$ORIGIN' -Wl,-rpath,'$$ORIGIN/$(RPATH_GSDK_REL)'
endif

# SDL3
SDL_CFLAGS := $(shell pkg-config --cflags sdl3 sdl3-ttf)#sdl3-image sdl3-ttf)
SDL_LIBS := $(shell pkg-config --libs sdl3 sdl3-ttf)#sdl3-image sdl3-ttf)

# Compiler and flags
CC = clang
CFLAGS = -g -Wall -Wextra -Iinclude -Igsdk/include -Igsdk/include/core -Igsdk/include/data -Igsdk/include/performance -Igsdk/include/reflection -std=c23 $(SDL_CFLAGS) 

# Directories
BUILD_DIR = build
GSDK_LIB_DIR = gsdk/build/lib
UI_SRC_DIR = src/*

# Sources / objects
UI_SRC = $(wildcard $(UI_SRC_DIR)/*.c)
UI_OBJ = $(patsubst $(UI_SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(UI_SRC))

# Library / executables (in build/)
UI_LIB_BASENAME = ui
UI_LIB = $(BUILD_DIR)/lib$(UI_LIB_BASENAME).$(SHARED_EXT)
UI = $(BUILD_DIR)/ui

# Locate gsdk shared libraries (full paths)
GSDK_LIBS = $(wildcard $(GSDK_LIB_DIR)/*.$(SHARED_EXT))

.PHONY: all clean info run

# Default target
all: $(UI_LIB) $(UI)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Object files
$(BUILD_DIR)/%.o: $(UI_SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# Shared library
$(UI_LIB): $(UI_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $^ $(GSDK_LIBS) $(SDL_LIBS) 

# Executables
$(UI): main.c $(UI_LIB) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(UI_LIB) $(GSDK_LIBS) $(SDL_LIBS) $(RPATH_FLAGS)

# Info
info:
	@echo "ui sources      : $(UI_SRC)"
	@echo "ui objects      : $(UI_OBJ)"
	@echo "ui library      : $(UI_LIB)"
	@echo "gsdk libraries  : $(GSDK_LIBS)"
	@echo "ui              : $(UI)"

# Clean
clean:
	rm -rf $(BUILD_DIR)

run: build
	@./build/ui

.PHONY: all clean info run
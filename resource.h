#pragma once
#define FRAMERATE 60.0
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
#define SPEED 8.0
#define ACCELERATION 30.0

#include "SDL.h"

enum State {
    IDLE,
    WALK,
};
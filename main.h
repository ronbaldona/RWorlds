#pragma once
#include <iostream>

#include "Window.h"
#include "PrintDebug.h"

static constexpr unsigned int STND_WIDTH = 800;
static constexpr unsigned int STND_HEIGHT = 600;
static long settings = 0x0;

// USER SETTINGS
static constexpr long PRINT_HELP_BIT = 0x1;
static constexpr long OBJ_LOADED_BIT = 0x2;
static constexpr long DEBUG_MODE_BIT = 0x4;

// Other constants
static constexpr int MAX_NUM_USAGE = 6;
static const std::string TEST_OBJ = "Models/happy-buddha.fbx";
//"Models/happy-buddha.fbx";

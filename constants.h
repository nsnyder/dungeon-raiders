// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "AI";
const char GAME_TITLE[] = "AI";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
const int SPRITE_SHEET_WIDTH = 240;
const float SPRITE_SHEET_SCALE = .15;

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const RECT  COLLISION_RECTANGLE = {-30,-16,30,16};
const RECT  COLLISION_BOX_PADDLE = {-45,-10,45,10};
const RECT COLLISION_BOX_PUCK = {-32, -32, 32, 32};
const float   COLLISION_RADIUS = 29;

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR PADDLE_LEFT    = VK_LEFT;     // left arrow
const UCHAR PADDLE_RIGHT   = VK_RIGHT;    // right arrow
const UCHAR ENTER_KEY    = VK_RETURN; 
const UCHAR PADDLE_UP = VK_UP;
const UCHAR PADDLE_DOWN = VK_DOWN;

//

// Assets
const std::string images[] = { 
	"img/swordSheet.png",
	"img/figure.bmp",
	"img/wall.bmp",
	"img/sprite_sheet.png",
	"img/figure.bmp",
	"img/health.bmp",
	"img/background1.png"
};
const int nTextures = 7;

const int loadImages[] = {
	2, 1, 6
};
const int nImages = 3;


// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\stick_wave_bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\stick_sound_bank.xsb";

// audio cues
const char SWORD_HIT[] = "sword_hit";
const char PUNCH_HIT[] = "punch_hit";
const char SWORD_MISS[] = "sword_miss";
const char PUNCH_MISS[] = "punch_miss";
const char BACKGROUND[]   = "background";
const char DEATH[] = "death";

// Pattern Step Action
enum PATTERN_STEP_ACTION {NONE, UP, DOWN, LEFT, RIGHT, TRACK, EVADE, UPLEFT};

// Game states
enum GameStates {SPLASH_SCREEN, MENU, CHARACTER_SELECT, INSTRUCTIONS_SINGLE, INSTRUCTIONS_MULTI, LEVEL1, WIN1, WIN2 };

// Menu Constants
const int MENU_OFFSET = 125;
enum menuStates { GAME_MODE = 1, SFX, CHEATS, FEELING_LUCKY,
					MODE_1_PLAYER = 11, MODE_2_PLAYER,
					SFX_ON = 21, SFX_OFF,
					CHEATS_ON = 31, CHEATS_OFF
};

#endif

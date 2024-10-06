#pragma once

#include <unistd.h>
#include <string>

#ifdef _WIN32
#include <conio.h>


#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
#include <termios.h>
#endif

enum GAME_MODE
{
	BEGINNER = 1,
	INTERMEDIATE,
	EXPERT,
	CUSTOM
};

extern GAME_MODE gameMode;

enum GAME_STATE
{
	VICTORY,
	DEFEAT,
	RUNNING
};

extern GAME_STATE gameState;

extern bool QUICK_CLEAR;

enum POSOF_CELL
{
	CENTRE,
	EDGE,
	CORNER
};

enum DIR_X
{
	NULL_DIR_X = 0,
	LEFT = -1,
	RIGHT = 1
};

enum DIR_Y
{
	NULL_DIR_Y = 0,
	UP = -1,
	DOWN = 1
};

const std::string endl = "\n";
using KEY = char;

enum KEYS
{
	K_ESC = '\e',
	K_BRAC_OPEN = '[',
	K_UP = 'A',
	K_DOWN = 'B',
	K_LEFT = 'D',
	K_RIGHT = 'C',
	K_F = 'f',		
	K_S = 's',		
	K_ENTER = '\n', 
	K_SPACE = ' '   
};

enum VI_KEYS
{
	K_K = 75,
	K_J = 74,
	K_H = 72,
	K_L = 76,
	K_k = 107,
	K_j = 106,
	K_h = 104,
	K_l = 108
};

#if defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
extern char getch();
#endif

KEY getKey();
#pragma once

#include <string>



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

/**
 * 获取一个输入的键位
 * @return 输入的键位
 */
extern KEY getKey();

#if defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
extern char getch();
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


#elifdef _WIN32
enum KEYS
{
	K_UP = (char)72,
	K_DOWN = (char)80,
	K_LEFT = (char)75,
	K_RIGHT = (char)77,
	K_F = 'f',
	K_S = 's',
	K_ENTER = '\r',
	K_SPACE = ' '
};
#endif


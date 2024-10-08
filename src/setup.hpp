#pragma once

#include <string>

/// 键盘控制以及操作信息类
///
///

/// 游戏模式
enum GAME_MODE
{
	BEGINNER = 1,
	INTERMEDIATE,
	EXPERT,
	CUSTOM
};

/// 当前游戏模式（全局变量）
extern GAME_MODE gameMode;

/// 游戏状态枚举（胜利，失败，进行中），用于显示状态
enum GAME_STATE
{
	VICTORY,
	DEFEAT,
	RUNNING
};

/// 当前游戏状态（全局变量）
extern GAME_STATE gameState;

/// 是否快速清除模式（全局变量）
extern bool QUICK_CLEAR;

/// 单元格格式
enum POSOF_CELL
{
	CENTRE,
	EDGE,
	CORNER
};

/// x轴下移动方位
enum DIR_X
{
	NULL_DIR_X = 0,
	LEFT = -1,
	RIGHT = 1
};

/// y轴下移动方位
enum DIR_Y
{
	NULL_DIR_Y = 0,
	UP = -1,
	DOWN = 1
};

const std::string endl = "\n";
using KEY = char;


/// VI键位枚举
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

/// UNIX下的键位枚举，以及getch的定义（unix下没有函数，自己用串口通讯写一个）
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

/// Windows下的键位定义
#elif defined(_WIN32)
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


#pragma once
///
/// 屏幕显示相关，用于显示信息
///

/// 清屏函数
/// win下使用vt100实现
/// mac/unix下使用clear实现
///
extern void clearScreen();

/// 最大化窗口
/// 模拟F11，非Windows下不生效
extern void maximizeConsole();

/// 显示banner图
extern void displayBanner();

/// 显示标志控制位
extern void displayFlagCounter();

/// 显示控制指南
extern void displayControls();

/// 显示输赢状态
extern void displayVictoryOrDefeat();

/// 设定游戏难度（游戏主菜单）
extern void setGameMode();

/// 显示是否快速清除菜单
extern void getQuickClearSettings();

/// ----------------------------------vt100操作控制符---------------------------
extern void saveLocation();

extern void backLocation();

extern void clearSiteToEnd();

extern void hideCursor();

#include <iostream>


#include "field.hpp"
#include "buffer.hpp"
#include "setup.hpp"
#include "colour.hpp"
#include "display.hpp"

int main()
{
    // Windows下需要调整UTF8字符集，保证显示正常
#ifdef _WIN32
    system("chcp 65001");
#endif
    // 最大化窗口
    maximizeConsole();
    // 隐藏指针
    hideCursor();
    // 清屏
    clearScreen();

    // 显示游戏难度菜单并等待选择
    setGameMode();

    // 显示是否快速清除菜单等待选择
    getQuickClearSettings();

    // 定义游戏棋盘，开始游戏
    Field field;
    // 显示Banner
    displayBanner();
    // 保存位置，无需重复显示，减少闪烁
    saveLocation();
    while (true)
    {
        // 恢复位置进行清除
        backLocation();
        clearSiteToEnd();

        // 画出新的棋盘
        field.drawField();
        displayFlagCounter();

        // 如果游戏结束了，画出输赢，否则画出控制
        if (gameState != RUNNING)
            displayVictoryOrDefeat();
        else
            displayControls();

        // 显示缓冲
        writeBuffer.display();
        writeBuffer.clear();

        // 如果游戏进行中，获取键盘移动信息
        if (gameState == RUNNING)
            field.getMove();
        else
            break;
    }

    std::cout << endl
              << reset;

    return 0;
}
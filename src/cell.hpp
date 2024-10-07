#pragma once

#include <vector>
#include <string>
#include "colour.hpp"
#include "setup.hpp"

// 单元格的状态
enum CELL_STATES {
    EMPTY, // 空
    MINE, // 有地雷
    ADJ_TO_MINE // 旁边地雷数
};

// 不同数量的地雷旁边的颜色数目
COLOUR MINE_COLOURS[] = {
    reset,
    cyan_fg, //1
    green_fg, //2
    red_fg, //3
    magenta_fg, //4
    yellow_fg, //5
    white_fg, //6
    magenta_fg, //7
    red_fg //8
};


class Cell {
public:
    Cell();

    void toggleFlag(); // 将当前格子标记为雷
    void reveal(); // 翻开当前格子
    void setMine(); // 设置当前格子为雷
    void markAdjMine(int); // 标记当前格子旁边的雷数
    bool flagged;
    bool hidden;
    CELL_STATES state;
    int noOfAdjMines;
    std::string sym;
};


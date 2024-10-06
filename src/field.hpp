#pragma once

#include <utility>
#include <vector>
#include "cell.hpp"

using GRID = std::vector<std::vector<Cell>>;

class Field
{
  public:
    Field();
    void mineTheField();
    void markAdjMineCells();
    void startSweep(int, int);
    void startSweep(int, int, POSOF_CELL, DIR_X, DIR_Y);
    void drawField();
    void checkVictoryAndFlagMines();
    void getMove();

    bool checkValidityOfQuickClear();
  
  private:
    int l;
    int b;
    int m;
    int x;
    int y;
    int flags;
    int hiddenCells;
    
    bool firstSweep;
    
    std::vector<std::pair<int, int>> mines; 
    
    GRID cells;
};
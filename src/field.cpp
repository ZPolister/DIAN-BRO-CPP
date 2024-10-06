//
// Created by Polister on 2024/10/6.
//
#include <iostream>
#include <random>
#include "sevsegdisp.hpp"
#include "buffer.hpp"
#include "display.hpp"
#include "colour.hpp"
#include "field.hpp"

Field::Field() {
    switch (gameMode) {
        case BEGINNER:
            l = 9;
            b = 9;
            m = 10;
            break;
        case INTERMEDIATE:
            l = 16;
            b = 16;
            m = 40;
            break;
        case EXPERT:
            l = 30;
            b = 16;
            m = 99;
            break;
        case CUSTOM:
            do {
                displayBanner();
                std::cout << endl;
                std::cout << white_fg << "    Minimum breadth of MineField is 9" << endl;
                std::cout << white_fg << "    Maximum size of MineField is 30 x 16" << endl;
                std::cout << blue_fg << "    Enter length of MineField : " << white_fg;
                std::cin >> l;

                std::cout << blue_fg << "    Enter breadth of MineField : " << white_fg;
                std::cin >> b;

                std::cout << blue_fg << "    Enter number of Mines : " << red_fg;
                std::cin >> m;
                clearScreen();
            } while ((!l || !b || !m) || b < 9 || l > 30 || b > 16);
    }
    x = l / 2;
    y = b / 2;
    if (m > l * b - 9)
        m = l * b - 9;
    flags = m;
    flagDisplay.set(flags);
    hiddenCells = l * b;
    firstSweep = true;
    for (int i = 0; i < l; ++i) {
        Cell c;
        std::vector<Cell> v(b, c);
        cells.push_back(v);
    }
}

void Field::mineTheField() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> x_uni(0, l - 1);
    std::uniform_int_distribution<int> y_uni(0, b - 1);
    auto m_copy = m;
    while (m_copy) {
        auto i = x_uni(rng);
        auto j = y_uni(rng);
        if ((i >= x - 1 && i <= x + 1) &&
            (j >= y - 1 && j <= y + 1))
            continue;
        if (cells[i][j].state != MINE) {
            cells[i][j].setMine();
            mines.emplace_back(i, j);
            --m_copy;
        }
    }
}

void Field::markAdjMineCells() {
    for (auto mine: mines) {
        int x_pos = mine.first, y_pos = mine.second;

        for (int i = x_pos - 1; i < x_pos + 2; ++i) {
            if (i < 0 || i > l - 1)
                continue;

            for (int j = y_pos - 1; j < y_pos + 2; ++j) {
                if (j < 0 || j > b - 1)
                    continue;
                if (cells[i][j].state == MINE)
                    continue;
                int mineCount = 0;

                for (int c = i - 1; c < i + 2; ++c) {
                    if (c < 0 || c > l - 1)
                        continue;
                    for (int d = j - 1; d < j + 2; ++d) {
                        if (d < 0 || d > b - 1)
                            continue;
                        if (cells[c][d].state == MINE)
                            ++mineCount;
                    }
                }
                if (mineCount)
                    cells[i][j].markAdjMine(mineCount);
            }
        }
    }
}

void Field::drawField() {
    writeBuffer << reset;
    for (int s = 0; s <= l * 4; ++s)
        writeBuffer << " ";
    writeBuffer << endl;

    writeBuffer << reset;
    writeBuffer << "    ";
    if (cells[0][0].hidden)
        writeBuffer << "┏";
    else
        writeBuffer << reset << "┌";

    for (int i = 0; i < l - 1; ++i) {
        if (cells[i][0].hidden) {
            writeBuffer << "━━━";
            if (cells[i + 1][0].hidden)
                writeBuffer << "┳";
            else
                writeBuffer << "┱";
        } else {
            writeBuffer << "───";
            if (cells[i + 1][0].hidden)
                writeBuffer << "┲";
            else
                writeBuffer << "┬";
        }
    }

    if (cells[l - 1][0].hidden)
        writeBuffer << "━━━┓";
    else
        writeBuffer << "───┐";
    writeBuffer << endl;

    writeBuffer << reset;
    for (int j = 0; j < b; ++j) {
        if (cells[0][j].hidden)
            writeBuffer << "    ┃";
        else
            writeBuffer << reset << "    │";

        for (int i = 0; i < l; ++i) {
            if (cells[i][j].state != MINE || cells[i][j].hidden)
                writeBuffer << " ";
            else
                writeBuffer << " ";

            if (i == x && j == y) {
                if ((cells[i][j].hidden || cells[i][j].state == EMPTY) &&
                    (!cells[i][j].flagged))
                    writeBuffer << blue_bg << " ";

                else
                    writeBuffer << blue_bg << cells[i][j].sym;
            } else
                writeBuffer << cells[i][j].sym;

            if (cells[i][j].hidden || (i != l - 1 && cells[i + 1][j].hidden))
                writeBuffer << reset << " ┃";
            else
                writeBuffer << reset << " │";
        }

        if (j != b - 1) {
            writeBuffer << endl;
            writeBuffer << reset;
            writeBuffer << "    ";

            if (cells[0][j].hidden) {
                if (cells[0][j + 1].hidden)
                    writeBuffer << "┣";
                else
                    writeBuffer << "┡";
            } else {
                if (cells[0][j + 1].hidden)
                    writeBuffer << "┢";
                else
                    writeBuffer << "├";
            }

            for (int k = 0; k < l - 1; ++k) {
                if (cells[k][j].hidden) {
                    writeBuffer << "━━━";

                    if (cells[k + 1][j].hidden && !cells[k][j + 1].hidden && !cells[k + 1][j + 1].hidden) {
                        writeBuffer << "╇";
                    } else if (!cells[k + 1][j].hidden && cells[k][j + 1].hidden && !cells[k + 1][j + 1].hidden) {
                        writeBuffer << "╉";
                    } else if (!cells[k + 1][j].hidden && !cells[k][j + 1].hidden && !cells[k + 1][j + 1].hidden) {
                        writeBuffer << "╃";
                    } else {
                        writeBuffer << "╋";
                    }
                } else {
                    if (cells[k][j + 1].hidden)
                        writeBuffer << "━━━";
                    else
                        writeBuffer << "───";

                    if (cells[k + 1][j].hidden && !cells[k][j + 1].hidden && !cells[k + 1][j + 1].hidden) {
                        writeBuffer << "╄";
                    } else if (!cells[k + 1][j].hidden && cells[k][j + 1].hidden && !cells[k + 1][j + 1].hidden) {
                        writeBuffer << "╅";
                    } else if (!cells[k + 1][j].hidden && !cells[k][j + 1].hidden && cells[k + 1][j + 1].hidden) {
                        writeBuffer << "╆";
                    } else if (cells[k + 1][j].hidden && !cells[k][j + 1].hidden && cells[k + 1][j + 1].hidden) {
                        writeBuffer << "╊";
                    } else if (!cells[k + 1][j].hidden && cells[k][j + 1].hidden && cells[k + 1][j + 1].hidden) {
                        writeBuffer << "╈";
                    } else if (!cells[k + 1][j].hidden && !cells[k][j + 1].hidden && !cells[k + 1][j + 1].hidden) {
                        writeBuffer << "┼";
                    } else {
                        writeBuffer << "╋";
                    }
                }
            }

            if (cells[l - 1][j].hidden) {
                writeBuffer << "━━━";
                if (cells[l - 1][j + 1].hidden)
                    writeBuffer << "┫";
                else
                    writeBuffer << "┩";
            } else {
                if (cells[l - 1][j + 1].hidden)
                    writeBuffer << "━━━┪";
                else
                    writeBuffer << "───┤";
            }
        }

        writeBuffer << endl;
        writeBuffer << reset;
    }

    writeBuffer << "    ";
    if (cells[0][b - 1].hidden)
        writeBuffer << "┗";
    else
        writeBuffer << "└";

    for (int i = 0; i < l - 1; ++i) {
        if (cells[i][b - 1].hidden) {
            writeBuffer << "━━━";
            if (cells[i + 1][b - 1].hidden)
                writeBuffer << "┻";
            else
                writeBuffer << "┹";
        } else {
            writeBuffer << "───";
            if (cells[i + 1][b - 1].hidden)
                writeBuffer << "┺";
            else
                writeBuffer << "┴";
        }
    }

    if (cells[l - 1][b - 1].hidden)
        writeBuffer << "━━━┛";
    else
        writeBuffer << "───┘";

    writeBuffer << endl;

    writeBuffer.goToLine(0);
}

void Field::getMove() {
    KEY k = getKey();
    switch (k) {
        case K_K:
        case K_k:
            if (y)
                --y;
            return;

        case K_J:
        case K_j:
            if (y != b - 1)
                ++y;
            return;

        case K_H:
        case K_h:
            if (x)
                --x;
            return;

        case K_L:
        case K_l:
            if (x != l - 1)
                ++x;
            return;

        case K_SPACE:
        case K_F:
            if (cells[x][y].flagged) {
                ++flags;
                ++flagDisplay;
                cells[x][y].toggleFlag();
            } else if (flags && cells[x][y].hidden) {
                --flags;
                --flagDisplay;
                cells[x][y].toggleFlag();
            }
            return;

        case K_ENTER:
        case K_S:
            if (firstSweep) {
                mineTheField();
                markAdjMineCells();
                firstSweep = false;
            }
            startSweep(x, y);
            return;
    }
}

void Field::checkVictoryAndFlagMines() {
    if (hiddenCells == m && gameState != DEFEAT) {
        gameState = VICTORY;
        for (auto mine: mines) {
            if (!cells[mine.first][mine.second].flagged) {
                cells[mine.first][mine.second].toggleFlag();
            }
        }
    }
}

bool Field::checkValidityOfQuickClear() {
    int flagsCopy = 0;
    for (int i = x - 1; i < x + 2; ++i) {
        for (int j = y - 1; j < y + 2; ++j) {
            if (i < 0 || i > l - 1 || j < 0 || j > b - 1)
                continue;

            if (i == x && j == y)
                continue;

            if (cells[i][j].flagged)
                ++flagsCopy;
        }
    }

    bool valid = flagsCopy == cells[x][y].noOfAdjMines;
    if (valid) {
        for (int i = x - 1; i < x + 2; ++i) {
            for (int j = y - 1; j < y + 2; ++j) {
                if (i < 0 || i > l - 1 || j < 0 || j > b - 1)
                    continue;

                if (i == x && j == y)
                    continue;

                switch (cells[i][j].state) {
                    case EMPTY:
                    case ADJ_TO_MINE:
                        break;

                    case MINE:
                        if (cells[i][j].flagged)
                            break;

                        gameState = DEFEAT;
                        for (auto mine: mines)
                            cells[mine.first][mine.second].reveal();
                }
            }
        }
    }
    return valid;
}

void Field::startSweep(int x, int y) {
    if (gameState != RUNNING)
        return;
    if (cells[x][y].flagged)
        return;
    if (!cells[x][y].hidden && !QUICK_CLEAR)
        return;

    switch (cells[x][y].state) {
        case EMPTY:
            --hiddenCells;
            cells[x][y].reveal();
            checkVictoryAndFlagMines();
            break;

        case ADJ_TO_MINE:
            if (cells[x][y].hidden) {
                --hiddenCells;
                cells[x][y].reveal();
                checkVictoryAndFlagMines();
                return;
            } else if (QUICK_CLEAR) {
                bool isValid = checkValidityOfQuickClear();
                checkVictoryAndFlagMines();
                if (isValid)
                    break;
                else
                    return;
            }

        case MINE:
            gameState = DEFEAT;
            for (auto mine: mines)
                cells[mine.first][mine.second].reveal();
            return;
    }

    startSweep(x - 1, y - 1, CORNER, LEFT, UP);
    startSweep(x, y - 1, EDGE, NULL_DIR_X, UP);
    startSweep(x + 1, y - 1, CORNER, RIGHT, UP);
    startSweep(x - 1, y, EDGE, LEFT, NULL_DIR_Y);
    startSweep(x + 1, y, EDGE, RIGHT, NULL_DIR_Y);
    startSweep(x - 1, y + 1, CORNER, LEFT, DOWN);
    startSweep(x, y + 1, EDGE, NULL_DIR_X, DOWN);
    startSweep(x + 1, y + 1, CORNER, RIGHT, DOWN);
    checkVictoryAndFlagMines();
}

void Field::startSweep(int x, int y, POSOF_CELL pos, DIR_X x_dir, DIR_Y y_dir) {
    checkVictoryAndFlagMines();
    if (x < 0 || x > l - 1 || y < 0 || y > b - 1)
        return;
    if (gameState != RUNNING)
        return;
    if (cells[x][y].flagged)
        return;
    if (!cells[x][y].hidden)
        return;

    switch (cells[x][y].state) {
        case EMPTY:
            cells[x][y].reveal();
            --hiddenCells;
            if (pos == CORNER) {
                startSweep(x + x_dir, y + y_dir, CORNER, x_dir, y_dir);
                startSweep(x + x_dir, y, EDGE, x_dir, NULL_DIR_Y);
                startSweep(x, y + y_dir, EDGE, NULL_DIR_X, y_dir);
                startSweep(x + x_dir, y - y_dir, CORNER, x_dir, (DIR_Y) (-y_dir));
                startSweep(x - x_dir, y + y_dir, CORNER, (DIR_X) (-x_dir), y_dir);
            } else {
                startSweep(x + x_dir, y + y_dir, EDGE, x_dir, y_dir);

                if (y_dir == NULL_DIR_Y) {
                    startSweep(x + x_dir, y - 1, CORNER, x_dir, UP);
                    startSweep(x, y - 1, EDGE, NULL_DIR_X, UP);
                    startSweep(x, y + 1, EDGE, NULL_DIR_X, DOWN);
                    startSweep(x + x_dir, y + 1, CORNER, x_dir, DOWN);
                } else {
                    startSweep(x - 1, y + y_dir, CORNER, LEFT, y_dir);
                    startSweep(x - 1, y, EDGE, LEFT, NULL_DIR_Y);
                    startSweep(x + 1, y, EDGE, RIGHT, NULL_DIR_Y);
                    startSweep(x + 1, y + y_dir, CORNER, RIGHT, y_dir);
                }
            }

            break;

        case ADJ_TO_MINE:
            cells[x][y].reveal();
            --hiddenCells;
            break;
    }
}

//
// Created by Polister on 2024/10/6.
//

#include "cell.hpp"


Cell::Cell(): hidden(true), flagged(false), state(EMPTY),
              sym(white_bg + " "), noOfAdjMines(0) {}

void Cell::toggleFlag()
{
    if (hidden)
    {
        flagged = !flagged;
        sym = flagged ? green_fg + "▶" : sym = white_bg + " ";
    }
}

void Cell::reveal()
{
    if (!flagged && hidden)
    {
        hidden = false;
        switch (state)
        {
            case EMPTY:
                sym = reset + " ";
                return;
            case MINE:
                sym = red_fg + "✸";
                return;
            case ADJ_TO_MINE:
                sym = MINE_COLOURS[noOfAdjMines] + std::to_string(noOfAdjMines);
                return;
        }
    }
}

void Cell::markAdjMine(int mines)
{
    state = ADJ_TO_MINE;
    noOfAdjMines = mines;
}

void Cell::setMine()
{
    state = MINE;
}


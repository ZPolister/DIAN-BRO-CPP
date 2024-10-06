//
// Created by Polister on 2024/10/6.
//

#include "setup.hpp"

GAME_MODE gameMode;
GAME_STATE gameState = RUNNING;
bool QUICK_CLEAR = false;


KEY getKey()
{
char c = (char)getch();
c = (c == K_ESC) ? (char)getch() : c;
c = (c == K_BRAC_OPEN) ? (char)getch() : c;
return c;
}
//
// Created by Polister on 2024/10/6.
//

#include "setup.hpp"

#ifdef _WIN32
#include <conio.h>
#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
#include <termios.h>
#include <unistd.h>
#endif

GAME_MODE gameMode;
GAME_STATE gameState = RUNNING;
bool QUICK_CLEAR = false;


KEY getKey() {
    char c = (char) getch();
#if defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
    c = (c == K_ESC) ? (char) getch() : c;
    c = (c == K_BRAC_OPEN) ? (char) getch() : c;
#elifdef _WIN32
    c = (c == -32) ? (char) getch() : c;
#endif
    return c;
}

#if defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
char getch() {
    char buf = 0;
    termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

#elifdef _WIN32
char getInputChar() {
    char ch = getch();
    if (ch == -32)
        ch = getch()

    return ch;
}
#endif


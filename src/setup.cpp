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
#endif

KEY getKey() {
    bool flag = false;
    char c = (char) getch();
#if defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
    c = (c == K_ESC) ? (char) getch() : c;
    if (c == K_BRAC_OPEN) {
        flag = true;
        c = (char)getch();
    }
#elif defined(_WIN32)
    if (c == -32) {
        flag = true;
        c = (char)getch();
    }
#endif
    // 箭头键转换为VI键位，防止冲突
    if (flag) {
        switch(c) {
            case K_UP:
                c = K_K;
                break;
            case K_DOWN:
                c = K_J;
                break;
            case K_LEFT:
                c = K_H;
                break;
            case K_RIGHT:
                c = K_L;
                break;
            default:
                break;
        }
    }
    return c;
}
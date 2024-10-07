//
// Created by Polister on 2024/10/6.
//

#include <iostream>
#include <iomanip>
#include <cctype>
#include "display.hpp"
#include "buffer.hpp"
#include "setup.hpp"
#include "sevsegdisp.hpp"
#include "colour.hpp"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

void maximizeConsole() {
#ifdef _WIN32
    keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11,0, KEYEVENTF_KEYUP,0);
#else
    printf("\e[8;100;600t");  // 根据需要设置行数和列数
#endif
}

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

void displayBanner() {

    std::cout << blue_fg;
    std::cout << R"(
    ##     ##  ##  ##    ## ########  ######  ##      ## ######## ######## ########  ######## ########
    ###   ###  ##  ###   ## ##       ##    ## ##  ##  ## ##       ##       ##     ## ##       ##     ##
    #### ####  ##  ####  ## ##       ##       ##  ##  ## ##       ##       ##     ## ##       ##     ##
    ## ### ##  ##  ## ## ## ######    ######  ##  ##  ## ######   ######   ########  ######   ########
    ##     ##  ##  ##  #### ##             ## ##  ##  ## ##       ##       ##        ##       ##   ##
    ##     ##  ##  ##   ### ##       ##    ## ##  ##  ## ##       ##       ##        ##       ##    ##
    ##     ##  ##  ##    ## ########  ######   ###  ###  ######## ######## ##        ######## ##     ##)";
    std::cout << reset << endl;

}

void displayFlagCounter() {
    writeBuffer << white_fg << R"(                (_)               )" << endl;
    writeBuffer << white_fg << R"(   _ __ ___  _ _ __   ___ ___ )" << endl;
    writeBuffer << white_fg << R"(  | '_ ` _ \| | '_ \ / _ / __|)" << endl;
    writeBuffer << white_fg << R"(  | | | | | | | | | |  __\__ \)" << endl;
    writeBuffer << white_fg << R"(  |_| |_| |_|_|_| |_|\___|___/)" << endl;
    writeBuffer << reset;

    flagDisplay.update("      ");
}

void displayControls() {
    writeBuffer << endl;
    writeBuffer << white_fg << "  ↑, ←, ↓, → : " << endl;
    writeBuffer << white_fg << "       OR      Movement" << endl;
    writeBuffer << white_fg << "  H, J, K, L : " << endl;
    writeBuffer << white_fg << "  S or ENTER : Sweep" << endl;
    writeBuffer << white_fg << "  F or SPACEBAR : Toggle Flag" << endl;
}

void displayVictoryOrDefeat() {
    writeBuffer << endl;
    COLOUR col = gameState == VICTORY ? green_fg : red_fg;

    writeBuffer << col << R"(  __   _____  _   _ )" << endl;
    writeBuffer << col << R"(  \ \ / / _ \| | | |)" << endl;
    writeBuffer << col << R"(   \ V / (_) | |_| |)" << endl;
    writeBuffer << col << R"(    |_| \___/ \___/ )" << endl;

    writeBuffer << endl;

    if (gameState == VICTORY)
    {

        writeBuffer << col << R"(  __      _____ _  _ _ )" << endl;
        writeBuffer << col << R"(  \ \    / /_ _| \| | |)" << endl;
        writeBuffer << col << R"(   \ \/\/ / | || .` |_|)" << endl;
        writeBuffer << col << R"(    \_/\_/ |___|_|\_(_))" << endl;
    }

    else
    {
        writeBuffer << col << R"(   _    ___  ___ ___ _ )" << endl;
        writeBuffer << col << R"(  | |  / _ \/ __| __| |)" << endl;
        writeBuffer << col << R"(  | |_| (_) \__ \ _||_|)" << endl;
        writeBuffer << col << R"(  |____\___/|___/___(_))" << endl;
    }

    // 防止Windows小黑窗直接退出
#ifdef _WIN32
    getch();
#endif
}

void setGameMode() {
    int ch;
    do
    {
        displayBanner();
        std::cout << std::setw(30);
        std::cout << yellow_fg << "Maximise Terminal or press F11 for the optimal experience" << reset;
        std::cout << endl
                  << endl;
        std::cout << std::setw(30);
        std::cout << white_fg << "Choose Game Mode:\n";
        std::cout << std::setw(30);
        std::cout << green_fg << "1. Beginner\n";
        std::cout << std::setw(30);
        std::cout << yellow_fg << "2. Intermediate\n";
        std::cout << std::setw(30);
        std::cout << red_fg << "3. Expert\n";
        std::cout << std::setw(30);
        std::cout << blue_fg << "4. Custom\n\n";
        std::cout << "                       ";
        ch = getch() - '0';


        if (ch < 1 || ch > 4)
        {
            std::cout << red_fg << "Invalid Choice. Try again\n";
        }
        else
            gameMode = (GAME_MODE)ch;

        clearScreen();

    } while (ch < 1 || ch > 4);
}

void getQuickClearSettings() {
    char ch;
    do
    {
        displayBanner();
        std::cout << endl;
        std::cout << yellow_fg <<
                  R"(            Quick Clear : If a cell with a number on it is already revealed,
                         and it's neighbours have been flagged with the same number,
                         then all tiles adjacent to this cell are also sweeped.

            Enable Quick Clear? )";

        std::cout << white_fg << "[" << green_fg <<"Y" << white_fg << " / " << red_fg << "N" << white_fg << "] : " << reset;

        std::cin >> ch;

        ch = std::tolower(ch);

        if (!(ch == 'y' || ch == 'n'))
        {
            std::cout << red_fg << "Invalid Choice. Try again\n";
            auto c = getch();
        }
        else
            QUICK_CLEAR = std::tolower(ch) == 'y';

        clearScreen();


    } while (!(ch == 'y' || ch == 'n'));
}

void saveLocation() {
    printf("\033[s");
}

void backLocation() {
    printf("\033[u");
}

void clearSiteToEnd() {
    printf("\033[K");
}

void hideCursor() {
    printf("\033[?25l");
}


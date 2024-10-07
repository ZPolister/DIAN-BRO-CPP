#include <iostream>


#include "field.hpp"
#include "buffer.hpp"
#include "setup.hpp"
#include "colour.hpp"
#include "display.hpp"

int main()
{
#ifdef _WIN32
    system("chcp 65001");
#endif
    maximizeConsole();
    hideCursor();
    clearScreen();
    setGameMode();
    getQuickClearSettings();

    Field field;
    saveLocation();
    while (true)
    {
        clearSiteToEnd();

        displayBanner();
        field.drawField();
        displayFlagCounter();

        if (gameState != RUNNING)
            displayVictoryOrDefeat();
        else
            displayControls();

        writeBuffer.display();
        writeBuffer.clear();

        if (gameState == RUNNING)
            field.getMove();
        else
            break;
    }

    std::cout << endl
              << reset;

    return 0;
}
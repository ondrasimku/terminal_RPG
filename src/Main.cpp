#include <iostream>
#include "classes/Game.h"

/* MAIN FUNCTION */
int main()
{
    Game game;
    game.mainMenu(); // Main menu handles calling characted creation or loading saved game.
        // It also starts the main game loop
   std::cout << "Ukončuji!" << std::endl;
    return 0;
}
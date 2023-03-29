#include "Ragnarok.h"
#include "../misc/Key.h"
#include "../weapons/Sword.h"
#include <iostream>
#include <limits>


Ragnarok::Ragnarok(const std::string &name, const double &strength, const int &level, const double &armor,
                   const int &health, const int &maxHealth, Item *drop) : Wendigo(name, strength, level, armor, health, maxHealth, drop) {}

void Ragnarok::deathAction(Player *player) {
    //Wendigo::deathAction(player);
    Console::clear();
    Console::printFile("texts/Louka/RagnarokOnDeath.txt");

    std::cout << "Přeješ si zabít Ragnaroka? (Y/N): ";
    char prompt;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> prompt && (prompt == 'y' || prompt == 'n' || prompt == 'Y' || prompt == 'N'))
        {
            break;
        }
        std::cout << "Zadej validní volbu!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(prompt == 'N')
    {
        player->inventoryAdd(new Key("Klíč", "Komnata"));
        return;
    }
    player->inventoryAdd(new Key("Klíč", "Komnata"));
    player->inventoryAdd(new Sword("Ragnarokův_meč", 300.0));
}

Ragnarok::~Ragnarok() {

}

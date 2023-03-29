#include "classes/Arena.h"
#include "classes/Console.h"
#include <iostream>
#include <limits>

bool Arena::fight(Player & player, Entity & entity ) {
    Weapon* primary = player.getPrimaryWeapon();
    bool simulate = false;

    if(primary->getItemType() == Item::BOW)
    {
        printStats(player, entity);
        playerMenu(player, &simulate);
        std::cout << "Útočíš lukem, než se k tobě nepřítel přiblíži" << std::endl;
        int shotsFired = Console::genRand(1, 5);
        for(int i = 0; i < shotsFired; ++i)
        {
            player.attack(entity, *primary);
        }
        std::cout << "Podařilo se ti vystřelit " << shotsFired << " šípů" << std::endl;
        primary = player.getSecondaryWeapon();
    }

    if(!simulate)
        std::cin.get();
    Console::clear();
    while(true)
    {
        printStats(player, entity);
        if(!simulate)
            playerMenu(player, &simulate);
        player.attack(entity, *primary);
        if(entity.getHealth() <= 0)
        {
            Console::clear();
            printStats(player, entity);
            std::cout << entity.getName() << " umřel." << std::endl;
            break;
        }
        if(!simulate)
            std::cin.get();
        Console::clear();


        printStats(player,  entity);
        entity.attack(player);
        if(player.getHealth() <= 0)
        {
            Console::clear();
            printStats(player,  entity);
            std::cout << " umřel jsi" << std::endl;
            break;
        }
        else if(entity.getHealth() <= 0)
        {
            Console::clear();
            printStats(player,  entity);
            std::cout << entity.getName() << " umřel." << std::endl;
            break;
        }
        if(!simulate)
            std::cin.get();
        Console::clear();
    }

    player.removePotions();
    if(entity.getHealth() <= 0)
    {
        entity.deathAction(&player);
        return true;
    }
    else
    {
        return false;
    }
}

void Arena::playerMenu(Player &player, bool *simulate) {
    std::cout << "1. Pokračovat\n2. Health Potion\n3. Strength Potion\n4. Dosimulovat" << std::endl;
    int choice;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice > 0 && choice <= 4)
        {
            break;
        }
        else
        {
            std::cout << "Zadej validní volbu!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch(choice)
    {
        case 1:
            break;
        case 2:
            player.useHealthPotion();
            playerMenu(player, simulate);
            break;
        case 3:
            player.useStrengthPotion();
            playerMenu(player, simulate);
            break;
        case 4:
            *simulate = true;
            break;
    }
}

void Arena::printStats(Player &player, Entity &entity)
{
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << player.getName() << "\t\t\t\t" << entity.getName() << std::endl;
    std::cout << "Health: " << player.getHealth() << "\t\t\tHealth: " << entity.getHealth() << std::endl;
    std::cout << "Strength: " << player.getStrength() << "\t\t\tStrength: " << entity.getStrength() << std::endl;
    std::cout << "Armor: " << player.getArmor() << "\t\t\tArmor: " << entity.getArmor() << std::endl;
    std::cout << "Max health: " << player.getMaxHealth() << "\t\tMax health: " << entity.getMaxHealth() << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
}

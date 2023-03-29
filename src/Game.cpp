#include "classes/Game.h"
#include "classes/Player.h"
#include "classes/Console.h"
#include "classes/Item.h"
#include "classes/weapons/Sword.h"
#include "classes/weapons/Axe.h"
#include "classes/weapons/Knife.h"
#include "classes/weapons/Bow.h"
#include "classes/entities/Rhaaba.h"
#include "classes/entities/Wendigo.h"
#include "classes/entities/Human.h"
#include "classes/entities/Ragnarok.h"
#include "classes/Arena.h"
#include "classes/locations/Location.h"
#include "classes/locations/GameStart.h"
#include "classes/locations/Eriador/Eriador.h"
#include "classes/locations/Les/Les.h"
#include "classes/locations/Louka/Louka.h"
#include "classes/locations/Hrad/Hrad.h"
#include "classes/locations/Komnata/Komnata.h"
#include "classes/potions/Health.h"
#include "classes/potions/Strength.h"
#include <iostream>
#include <limits>
#include <string>
#include <filesystem>


Game::Game()
{
    std::cout << "Hra spuštěna!" << std::endl;
    m_locationCount = 0;
    m_end = false;
    m_player = nullptr;
}

Game::~Game() {
    for(auto &location : m_locations)
        delete location;

    if(m_player != nullptr)
        delete m_player;
}

void Game::mainMenu()
{
    Console::initRand();
    Console::clear();
    std::cout << "Hlavní menu - napiš svou volbu\n-----------" << std::endl;
    std::cout << "1. Nová hra\n2. Načíst save\n3. Smazat save\n0. Konec" << std::endl;
    int choice;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice >= 0 && choice < 4)
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

    Console::clear();

    switch(choice)
    {
        case 1:
            newGame();
            break;
        case 2:
            loadSave();
            break;
        case 3:
            removeSave();
            break;
        case 0:
            return;
        default:
            return;
    }
}

void Game::newGame()
{
    addLocation(new GameStart("cesta do Eriadoru", m_locationCount));
    m_locations[0]->addEnemy(new Rhaaba("Rhaaba", 20.0, 1, 2000, 2000, new Sword("Bersek", 150.0)));
    m_locations[0]->addEnemy(new Wendigo("Wendigo", 20.0, 1, 4.0, 2000, 2000, nullptr));
    addLocation(new Eriador("Eriador", m_locationCount));
    addLocation(new Les("Temný les", m_locationCount));
    m_locations[2]->addEnemy(new Rhaaba("Rhaaba", 45.0, 2, 2500, 2500, nullptr));
    m_locations[2]->addEnemy(new Wendigo("Wendigo", 50.0, 2, 30.0, 2000, 2000, nullptr));
    m_locations[2]->addEnemy(new Rhaaba("Rhaaba", 70.0, 4, 3000, 3000, new StrengthPotion(200)));
    m_locations[2]->addEnemy(new Wendigo("Wendigo", 5.0, 4, 60.0, 2000, 2000, nullptr));
    addLocation(new Louka("Louka za temným lesem", m_locationCount));
    m_locations[3]->addEnemy(new Ragnarok("Ragnarok", 100.0, 7, 20.0, 3000, 3000, nullptr));
    addLocation(new Hrad("Hrad", m_locationCount));
    m_locations[4]->addEnemy(new Rhaaba("Rhaaba", 45.0, 2, 2500, 2500, nullptr));
    m_locations[4]->addEnemy(new Wendigo("Wendigo", 50.0, 2, 30.0, 2000, 2000, new HealthPotion(500)));
    m_locations[4]->addEnemy(new Rhaaba("Rhaaba", 70.0, 4, 3000, 3000, new StrengthPotion(200)));
    m_locations[4]->addEnemy(new Wendigo("Wendigo", 5.0, 4, 60.0, 2000, 2000, nullptr));
    addLocation(new Komnata("Komnata", m_locationCount, &m_end));
    addNeighbour(1, 0);
    addNeighbour(1, 2);
    addNeighbour(2, 3);
    addNeighbour(1, 4);
    addNeighbour(4, 5);
    m_player = new Player();
    m_player->newPlayer();
    enter(m_locations[0]);
    gameLoop();
}



void Game::gameLoop()
{
    m_end = false;
    while(!m_end)
    {
        switch(loopMenu())
        {
            case 0:
                m_end = true;
                break;
            case 1:
                travel();
                break;
            case 2:
                arena();
                break;
            case 3:
                inventory();
                break;
            case 4:
                m_player->changePrimary();
                break;
            case 5:
                m_player->changeSecondary();
                break;
            case 6:
                saveGame();
                break;
            default:
                std::cout << "Zadej validní volbu" << std::endl;
                continue;
        }
    }
}

int Game::loopMenu() {
    int choice;
    std::cout << "\n\nCo si přeješ udělat dál?" << std::endl;
    std::cout << "1. Cestovat\n2. Bojovat\n3. Inventář\n4. Změnit primární zbraň\n5. Změnit sekundární zbraň\n6. Uložit\n0. Konec" << std::endl;

    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice)
        {
            break;
        }
        std::cout << "Zadej validní volbu!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return choice;
}

void Game::travel() {
    Console::clear();
    int cnt = 1;
    std::cout << "0. Zpět" << std::endl;
    for(auto & neighbour : m_currentLocation->getNeighbours())
    {
        std::cout << cnt << ". " << neighbour->getName() << std::endl;
        cnt++;
    }
    int choice;
    std::cout << "\nVyber kam chceš cestovat" << std::endl;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice >= 0 && choice < cnt)
        {
            break;
        }
        std::cout << "Zadej validní volbu!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(choice == 0)
        return;
    choice -= 1;
    enter(m_currentLocation->getNeighbours()[choice]);
}

void Game::enter(Location* location) {
    if(location->canEnter(m_player->getInventory(), m_locations))
    {
        m_currentLocation = location;
        m_currentLocationIdx = location->getIdx();
        location->showEnterText();
        m_currentLocation->m_alreadyEntered = true;
    }
}

void Game::arena() {
    Console::clear();
    int cnt = 1;
    std::cout << "0. Zpět" << std::endl;
    for(auto & enemy : m_currentLocation->getEnemies())
    {
        std::cout << cnt << ". " << enemy->getName() << ", síla: " << enemy->getStrength() << ", životy: " << enemy->getHealth() << std::endl;
        cnt++;
    }

    int choice;
    std::cout << "\nVyber s kým chceš bojovat" << std::endl;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice >= 0 && choice < cnt)
        {
            break;
        }
        std::cout << "Zadej validní volbu!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(choice == 0)
        return;

    choice -= 1;
    bool result = Arena::fight(*m_player, *m_currentLocation->getEnemies()[choice]);
    if(result)
    {
        m_player->heal();
        m_player->addXP(50);
        m_currentLocation->eraseEnemy(choice);
    }
    else
    {
        playerDeath();
    }

}

void Game::inventory() {
    Console::clear();
    m_player->printInventory();
}

void Game::saveGame() {
    std::string fileName;
    std::cout << "\nZadej jméno savu" << std::endl;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> fileName)
        {
            break;
        }
        std::cout << "Zadej validní volbu!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    m_player->save(fileName, m_locationCount, m_currentLocationIdx);

    for(auto & location : m_locations)
    {
        location->save(fileName);
    }

    std::fstream saveFile;
    saveFile.open("examples/saves/"+fileName, std::ios::out | std::ios::app);
    if(!saveFile)
    {
        std::cerr << "Error opening save file" << std::endl;
        saveFile.close();
        return;
    }
    saveFile << "LOCATION_END" << std::endl;

    for(const auto & m_neighbour : m_neighbours)
    {
        saveFile << m_neighbour.first << " " << m_neighbour.second << std::endl;
    }
    saveFile << "NEIGHBOUR_END" << std::endl;
    saveFile.close();
}

void Game::loadSave() {
    Console::clear();
    std::string savesPath = "examples/saves/";
    std::vector<std::string> saves;
    int cnt = 1;
    for (const auto &file : std::filesystem::directory_iterator(savesPath)) {
        std::cout << cnt << ". " << file.path().string() << std::endl;
        saves.push_back(file.path().string());
        cnt++;
    }

    std::cout << "0. Zpět" << std::endl;

    int choice;
    std::cout << "\nVyber si save" << std::endl;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice >= 0 && choice < cnt)
        {
            break;
        }
        std::cout << "Zadej validní volbu!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(choice == 0)
        mainMenu();

    std::string line;
    std::ifstream file;
    if(choice == 0)
        return;
    file.open(saves[choice-1]);
    if(!file)
        std::cerr << "Error opening save file" << std::endl;

    getline(file, line);
    std::istringstream iss(line);

    if(!readPlayer(iss))
    {
        file.close();
        return;
    }

    if(!readInventory(file, line))
    {
        file.close();
        return;
    }
    getline(file, line);
    iss.clear();
    iss.str(line);
    int numOfLocations;
    int currLocation;
    if(!(iss >> numOfLocations >> currLocation))
        return;

    if(!readLocations(file, line))
    {
        file.close();
        return;
    }

    file.close();
    enter(m_locations[currLocation]);
    gameLoop();
}

bool Game::readItem(std::string &itemStr, std::istringstream &iss) {
    if(itemStr == "SWORD")
    {
        std::string name;
        double damage, armorPen;
        if(!(iss >> name >> damage >> armorPen))
        {
            std::cerr << "Error loading item from save file" << std::endl;
            return false;
        }
        else
        {
            m_player->inventoryAdd(new Sword(name, damage));
        }
    }
    else if (itemStr == "AXE")
    {
        std::string name;
        double damage, armorPen;
        if(!(iss >> name >> damage >> armorPen))
        {
            std::cerr << "Error loading item from save file" << std::endl;
            return false;
        }
        else
        {
            m_player->inventoryAdd(new Axe(name, damage, armorPen));
        }
    }
    else if (itemStr == "KNIFE")
    {
        std::string name;
        double damage, armorPen;
        if(!(iss >> name >> damage >> armorPen))
        {
            std::cerr << "Error loading item from save file" << std::endl;
            return false;
        }
        else
        {
            m_player->inventoryAdd(new Knife(name, damage, armorPen));
        }
    }
    else if (itemStr == "BOW")
    {
        std::string name;
        double damage, armorPen;
        if(!(iss >> name >> damage >> armorPen))
        {
            std::cerr << "Error loading item from save file" << std::endl;
            return false;
        }
        else
        {
            m_player->inventoryAdd(new Bow(name, damage, armorPen));
        }
    }
    else if (itemStr == "KEY")
    {
        std::string name, opens;
        if(!(iss >> name >> opens))
        {
            std::cerr << "Error loading item from save file" << std::endl;
            return false;
        }
        else
        {
            m_player->inventoryAdd(new Key(name, opens));
        }
    }
    else if (itemStr == "HEALTH_POTION")
    {
        std::string name;
        int heal;
        if(!(iss >> name >> heal))
        {
            std::cerr << "Error loading item from save file" << std::endl;
            return false;
        }
        else
        {
            m_player->inventoryAdd(new HealthPotion(heal));
        }
    }
    else if(itemStr == "STRENGTH_POTION")
    {
        std::string name;
        int power;
        if(!(iss >> name >> power))
        {
            std::cerr << "Error loading item from save file" << std::endl;
            return false;
        }
        else
        {
            m_player->inventoryAdd(new StrengthPotion(power));
        }
    }

    return true;
}

bool Game::readPlayer(std::istringstream &iss) {
    std::string id, name;
    double strength, armor;
    int level, health, maxHealth, xp, primary, secondary;
    std::string roleStr;
    Player::Role role;
    if(!(iss >> id >> name >> strength >> armor >> level >> health >> maxHealth >> xp >> primary >> secondary >> roleStr))
    {
        std::cerr << "Error loading player info from save file" << std::endl;
        return false;
    }

    if(roleStr == "WARRIOR")
        role = Player::WARRIOR;
    else if (roleStr == "PALADIN")
        role = Player::PALADIN;
    else
        role = Player::HUNTER;

    m_player = new Player(name, strength, armor, level, health, maxHealth, xp, role);
    m_player->setPrimaryIdx(primary);
    m_player->setSecondaryIdx(secondary);
    return true;
}

bool Game::readInventory(std::ifstream &file, std::string &line) {
    while(getline(file, line))
    {
        std::string lineId;
        std::istringstream iss(line);
        if(!(iss >> lineId))
        {
            std::cerr << "Error reading inventory from save file" << std::endl;
            return false;
        }
        if(lineId == "INVENTORY_END")
            break;

        if(!readItem(lineId, iss))
        {
            return false;
        }

    }
    m_player->setPrimaryWeapon(m_player->getInventory()[m_player->getPrimaryIdx()]);
    m_player->setSecondaryWeapon(m_player->getInventory()[m_player->getSecondaryIdx()]);
    return true;
}

void Game::removeSave() {
    std::vector<std::filesystem::directory_entry> saves;
    Console::clear();
    std::string savesPath = "examples/saves/";
    int cnt = 1;
    for(const auto & file : std::filesystem::directory_iterator(savesPath))
    {
        std::cout << cnt << ". " << file.path().string() << std::endl;
        saves.push_back(file);
        cnt++;
    }
    std::cout << "0. Zpět" << std::endl;

    int choice;
    std::cout << "\nVyber si save" << std::endl;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice >= 0 && choice < cnt)
        {
            break;
        }
        std::cout << "Zadej validní volbu!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(choice == 0)
        mainMenu();

    if(choice == 0)
        return;

    std::cout << "Opravdu chceš odstranit save (Y/N): " << saves[choice-1].path().string() << std::endl;

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
        mainMenu();

    if(remove(saves[choice-1]) != 0)
    {
        std::cerr << "Error deleting save" << std::endl;
        mainMenu();
    }
}

void Game::addNeighbour(const int &idx1, const int &idx2) {
    m_locations[idx1]->addNeighbour(m_locations[idx2]);
    m_locations[idx2]->addNeighbour(m_locations[idx1]);

    m_neighbours.insert(std::make_pair(idx1, idx2));
}

void Game::addLocation(Location* location) {
    m_locations.push_back(location);
    m_locationCount++;
}

bool Game::readLocations(std::ifstream &file, std::string &line) {

    while(true) {
        getline(file, line);
        std::istringstream iss(line);
        if(line == "LOCATION_END")
            break;
        int idx;
        bool alreadyEntered;
        std::string name, ts;
        if (!(iss >> ts >> idx >> alreadyEntered))
            return false;
        getline(file, line);
        name = line;

        switch(idx)
        {
            case 0:
                addLocation(new GameStart(name, idx));
                break;
            case 1:
                addLocation(new Eriador(name, idx));
                break;
            case 2:
                addLocation(new Les(name, idx));
                break;
            case 3:
                addLocation(new Louka(name, idx));
                break;
            case 4:
                addLocation(new Hrad(name, idx));
                break;
            case 5:
                addLocation(new Komnata(name, idx, &m_end));
                break;
            default:
                return false;
        }

        m_locations[idx]->m_alreadyEntered = alreadyEntered;

        while (getline(file, line)) {
            if (line == "ENEMY_END")
                break;
            iss.clear();
            iss.str(line);
            std::string type, entName, wepType, wepName;
            double strength, armor, wepDamage, wepArmor;
            int level, health, maxHealth, power;
            bool hasDrop;
            Item *drop;
            if (!(iss >> type >> entName >> strength >> armor >> level >> health >> maxHealth))
                return false;
            getline(file, line);
            iss.clear();
            iss.str(line);
            if (!(iss >> wepType))
                return false;

            hasDrop = (wepType != "nullptr");
            if (hasDrop) {
                if(wepType == "STRENGTH_POTION" || wepType == "HEALTH_POTION")
                {
                    if (!(iss >> wepName >> power))
                    {
                        return false;
                    }

                    if(wepType == "STRENGTH_POTION")
                        drop = new StrengthPotion(power);
                    else
                        drop = new HealthPotion(power);
                }
                else
                {
                    if (!(iss >> wepName >> wepDamage >> wepArmor))
                        return false;
                    else
                        drop = readWeapon(wepType, wepName, wepDamage, wepArmor);
                }
            } else {
                drop = nullptr;
            }

            if (type == "WENDIGO" && entName != "Ragnarok")
                m_locations[idx]->addEnemy(new Wendigo(entName, strength, level, armor, health, maxHealth, drop));
            else if (type == "RHAABA")
                m_locations[idx]->addEnemy(new Rhaaba(entName, strength, level, health, maxHealth, drop));
            else if (type == "HUMAN")
                m_locations[idx]->addEnemy(new Human(entName, strength, level, armor, health, maxHealth, drop));
            else if (type == "WENDIGO" && entName == "Ragnarok")
                m_locations[idx]->addEnemy(new Ragnarok(entName, strength, level, armor, health, maxHealth, drop));

            std::cout << ts << " " << name << " " << idx << std::endl;
            std::cout << type << " " << entName << " " << strength << " " << armor << " " << level << " " << health
                      << " " << maxHealth << std::endl;
            if (drop != nullptr)
                std::cout << *drop << std::endl;

        }
    }

    while(getline(file, line))
    {
        if(line == "NEIGHBOUR_END")
            break;
        std::istringstream iss(line);
        int n1, n2;
        if(!(iss >> n1 >> n2))
            return false;

        addNeighbour(n1, n2);
    }
    return true;
}

Item* Game::readWeapon(const std::string& type, const std::string& name, double damage, double armorPen) {
    if(type == "SWORD")
        return (new Sword(name, damage));
    else if (type == "AXE")
        return (new Axe(name, damage, armorPen));
    else if (type == "BOW")
        return (new Bow(name, damage, armorPen));
    else if (type == "KNIFE")
        return (new Knife(name, damage, armorPen));
    else
        return nullptr;
}

void Game::playerDeath() {
    Console::clear();
    std::cout << "Umřel jsi" << std::endl;
    int choice;
    std::cout << "\n0. Nová hra" << std::endl;
    std::cout << "1. Načíst save" << std::endl;

    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice >= 0 && choice < 2)
        {
            break;
        }
        std::cout << "Zadej validní volbu!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(choice == 0)
    {
        for(auto & location : m_locations)
            delete location;

        m_locations.clear();
        delete m_player;
        newGame();
    }
    else
    {
        for(auto & location : m_locations)
            delete location;

        m_locations.clear();
        delete m_player;
        loadSave();
    }

}



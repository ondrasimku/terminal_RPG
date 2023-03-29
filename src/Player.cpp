#include "classes/Player.h"
#include "classes/Console.h"
#include "classes/Entity.h"
#include "classes/weapons/Sword.h"
#include "classes/weapons/Axe.h"
#include "classes/weapons/Knife.h"
#include "classes/weapons/Bow.h"
#include "classes/potions/Health.h"
#include "classes/potions/Strength.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>


Player::Player() : Entity("noname", 50.0, 10.0, 1, 2500, 2500, nullptr)
{
    m_xp = 0;
}

Player::Player(const std::string &name, const double &strength, const double &armor, const int &level,
               const int &health,
               const int &maxHealth, const int &xp, Role role)
        : Entity(name, strength, armor, level, health, maxHealth, nullptr), m_xp(xp), m_role(role) {

}

Player::~Player() {
    for(auto item : m_inventory)
        delete item;
}

void Player::newPlayer()
{
    pickName();
    pickRole();

}

void Player::pickName() {
    Console::printFile("texts/character_creation.txt");

    for(;;)
    {
        std::cout << "\nZadej jméno postavy: ";
        if(std::cin >> m_name)
        {
            break;
        }
        else
        {
            std::cout << "Zadej validní jméno!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    Console::clear();
}

void Player::pickRole() {
    Console::printFile("texts/roles.txt");
    std::cout << std::endl;
    std::cout << "1. Warrior\n2. Paladin\n3. Hunter " << std::endl;
    int choice;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice > 0 && choice < 4)
        {
            switch(choice)
            {
                case 1:
                    m_role = WARRIOR;
                    inventoryAdd(new Sword("Meč", 100.0));
                    setPrimaryWeapon(m_inventory[0]);
                    m_primaryIdx = 0;
                    inventoryAdd(new Knife("Nůž", 30.0, 4.0));
                    setSecondaryWeapon(m_inventory[1]);
                    m_secondaryIdx = 1;
                    inventoryAdd(new HealthPotion(200.0));
                    inventoryAdd(new HealthPotion(200.0));
                    inventoryAdd(new HealthPotion(200.0));
                    inventoryAdd(new StrengthPotion(30.0));
                    break;
                case 2:
                    m_role = PALADIN;
                    inventoryAdd(new Axe("Sekera", 80.0, 10.0));
                    setPrimaryWeapon(m_inventory[0]);
                    m_primaryIdx = 0;
                    inventoryAdd(new Knife("Nůž", 30.0, 4.0));
                    setSecondaryWeapon(m_inventory[1]);
                    m_secondaryIdx = 1;
                    inventoryAdd(new HealthPotion(200.0));
                    inventoryAdd(new HealthPotion(200.0));
                    inventoryAdd(new HealthPotion(200.0));
                    inventoryAdd(new StrengthPotion(30.0));
                    break;
                case 3:
                    m_role = HUNTER;
                    inventoryAdd(new Bow("Luk", 100.0, 10.0));
                    setPrimaryWeapon(m_inventory[0]);
                    m_primaryIdx = 0;
                    inventoryAdd(new Knife("Nůž", 50.0, 4.0));
                    setSecondaryWeapon(m_inventory[1]);
                    m_secondaryIdx = 1;
                    inventoryAdd(new Sword("Meč", 30.0));
                    inventoryAdd(new HealthPotion(200.0));
                    inventoryAdd(new HealthPotion(200.0));
                    inventoryAdd(new HealthPotion(200.0));
                    break;
            }
            break;
        }
        else
        {
            std::cout << "Zadej validní číslo!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    Console::clear();
}

void Player::attack(Entity & enemy, Weapon & weapon)
{
    if(m_role == WARRIOR || m_role == HUNTER)
    {
        if(Console::genRand(1, 15) == 4)
            weapon.attack(enemy, m_strength, true);
        else
            weapon.attack(enemy, m_strength, false);
    }
    else
    {
        weapon.attack(enemy, m_strength, false);
    }
}

void Player::inventoryAdd(Item *item) {
    m_inventory.push_back(item);
}

void Player::removePotions() {
    m_strength -= m_potionBoost;
    m_potionBoost = 0;
}

void Player::useHealthPotion() {
    std::vector<size_t> position;
    int cnt = 0;
    for(size_t i = 0; i < m_inventory.size(); ++i)
    {
        if(m_inventory[i]->getItemType() == Item::HEALTH_POTION)
        {
            std::cout << cnt << ". " << *m_inventory[i] << std::endl;
            position.push_back(i);
            cnt++;
        }
    }

    if(cnt > 0)
    {
        int choice;
        for(;;)
        {
            std::cout << "> ";
            if(std::cin >> choice && choice >= 0 && choice < cnt)
            {
                break;
            }
            else
            {
                std::cout << "Zadej validní číslo!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        auto* potion = dynamic_cast<HealthPotion*>(m_inventory[position[choice]]);
        potion->use(&m_health);
        if(m_health > m_maxHealth)
            m_health = m_maxHealth;
        delete m_inventory[position[choice]];
        m_inventory.erase(m_inventory.begin()+position[choice]);
    }
    else
    {
        std::cout << "Nemáš žádné Health Potiony" << std::endl;
    }

}

void Player::printInventory() const {
    std::cout << "----------------------------" << std::endl;
    std::cout << getName() << std::endl;
    std::cout << "Level: " << getLevel() << std::endl;
    std::cout << "Health: " << getHealth() << std::endl;
    std::cout << "Strength: " << getStrength() << std::endl;
    std::cout << "Armor: " << getArmor() << std::endl;
    std::cout << "Max health: " << getMaxHealth() << std::endl;
    std::cout << "----------------------------" << std::endl;

    for(auto & item : m_inventory)
        std::cout << *item << std::endl;
    std::cout << std::endl;
    std::cout << "Primární zbraň: " << *m_primaryWeapon << std::endl;
    std::cout << "Sekundární zbraň: " << *m_secondaryWeapon << std::endl;
}

Player::Role Player::getRole() const {
    return m_role;
}


void Player::setPrimaryWeapon(Item *weapon) {
    m_primaryWeapon = weapon;
}

void Player::setSecondaryWeapon(Item *weapon) {
    m_secondaryWeapon = weapon;
}

Weapon *Player::getPrimaryWeapon() {
    return (dynamic_cast<Weapon*>(m_primaryWeapon));
}

Weapon *Player::getSecondaryWeapon() {
    return (dynamic_cast<Weapon*>(m_secondaryWeapon));
}

void Player::useStrengthPotion() {
    std::vector<size_t> position;
    int cnt = 0;
    for(size_t i = 0; i < m_inventory.size(); ++i)
    {
        if(m_inventory[i]->getItemType() == Item::STRENGTH_POTION)
        {
            std::cout << cnt << ". " << *m_inventory[i] << std::endl;
            position.push_back(i);
            cnt++;
        }
    }

    if(cnt > 0)
    {
        int choice;
        for(;;)
        {
            std::cout << "> ";
            if(std::cin >> choice && choice >= 0 && choice < cnt)
            {
                break;
            }
            else
            {
                std::cout << "Zadej validní číslo!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        auto* potion = dynamic_cast<StrengthPotion*>(m_inventory[position[choice]]);
        potion->use(&m_strength, &m_potionBoost);
        delete m_inventory[position[choice]];
        m_inventory.erase(m_inventory.begin()+position[choice]);
    }
    else
    {
        std::cout << "Nemáš žádné Strength Potiony" << std::endl;
    }
}

std::vector<Item *> & Player::getInventory() {
    return m_inventory;
}

void Player::heal() {
    m_health = m_maxHealth;
}

void Player::addXP(int xp) {
    m_xp += xp;
    if(m_xp >= 100)
    {
        m_level++;
        m_xp -= 100;
    }
}

void Player::save(std::string saveName, int locCnt, int curLocIdx) {
    std::fstream saveFile;
    saveFile.open("examples/saves/"+saveName, std::ios::out);
    if(!saveFile)
    {
        std::cerr << "Error opening save file" << std::endl;
        saveFile.close();
        return;
    }
    saveFile << "PLAYER_BEGIN ";
    saveFile << m_name << " ";
    saveFile << m_strength << " ";
    saveFile << m_armor<< " ";
    saveFile << m_level << " ";
    saveFile << m_health << " ";
    saveFile << m_maxHealth << " ";
    saveFile << m_xp << " ";
    saveFile << m_primaryIdx << " ";
    saveFile << m_secondaryIdx << " ";
    switch(m_role)
    {
        case WARRIOR:
            saveFile << "WARRIOR" << std::endl;
            break;
        case PALADIN:
            saveFile << "PALADIN" << std::endl;
            break;
        case HUNTER:
            saveFile << "HUNTER" << std::endl;
            break;
    }


    for(auto & item : m_inventory)
    {
        item->save(saveFile);
    }
    saveFile << "INVENTORY_END" << std::endl;
    saveFile << locCnt << " " << curLocIdx << std::endl;
    saveFile.close();
}

void Player::changePrimary() {
    std::vector<int> indexes;
    Console::clear();
    int cnt = 1;
    std::cout << "0. Zpět" << std::endl;
    for(int i = 0; i < (int)m_inventory.size(); ++i)
    {
        if(m_inventory[i]->getItemType() == Item::SWORD || m_inventory[i]->getItemType() == Item::AXE || m_inventory[i]->getItemType() == Item::BOW)
        {
            std::cout << cnt << ". " << *m_inventory[i] << std::endl;
            indexes.push_back(i);
            cnt++;
        }
    }

    int choice;
    std::cout << "Vyber si primární zbraň" << std::endl;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice >= 0 && choice < cnt)
        {
            break;
        }
        else
        {
            std::cout << "Zadej validní číslo!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if(choice == 0)
        return;

    setPrimaryWeapon(m_inventory[indexes[choice-1]]);
    m_primaryIdx = indexes[choice-1];
}

void Player::changeSecondary() {
    std::vector<int> indexes;
    Console::clear();
    int cnt = 1;
    std::cout << "0. Zpět" << std::endl;
    for(int i = 0; i < (int)m_inventory.size(); ++i)
    {
        if(m_inventory[i]->getItemType() == Item::KNIFE)
        {
            std::cout << cnt << ". " << *m_inventory[i] << std::endl;
            indexes.push_back(i);
            cnt++;
        }
    }

    int choice;
    std::cout << "Vyber si sekundární zbraň" << std::endl;
    for(;;)
    {
        std::cout << "> ";
        if(std::cin >> choice && choice >= 0 && choice < cnt)
        {
            break;
        }
        else
        {
            std::cout << "Zadej validní číslo!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if(choice == 0)
        return;

    setSecondaryWeapon(m_inventory[indexes[choice-1]]);
    m_secondaryIdx = indexes[choice-1];
}

void Player::setPrimaryIdx(int idx) {
    m_primaryIdx = idx;
}

void Player::setSecondaryIdx(int idx) {
    m_secondaryIdx = idx;
}

int Player::getPrimaryIdx() {
    return m_primaryIdx;
}

int Player::getSecondaryIdx() {
    return m_secondaryIdx;
}
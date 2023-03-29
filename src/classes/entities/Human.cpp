#include "Human.h"
#include "../Player.h"
#include "../Console.h"
#include <iostream>

Human::Human(const std::string &name,
               const double &strength,
                 const int &level,
               const double &armor,
               const int &health,
               const int & maxHealth,
               Item *drop = nullptr) : Entity(name, strength, armor, level, health, maxHealth, drop) {}


Human::~Human() {

}

void Human::attack(Player & player)
{
    double totalDamage = Console::genRand(1, 2) * 50.0 + m_strength;
    double armorBlock = player.getArmor() * Console::genRand(1, 2);
    totalDamage = totalDamage - armorBlock;
    player.dealDamage(totalDamage);
    std::cout << "Útok nepřítele " << m_name << " udělil " << totalDamage << " poškození" << std::endl;
}

void Human::save(std::fstream &output) {
    output << "HUMAN " << m_name << " " << m_strength << " " << m_armor << " " << m_level << " " << m_health << " " << m_maxHealth << std::endl;
    if(m_drops == nullptr)
        output << "nullptr" << std::endl;
    else
        m_drops->save(output);
}

void Human::deathAction(Player *player) {
    if(getDrops() != nullptr)
    {
        player->inventoryAdd(getDrops());
        std::cout << "Dropnul ti: " << *(getDrops()) << std::endl;
    }
}

#include "Rhaaba.h"
#include "../Player.h"
#include "../Console.h"
#include <iostream>

Rhaaba::Rhaaba(const std::string &name,
                 const double &strength,
                 const int &level,
                 const int &health,
                 const int & maxHealth,
                 Item *drop = nullptr) : Entity(name, strength, 0, level, health, maxHealth, drop) {}

void Rhaaba::attack(Player & player)
{
    double totalDamage = Console::genRand(1, 2) * 50.0 + m_strength;
    player.dealDamage(totalDamage);
    std::cout << "Útok nepřítele " << m_name << " udělil " << totalDamage << " poškození" << std::endl;
}

Rhaaba::~Rhaaba() {

}

void Rhaaba::save(std::fstream &output) {
    output << "RHAABA " << m_name << " " << m_strength << " " << m_armor << " " << m_level << " " << m_health << " " << m_maxHealth << std::endl;
    if(m_drops == nullptr)
        output << "nullptr" << std::endl;
    else
        m_drops->save(output);
}

void Rhaaba::deathAction(Player *player) {
    if(getDrops() != nullptr)
    {
        player->inventoryAdd(getDrops());
        std::cout << "Dropnul ti: " << *(getDrops()) << std::endl;
    }
}

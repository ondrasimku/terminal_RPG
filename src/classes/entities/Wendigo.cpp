#include "Wendigo.h"
#include "../Player.h"
#include <iostream>

Wendigo::Wendigo(const std::string &name, const double &strength, const int &level, const double &armor,
                 const int &health, const int &maxHealth, Item *drop = nullptr) : Entity(name, strength, armor, level, health, maxHealth, drop) {}

void Wendigo::attack(Player & player)
{
    double totalDamage = Console::genRand(1, 2) * 50.0 + m_strength;
    double armorBlock = player.getArmor() * Console::genRand(1, 2);
    totalDamage = totalDamage - armorBlock;
    if(tryHeal() && player.getRole() == Player::PALADIN)
    {
        m_health = 0;
        return;
    }
    player.dealDamage(totalDamage);
    std::cout << "Útok nepřítele " << m_name << " udělil " << totalDamage << " poškození" << std::endl;
}

Wendigo::~Wendigo() {

}

bool Wendigo::tryHeal() {
    if(Console::genRand(1, 20) == 5)
    {
        m_health = m_maxHealth;
        std::cout << "Nepřítel " << m_name << " se uzdravil!" << std::endl;
        return true;
    }

    return false;
}

void Wendigo::save(std::fstream &output) {
    output << "WENDIGO " << m_name << " " << m_strength << " " << m_armor << " " << m_level << " " << m_health << " " << m_maxHealth << std::endl;
    if(m_drops == nullptr)
        output << "nullptr" << std::endl;
    else
        m_drops->save(output);
}

void Wendigo::deathAction(Player *player) {
    if(getDrops() != nullptr)
    {
        player->inventoryAdd(getDrops());
        std::cout << "Dropnul ti: " << *(getDrops()) << std::endl;
    }
}

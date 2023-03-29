#include "Bow.h"
#include "../Entity.h"
#include "../Console.h"
#include <iostream>

Bow::Bow(const std::string &name,
             const double &damage,
             const double &armorPen) : Weapon(BOW, name, damage, armorPen)
{
}

void Bow::attack(Entity &enemy, double &strength, bool critic)
{
    double totalDamage = Console::genRand(1, 3) * m_damage;
    if(critic)
    {
        enemy.setHealth(0);
        std::cout << "Kritický zásah lukem" << std::endl;
    }
    double armorBlock = enemy.getArmor() * Console::genRand(1, 2);
    if(m_armorPen <= armorBlock)
        armorBlock -= m_armorPen;
    totalDamage = totalDamage - armorBlock;
    if(enemy.getArmor() > m_armorPen + 300)
        totalDamage = 0.0;

    enemy.dealDamage(totalDamage);
    std::cout << "Útok na " << enemy.getName() << " udělil " << totalDamage << " poškození" << std::endl;
}

void Bow::save(std::fstream &output) {
    output << "BOW" << " " << m_name << " " << m_damage << " " << m_armorPen << std::endl;
}

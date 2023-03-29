#include "Knife.h"
#include "../Entity.h"
#include "../Console.h"
#include <iostream>

Knife::Knife(const std::string &name,
             const double &damage,
             const double &armorPen) : Weapon(KNIFE, name, damage, armorPen)
{
}

Knife::~Knife() {

}

void Knife::attack(Entity &enemy, double &strength, bool critic)
{
    double totalDamage = Console::genRand(1, 3) * m_damage + strength;
    if(critic)
    {
        totalDamage *= 2;
        std::cout << "Kritický zásah" << std::endl;
    }
    double armorBlock = enemy.getArmor() * Console::genRand(1, 2);
    if(m_armorPen <= armorBlock)
        armorBlock -= m_armorPen;
    totalDamage = totalDamage - armorBlock;
    enemy.dealDamage(totalDamage);
    std::cout << "Útok na " << enemy.getName() << " udělil " << totalDamage << " poškození" << std::endl;
}

void Knife::save(std::fstream &output) {
    output << "KNIFE" << " " << m_name << " " << m_damage << " " << m_armorPen << std::endl;
}

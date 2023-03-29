#include "Sword.h"
#include "../Entity.h"
#include "../Console.h"
#include <iostream>

Sword::Sword(const std::string &name,
             const double &damage) : Weapon(SWORD, name, damage, 0)
{
}

void Sword::attack(Entity &enemy, double &strength, bool critic) {
    double totalDamage = Console::genRand(1, 3) * m_damage + strength;
    if(critic)
    {
        totalDamage *= 2;
        std::cout << "Kritický zásah" << std::endl;
    }
    enemy.dealDamage(totalDamage);
    std::cout << "Útok na " << enemy.getName() << " udělil " << totalDamage << " poškození" << std::endl;
}

Sword::~Sword() {

}

void Sword::save(std::fstream &output) {
    output << "SWORD" << " " << m_name << " " << m_damage << " " << m_armorPen << std::endl;
}

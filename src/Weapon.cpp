#include "classes/Weapon.h"
#include "classes/Entity.h"

Weapon::Weapon(const Type &type, const std::string &name, const double &damage, const double &armorPen) : Item(type, name)
               {
                   m_damage = damage;
                   m_armorPen = armorPen;
               }

Weapon::~Weapon() {

}

void Weapon::print(std::ostream &os) {
    os << m_name << ", damage: " << m_damage << ", armorPen: " << m_armorPen;
}

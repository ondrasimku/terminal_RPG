#include "Strength.h"
#include <iostream>
#include <fstream>

StrengthPotion::StrengthPotion(double potionPower) : Item(STRENGTH_POTION, "StrengthPotion") {
    m_power = potionPower;
}

StrengthPotion::~StrengthPotion() noexcept {

}

void StrengthPotion::print(std::ostream &os) {
    os << m_name << ",  dodá: " << m_power << " síly";
}

void StrengthPotion::use(double *playerStrength, double *playerPotionBoost) {
    *playerStrength += m_power;
    *playerPotionBoost += m_power;
}

void StrengthPotion::save(std::fstream &output) {
    output << "STRENGTH_POTION" << " " << m_name << " " << m_power << std::endl;
}

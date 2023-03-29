#include "Health.h"
#include <fstream>

HealthPotion::HealthPotion(double potionPower) : Item(HEALTH_POTION, "HealthPotion") {
    m_power = potionPower;
}

HealthPotion::~HealthPotion() {

}

void HealthPotion::print(std::ostream &os) {
    os << m_name << ", healuje za: " << m_power << " životů";
}

void HealthPotion::use(int *playerHealth) {

    *playerHealth += m_power;
}

void HealthPotion::save(std::fstream &output) {
    output << "HEALTH_POTION" << " " << m_name << " " << m_power << std::endl;
}

#include "classes/Entity.h"

Entity::Entity(const std::string &name, const double &strength, const double &armor, const int &level,
               const int &health,
               const int &maxHealth, Item *drop = nullptr)
{
    m_name = name;
    m_strength = strength;
    m_armor = armor;
    m_level = level;
    m_health = health;
    m_maxHealth = maxHealth;
    m_drops = drop;
    m_dropped = false;
}

Entity::~Entity() {
    if(m_drops != nullptr && !m_dropped)
        delete m_drops;
}


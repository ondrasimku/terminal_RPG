#ifndef SIMKUOND_ENTITY_H
#define SIMKUOND_ENTITY_H
#include <string>
#include "./Weapon.h"
#include "./Item.h"

class Player;

class Entity
{
public:
    /**
     * @brief @brief Constructs new instance of Entity
     *
     * Gets called by derived classes.
     *
     * @param name      _string_ with entity's name
     * @param strength  _double_ with entity's strength
     * @param armor     _double_ with entity's armor
     * @param level     _int_ with entity's level
     * @param health    _int_ with entity's current health
     * @param maxHealth _int_ with entity's max health
     * @param drop      _Item*_ pointing to item which will be dropped on death
     */
    Entity(const std::string &name, const double &strength, const double &armor, const int &level, const int &health,
           const int &maxHealth, Item *drop);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Entity();

    /**
     * @brief Virtal method. Gets implemented by derived classes
     *
     * @param player _Player_ to attack
     */
    virtual void attack(Player & player) = 0;

    /**
     * @brief Virtual method. Gets implemented by each derived class.
     *
     * @param output _fstream_ to print itself into
     */
    virtual void save(std::fstream &output) = 0;

    /**
     * @brief Virtual method. Gets implemented by each derived class.
     *
     * Implements after death actions like dropping items or some dialogues.
     *
     * @param player _Player*_ used to interact with players inventory
     */
    virtual void deathAction(Player* player) = 0;

    /**
     * @brief Decreases entity's health by _damage_.
     *
     * @param damage _double_ value of damage to be dealt
     */
    void dealDamage(double & damage) { m_health -= damage; }

    // Getters
    const std::string & getName() const { return m_name; }
    const double & getStrength() const { return m_strength; }
    const double & getArmor() const { return m_armor; }
    const int & getLevel() const { return m_level; }
    const int & getHealth() const {return m_health; }
    const int & getMaxHealth() const {return m_maxHealth; }
    Item* getDrops() { m_dropped = true; return m_drops; }

    // Setters
    void setHealth(const int & newHealth) { m_health = newHealth; }

protected:
    //! name of entitiy
    std::string     m_name;
    //! strength of entitiy
    double          m_strength;
    //! value of armor
    double          m_armor;
    //! current level
    int             m_level;
    //! current health
    int             m_health;
    //! max health
    int             m_maxHealth;
    //! pointer to _Item_ which will be dropped after death
    Item*           m_drops;
    //! true if item is already dropped
    bool            m_dropped;

};

#endif //SIMKUOND_ENTITY_H

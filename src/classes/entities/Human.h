#ifndef SIMKUOND_HUMAN_H
#define SIMKUOND_HUMAN_H
#include "../Entity.h"

class Human : public Entity
{
public:
    /**
     * @brief Constructs new instance of Human entity
     *
     * Calls base constructor.
     *
     * @param name      _string_ with human's name
     * @param strength  _double_ with human's strength
     * @param armor     _double_ with human's armor
     * @param level     _int_ with human's level
     * @param health    _int_ with human's current health
     * @param maxHealth _int_ with human's max health
     * @param drop      _Item*_ pointing to item which will be dropped on death
     */
    Human(const std::string & name,
           const double & strength,
           const int & level,
          const double & armor,
           const int & health,
           const int & maxHealth,
           Item *drop);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Human();

    /**
     * @brief Implementation of saving this class into save file.
     *
     * @param output _fstream_ to print itself into
     */
    virtual void save(std::fstream &output) override;

    /**
     * @brief Defines how this class will attack _Player_
     *
     * @param player _Player_ to attack
     */
    virtual void attack(Player & player) override;

    /**
     * @brief Defines what happens after this entity dies.
     *
     * @param player _Player*_ used to access players inventory and add drop
     */
    virtual void deathAction(Player* player) override;
};

#endif //SIMKUOND_HUMAN_H

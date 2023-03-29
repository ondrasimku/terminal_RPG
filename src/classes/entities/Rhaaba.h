#ifndef SIMKUOND_RHAABA_H
#define SIMKUOND_RHAABA_H
#include "../Entity.h"

class Rhaaba : public Entity
{
public:
    /**
     * @brief Constructs new instance of Rhaaba entity
     *
     * Calls base constructor.
     *
     * @param name      _string_ with rhaaba's name
     * @param strength  _double_ with rhaaba's strength
     * @param armor     _double_ with rhaaba's armor
     * @param level     _int_ with rhaaba's level
     * @param health    _int_ with rhaaba's current health
     * @param maxHealth _int_ with rhaaba's max health
     * @param drop      _Item*_ pointing to item which will be dropped on death
     */
    Rhaaba(const std::string & name,
            const double & strength,
            const int & level,
            const int & health,
            const int & maxHealth,
            Item *drop);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Rhaaba();

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


#endif //SIMKUOND_RHAABA_H

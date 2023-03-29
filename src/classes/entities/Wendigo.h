#ifndef SIMKUOND_WENDIGO_H
#define SIMKUOND_WENDIGO_H
#include "../Entity.h"
#include "../Console.h"

class Wendigo : public Entity
{
public:
    /**
     * @brief Constructs new instance of Wendigo entity
     *
     * Calls base constructor.
     *
     * @param name      _string_ with wendigo's name
     * @param strength  _double_ with wendigo's strength
     * @param armor     _double_ with wendigo's armor
     * @param level     _int_ with wendigo's level
     * @param health    _int_ with wendigo's current health
     * @param maxHealth _int_ with wendigo's max health
     * @param drop      _Item*_ pointing to item which will be dropped on death
     */
    Wendigo(const std::string &name, const double &strength, const int &level, const double &armor,
            const int &health, const int &maxHealth, Item *drop);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Wendigo();

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

    /**
     * @brief Tries to heal Wendigo using random numbers.
     *
     * @return  true    if wendigo healed
     * @return  false   if wendigo didn't heal
     */
    bool tryHeal();
};

#endif //SIMKUOND_WENDIGO_H

#ifndef SIMKUOND_RAGNAROK_H
#define SIMKUOND_RAGNAROK_H
#include "Wendigo.h"
#include "../Player.h"

class Ragnarok : public Wendigo {
public:
    /**
     * @brief Constructs new instance of Ragnarok entity
     *
     * Calls base constructor.
     *
     * @param name      _string_ with ragnarok's name
     * @param strength  _double_ with ragnarok's strength
     * @param armor     _double_ with ragnarok's armor
     * @param level     _int_ with ragnarok's level
     * @param health    _int_ with ragnarok's current health
     * @param maxHealth _int_ with ragnarok's max health
     * @param drop      _Item*_ pointing to item which will be dropped on death
     */
    Ragnarok(const std::string &name, const double &strength, const int &level, const double &armor,
                 const int &health, const int &maxHealth, Item *drop);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Ragnarok();

    /**
     * @brief Defines what happens after this entity dies.
     *
     * @param player _Player*_ used to access players inventory and add drop
     */
    virtual void deathAction(Player* player) override;
};


#endif //SIMKUOND_RAGNAROK_H

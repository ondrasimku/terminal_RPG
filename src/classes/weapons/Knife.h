#ifndef SIMKUOND_KNIFE_H
#define SIMKUOND_KNIFE_H

#include "../Weapon.h"

class Knife : public Weapon
{
public:
    /**
     * @brief Constructs new Knife instance.
     *
     * Calls _Weapon_ constructor to handle all initialization.
     *
     * @param name      _string_ with weapons name
     * @param damage    _double_ with weapons damage
     * @param armorPen  _double_ with weapons armor penetration
     */
    Knife( const std::string & name,
           const double & damage,
           const double & armorPen );

    /**
     * @brief Virtual destructor.
     */
    virtual ~Knife();

    /**
     * @brief Implementation of overriden virtual _attack()_ method.
     *
     * @param enemy     _Entity_ to be attacked
     * @param strength  _double_ strength of player
     * @param critic    _bool_ true if critic has been randomly generated
     */
    virtual void attack(Entity &enemy, double &strength, bool critic) override;

    /**
     * @brief Saves knife to file.
     *
     * @param output _fstream_ to write into
     */
    virtual void save(std::fstream &output) override;

};

#endif //SIMKUOND_KNIFE_H

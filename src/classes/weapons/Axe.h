#ifndef SIMKUOND_AXE_H
#define SIMKUOND_AXE_H
#include "../Weapon.h"

class Axe : public Weapon
{
public:
    /**
     * @brief Constructs new Axe instance.
     *
     * Calls _Weapon_ constructor to handle all initialization.
     *
     * @param name      _string_ with weapons name
     * @param damage    _double_ with weapons damage
     * @param armorPen  _double_ with weapons armor penetration
     */
    Axe( const std::string & name,
           const double & damage,
           const double & armorPen );

    /**
     * @brief Virtual destructor.
     */
    virtual ~Axe() {

    }

    /**
     * @brief Implementation of overriden virtual _attack()_ method.
     *
     * damage depends on players strength and on enemy's armor.
     *
     * @param enemy     _Entity_ to be attacked
     * @param strength  _double_ strength of player
     * @param critic    _bool_ true if critic has been randomly generated
     */
    virtual void attack(Entity &enemy, double &strength, bool critic) override;

    /**
     * @brief Saves Axe to file.
     *
     * @param output _fstream_ to write into
     */
    virtual void save(std::fstream &output) override;

};
#endif //SIMKUOND_AXE_H

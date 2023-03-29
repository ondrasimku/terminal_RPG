#ifndef SIMKUOND_BOW_H
#define SIMKUOND_BOW_H
#include "../Weapon.h"

class Bow : public Weapon
{
public:
    /**
     * @brief Constructs new Bow instance.
     *
     * Calls _Weapon_ constructor to handle all initialization.
     *
     * @param name      _string_ with weapons name
     * @param damage    _double_ with weapons damage
     * @param armorPen  _double_ with weapons armor penetration
     */
    Bow( const std::string & name,
           const double & damage,
           const double & armorPen );

    /**
     * @brief Virtual destructor.
     */
    virtual ~Bow() {

    }

    /**
     * @brief Implementation of overriden virtual _attack()_ method.
     *
     * Bow is not dependant on player strength.
     *
     * @param enemy     _Entity_ to be attacked
     * @param strength  _double_ strength of player
     * @param critic    _bool_ true if critic has been randomly generated
     */
    virtual void attack(Entity &enemy, double &strength, bool critic) override;

    /**
     * @brief Saves bow to file.
     *
     * @param output _fstream_ to write into
     */
    virtual void save(std::fstream &output) override;

};

#endif //SIMKUOND_BOW_H

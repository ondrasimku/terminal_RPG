#ifndef SIMKUOND_SWORD_H
#define SIMKUOND_SWORD_H
#include "../Weapon.h"

class Sword : public Weapon
{
public:
    /**
     * @brief Constructs new Sword instance.
     *
     * Calls _Weapon_ constructor to handle all initialization.
     *
     * @param name      _string_ with weapons name
     * @param damage    _double_ with weapons damage
     */
    Sword( const std::string & name,
           const double & damage);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Sword();

    /**
     * @brief Implementation of overriden virtual _attack()_ method.
     *
     * Sword ignores enemy's armor.
     *
     * @param enemy     _Entity_ to be attacked
     * @param strength  _double_ strength of player
     * @param critic    _bool_ true if critic has been randomly generated
     */
    virtual void attack(Entity &enemy, double &strength, bool critic) override;

    /**
     * @brief Saves sword to file.
     *
     * @param output _fstream_ to write into
     */
    virtual void save(std::fstream &output) override;

};

#endif //SIMKUOND_SWORD_H

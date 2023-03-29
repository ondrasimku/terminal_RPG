#ifndef SIMKUOND_WEAPON_H
#define SIMKUOND_WEAPON_H
#include "Item.h"

class Entity;

class Weapon : public Item
{
public:
    /**
     * @brief Constructs new _Weapon_ instance.
     *
     * Calls base constructor (_Item()_). sets damage and armor penetration.
     * Setting of type and name gets handled by base constructor.
     *
     * @param type      _Type_ of weapon from _Item::TYPE_ enum
     * @param name      _string_ with name of the weapon
     * @param damage    _double_ with weapons damage
     * @param armorPen  _double_ with weapon armor penetration
     */
    Weapon(const Type &type, const std::string &name, const double &damage, const double &armorPen);

    /**
     * @brief Virtual destructor
     */
    virtual ~Weapon();

    /**
     * @brief prints itself to _os_ stream
     *
     * Gets called by base's overloaded << operator.
     *
     * @param os _ostream_ to print itself into
     */
    virtual void print(std::ostream & os) override;

    /**
     * @brief Virtual method which gets implemented inside each child.
     *
     * @param enemy     _Entity_    to attack
     * @param strength  _double_    strength of player
     * @param critic    _bool_      true or false depending on random generation of crtitic attack
     */
    virtual void attack(Entity &enemy, double &strength, bool critic) = 0;

    /**
     * @brief Virtual method which gets implemented inside each child.
     *
     * @param output    _fstream_ to save itself into
     */
    virtual void save(std::fstream &output) = 0;


protected:
    //! damage of weapon
    double  m_damage;
    //! armor penetration of weapon
    double  m_armorPen;
};

#endif //SIMKUOND_WEAPON_H

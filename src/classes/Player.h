#ifndef SIMKUOND_PLAYER_H
#define SIMKUOND_PLAYER_H
#include "./Entity.h"
#include <string>
#include <vector>
#include <string>

class Weapon;

class Player : public Entity
{
public:
    //! Role enum defining which classes can player choose from
    enum Role {WARRIOR, PALADIN, HUNTER};

    /**
     * @brief default constructor
     *
     * Calls base constructor with players starting stats.
     */
    Player();

    /**
     *
     * @brief Constructs new instance of Player
     *
     * Calls base constructor and passes all parameters. Get called after loading player stats from save file.
     *
     * @param name      _string_ with players naem
     * @param strength  _double_ with players strength
     * @param armor     _double_ with players armor
     * @param level     _int_ with players level
     * @param health    _int_ with players current health
     * @param maxHealth _int_ with players max health
     * @param xp        _int_ with players current xp
     * @param role      _Role_ with players picked role
     */
    Player(const std::string &name, const double &strength, const double &armor, const int &level, const int &health,
           const int &maxHealth, const int &xp, Role role);

    /**
     * @brief Destructor if _Player_ class.
     *
     * Deletes every item from _m_inventory_ vector to free memory.
     */
    virtual ~Player();


    /**
     * @brief Let'S user pick name and role.
     *
     * Calls _pickName()_ and _pickRole()_ method.
     */
    void newPlayer();

    /**
     * @brief Saves player stats and every item from inventory to save file.
     *
     * Get's called by _Game_ class when saving game progress. Opens _fstream_ and writes each stat on the first line
     * of save file. Iterates through items in inventory and calls it's _save()_ method which then handles writing the
     * item.
     *
     * @param saveName  _string_ defining save file name
     * @param locCnt    _int_ containing number of locations
     * @param curLocIdx _int_ with index of current location
     */
    void save(std::string saveName, int locCnt, int curLocIdx);

    /**
     * @brief Derived from _Entitiy_. Never used. Plain body.
     *
     * @param output
     */
    virtual void save(std::fstream &output) override {}

    /**
     * @brief Derived from _Entitiy_. Never used. Plain body.
     *
     * @param output
     */
    virtual void deathAction(Player* player) override {}

    /**
     * @brief Prompts user to enter characters name.
     *
     * Saves entered name into _m_name_ string.
     */
    void pickName();

    /*
     * @brief Prompts user to pick role from list.
     *
     * Shows roles.txt containing each roles cons and pros. Adds items to inventory depending on chosen role.
     */
    void pickRole();

    /**
     * @brief Sets new primary weapon
     *
     * @param weapon    _Item*_ pointing to new primary weapon
     */
    void setPrimaryWeapon(Item* weapon);

    /**
     * @brief Sets new secondary weapon
     *
     * @param weapon    _Item*_ pointing to new secondary weapon
     */
    void setSecondaryWeapon(Item* weapon);

    /**
     * @brief Sets new primary weapons idx
     *
     *
     * @param idx   Index of new primary weapon in _m_inventory_ vector
     */
    void setPrimaryIdx(int idx);

    /**
     * @brief Sets new secondary weapons idx
     *
     * @param idx   Index of new secondary weapon in _m_inventory_ vector
     */
    void setSecondaryIdx(int idx);

    /**
     * @brief Returns primary weapons index in _m_inventory_ vector.
     *
     * @return _int_ primary weapon index
     */
    int getPrimaryIdx();

    /**
     * @brief Returns secondary weapons index in _m_inventory_ vector.
     *
     * @return _int_ secondary weapon index
     */
    int getSecondaryIdx();

    /**
     * @brief Let's user to pick new primary weapon.
     *
     * iterates through _m_inventory_ and shows every wepaon in list. User inputs which wepaon
     * to use as new primary weapon.
     */
    void changePrimary();

    /**
     * @brief Let's user to pick new secondary weapon.
     *
     * iterates through _m_inventory_ and shows every KNIFE in list. User inputs which knife
     * to use as new secondary weapon.
     */
    void changeSecondary();

    /**
     * @brief Returns pointer to primary weapon.
     *
     * _dynamic_cast_'s _m_primaryWeapon_ to _Weapon*_ and returns.
     *
     * @return _Weapon*_ pointing to primary weapon
     */
    Weapon* getPrimaryWeapon();

    /**
     * @brief Returns pointer to secondary weapon.
     *
     * _dynamic_cast_'s _m_secondaryWeapon_ to _Weapon*_ and returns.
     *
     * @return _Weapon*_ pointing to secondary weapon
     */
    Weapon* getSecondaryWeapon();

    /**
     * @brief Derived from _Entitiy_. Never used. Plain body.
     *
     * Player never attack another player in this singleplayer game.
     *
     * @param output
     */
    virtual void attack(Player & player) override {};

    /**
     * @brief Attacks _enemy_ with _weapon_ by calling weapons _attack()_ method.
     *
     * If player's role is WARRIOR or HUNTER, player has chance to deal critic.
     *
     * @param enemy     _Entitiy&_ refernece to enemy to be attacked
     * @param weapon    _Weapon&_ reference to weapon to be used in attack
     */
    void attack(Entity & enemy, Weapon & weapon);

    /**
     * @brief Sets players health to _m_maxHealth_
     */
    void heal();

    /**
     * @brief Returns player _Role_
     *
     * @return _Role_ players role from _m_role_
     */
    Role getRole() const;


    /**
     * @brief Removes strength potions boost after fight ends.
     *
     * Subtracts _m_potionBoost_ from _m_strength__
     */
    void removePotions();

    /**
     * @brief Adds _Item*_ to inventory by adding it to _m_inventory_ vector
     *
     * @param item _Item*_ poiting to item which will be added
     */
    void inventoryAdd(Item* item);

    /**
     * @brief Returns _m_inventory_
     *
     * @return _std::vector<Item*>_ which is _m_inventory_
     */
    std::vector<Item *> & getInventory();

    /**
     * @brief Prints player stats and each item from _m_inventory_.
     *
     * Gets called by _Game_'s _inventory()_ method.
     */
    void printInventory() const;


    /**
     * @brief Let's user pick one health potion which will be used.
     *
     * Show's list with every health potion from inventory. Prompts user to pick one of them.
     * Calls potion _use()_ method to use it. Potion is then deleted. If new health is higher
     * than maximum health health is set to it's maximum value.
     */
    void useHealthPotion();

    /**
     * @brief Let's user pick one strength potion which will be used.
     *
     * Show's list of every strength potion from inventory. Prompts user to pick one of them.
     * Calls potion _use()_ method to use it. Potion is then deleted. Potions _m_power_ is added
     * to player strength and added to _m_potionBoost_ member which is uset to remove the boost after
     * fight.
     */
    void useStrengthPotion();

    /**
     * @brief Adds _xp_ to players _m_xp_.
     *
     * if new player's _m_xp_ value is higher or equal to 100, level is increased by 1.
     *
     * @param xp    _int_ number of xp's to add
     */
    void addXP(int xp);


private:
    //! current xp
    int m_xp;
    //! players role
    Role m_role;
    //! vector with items in inventory
    std::vector<Item*> m_inventory;
    //! current potion boost of strength
    double m_potionBoost;
    //! pointer to primary weapon
    Item* m_primaryWeapon;
    //! index of primary weapon in _m_inventory_ vector
    int m_primaryIdx;
    //! pointer to secondary weapon
    Item* m_secondaryWeapon;
    //! index of secondary weapon in _m_inventory_ vector
    int m_secondaryIdx;

};

#endif //SIMKUOND_PLAYER_H

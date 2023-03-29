#ifndef SIMKUOND_KOMNATA_H
#define SIMKUOND_KOMNATA_H
#include "../Location.h"

class Komnata : public Location {
public:

    /**
     * @brief Constructs Komnata location.
     *
     * @param name _string_ name of location
     * @param idx  _int_ index of this location inside _Game_'s _m_locations_ vector
     */
    Komnata(const std::string &name, int idx, bool* endGame);

    /*
     * @brief Virtual destructor.
     */
    virtual ~Komnata();


    /**
     * @brief Implemented _showEnterText()_ method. Shows enter text of this location.
     */
    virtual void showEnterText() override;

    /**
     * @brief Returns whether user can enter this location depending on other locations and players inventory.
     *
     * @param   inventory     _vector<Item*>_ players inventory so this method can check for items
     * @param   locations     _vector<Location*>_ so this method can check other locations for dead enemies
     * @return  true          if user can enter this location
     * @return  false         if user cant enter this location
     */
    virtual bool canEnter(std::vector<Item *> &inventory, std::vector<Location *> locations) override;
private:
    //! is true if ragnarok is dead and player has his sword in inventory
    bool m_killedRagnarok;
    //! pointer to _Game_'s _m_end_ member used to end game in this location
    bool* m_endGame;
};

#endif //SIMKUOND_KOMNATA_H

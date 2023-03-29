#ifndef SIMKUOND_LOUKA_H
#define SIMKUOND_LOUKA_H
#include "../Location.h"

class Louka : public Location {
public:
    /**
     * @brief Constructs Louka location.
     *
     * @param name _string_ name of location
     * @param idx  _int_ index of this location inside _Game_'s _m_locations_ vector
     */
    Louka(const std::string &name, int idx);

    /*
     * @brief Virtual destructor.
     */
    virtual ~Louka();

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
};


#endif //SIMKUOND_LOUKA_H

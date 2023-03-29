#ifndef SIMKUOND_LOCATION_H
#define SIMKUOND_LOCATION_H
#include "../Entity.h"
#include "../Item.h"
#include "../misc/Key.h"
#include "../Player.h"
#include <vector>
#include <string>

class Location {
public:
    //! true if location has been already entered
    bool m_alreadyEntered;

    /**
     * @brief Constructs new _Location_
     *
     * Sets _m_name_, _m_alreadyEntered_ and _m_idx_.
     *
     * @param name  _string_ with name of location
     * @param idx   _int_ index of location in _Game_'s _m_locations_ vector
     */
    Location(const std::string &name, int idx);

    /**
     * @brief Virtual destructor.
     *
     * deletes each enemy from _m_enemies_ vector
     */
    virtual ~Location();

    /**
     * @brief Returns locations _m_name_.
     *
     * @return _string_ name of the location
     */
    std::string getName() const;

    /**
     * @brief Adds enemy to locations _m_enemies_.
     *
     * @param enemy _Entity*_ poiting to enemy to be added into vector
     */
    void addEnemy(Entity* enemy);

    /**
     * @brief Adds location to _m_neighbours_ vector.
     *
     * @param location _Location*_ pointing to location to be added into vector
     */
    void addNeighbour(Location* location);

    /**
     * @brief Deletes enemy from _m_enemies_ vector by it's index.
     *
     * @param idx _int_ index of entity to be removed from vector
     */
    void eraseEnemy(int &idx);

    /**
     * @brief Returns _m_neighbours_ vector.
     *
     * @return _vector<Location*>_  containing pointers to all neighbours.
     */
    std::vector<Location*> getNeighbours();

    /**
     * @brief Returns _m_enemies_ vector.
     *
     * @return _vector<Entity*>_  containing pointers to all enemies.
     */
    std::vector<Entity *> & getEnemies();

    /**
     * @brief Virtual method. Gets implemented by each derived class. Shows enter text defined in assets files.
     *
     */
    virtual void showEnterText() = 0;

    /**
     * @brief Virtual method. Gets implemented by each derived class. Checks whether user can enter this location.
     *
     * @param   inventory       _vector<Item*>_ players inventory so this method can check for items
     * @param   locations       _vector<Location*>_ so this method can check other locations for dead enemies
     * @return  true            if player can enter
     * @return  false           if player can't enter
     */
    virtual bool canEnter(std::vector<Item *> &inventory, std::vector<Location *> locations) = 0;

    /**
     * @brief Returns index of this location in _Game_'s _m_locations_ vector.
     *
     * @return _int_ index of this location in _Game_'s _m_locations_ vector
     */
    int getIdx() const;

    /**
     * @brief Saves location into save file passed in parameter.
     *
     * @param fileName _string_ with path to save file
     */
    void save(std::string fileName);
protected:
    //! name of location
    std::string m_name;
    //! vector with all enemies in this location
    std::vector<Entity*> m_enemies;
    //! vector with pointers to all neighbour locations
    std::vector<Location*> m_neighbourLocations;
    //! index of this location inside _Game_'s _m_locations_ vector
    int m_idx;
};

#endif //SIMKUOND_LOCATION_H

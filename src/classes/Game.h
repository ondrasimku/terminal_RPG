#ifndef SIMKUOND_GAME_H
#define SIMKUOND_GAME_H
#include <vector>
#include <string>
#include <set>

class Player;
class Location;
class Item;

class Game
{
public:
    /**
     * @brief sets _m_end_ to false, location count to 0 and _m_player_ to nullptr
     */
    Game();

    /**
     * @brief Deletes every location and _m_player_ to free memory.
     */
    ~Game();

    /**
     * @brief Shows main menu.
     *
     * Prompts user to pick one action from menu. User can start _newGame()_, _loadSave()_, _removeSave()_ or exit
     * the game
     */
    void mainMenu();
private:
    /**
     * @brief Starts new game. Adds all locations and enemies to each location.
     *
     * add new instances of Locations into m_locations vector. Adds multiple enemies
     * to each m_location. At the end calls enter(m_locations[0]) to enter the
     * starting location and calls gameLoop() method to start the main loop.
     */
    void newGame();

    /**
     * @brief Saves game into file.
     *
     * Prompts user to enter file name. Than calls _m_player->save_ to save player into the save file.
     * Calls _location->save_ for each location in _m_locations_ and saves it. Saves neighbours state
     * by saving index pairs of each neighbour locations from _m_neighbours_ set.
     */
    void saveGame();

    /**
     * @brief Load save from file.
     *
     * Iterates through save files. Prompts user to choose one save file. Reads player stats
     * from first line of save file using _readPlayer()_ method. Add all items from save
     * to inventory using _readInventory()_ method. Reads number of locations and index
     * of current location. Reads each location using _readLocation()_ method.
     */
    void loadSave();

    /**
     * @brief Removes chosen save file.
     *
     * Iterates through save files. Prompts user to pick one save file to be removed.
     * Returns to _mainMenu()_
     */
    void removeSave();

    /**
     * @brief Takes string stream to read player starts from.
     *
     * Reads all needed stats from stream to variables. Makes new Player instance with pointer
     * saved in _m_player_ member.
     *
     * @param   iss         _std::istringstream_ containing line with player stats
     * @return  _true_      if player has been loaded successfully
     * @return  _false_     if there was error in reading player stats
     */
    bool readPlayer(std::istringstream &iss);

    /**
     * @brief Reads inventory items from save file until "INVENTORY_END" is found.
     *
     * Reads each line containing item using _getline()_ and passes the line to _readItem()_ method, which
     * than handles the process of adding the right item.
     *
     * @param   file    _ifstream_ reference to save file
     * @param   line    _string_ reference to string used to read each line into
     * @return  _true_  if each item has been loaded successfully and "INVENTORY_END" was found
     * @return  _false_ if _readItem()_ method returned false meaning reading of the item failed
     */
    bool readInventory(std::ifstream &file, std::string &line);

    /**
     * @brief Checks which item to create by checking _itemStr_ string. Reads item stats from _iss_.
     *
     * Calls _m_player->inventoryAdd()_ method to add item to player's inventory
     *
     * @param   itemStr _string_ containing item type
     * @param   iss     _istringstream_ containing item stats
     * @return  _true_  if item has been successfully loaded
     * @return _false_  if reading of the item failed
     */
    bool readItem(std::string &itemStr, std::istringstream &iss);

    /**
     * @brief Za tuhle metodu se omlouvám a stydím se. Spaghetti coded reading of locations from
     * save file with hard coded location names.
     *
     * Reads each locations name and id in _m_locations_ vector. Adds newly created location into
     * the vector. Reads every enemy of the location with it's stats and adds each read enemy
     * into locations _m_enemies_ vector.
     *
     * @param   file    _ifstream_ reference to save file
     * @param   line    _string_ reference to string used to read each line into
     * @return  _true_  if loading of each location and enemy is successful
     * @return  _false_ if loading of any location or enemy fails
     */
    bool readLocations(std::ifstream & file, std::string & line);

    /**
     * @brief Reads weapon type from _type_ string and returns pointer to instance of read weapon
     *
     * @param   type        _string_ containing weapon type
     * @param   name        _string_ containing weapon name
     * @param   damage      _double_ containing weapon damage
     * @param   armorPen    _double_ containing weapon armor penetration
     * @return _nullptr_    if _type_ string doesn't contain any known weapon type ("nullptr" for example)
     * @return _Item*_      pointer to newly created weapon if the weapon was read successfully
     */
    Item* readWeapon(const std::string& type, const std::string& name, double damage, double armorPen);

    /**
     * @brief Main game loop with menu.
     *
     * This loop goes on until _m_end_ member is set to true. Calls _loopMenu()_ inside switch
     * to get user input.
     */
    void gameLoop();

    /**
     * @brief Get's called inside _gameLoop()_ method's switch.
     *
     * Shows main menu and prompts user to select which action to make next.
     *
     * @return  _int_   containing which action user picked
     */
    int loopMenu();


    /**
     *
     * @brief Adds _location_ into _m_locations_ vector. Increases _m_locationCount_ by 1.
     *
     * @param   location    _Location*_ pointing to location to be added
     */
    void addLocation(Location* location);

    /**
     *
     * @brief Adds two location indexes into _m_neighbours_ set.
     *
     * @param   idx1    _int_ to be added into neighbours set
     * @param   idx2    _int_ to be added into neighbours set
     */
    void addNeighbour(const int &idx1, const int &idx2);


    /**
     * @brief Enters passed location.
     *
     * Calls locations _canEnter()_ method. If method returned true, this method sets
     * _m_currentLocation_ to entered location. Calls locations _showEnterText()_.
     * Sets locations _m_alreadyEntered_ to true.
     *
     * @param   location    _Location*_ pointing to location which we want to enter
     */
    void enter(Location* location);

    /**
     * @brief Show travel menu.
     *
     * Reads all neighbour locations and prompts user to pick one location to travel into.
     * Calls _enter()_ method to enter the location.
     */
    void travel();

    /**
     * @brief Show each enemy which can be attacked in current location.
     *
     * Iterates through location's _m_enemies_ vector and prompts user to pick one enemy,
     * which will be attacked. Uses _Arena_ class _fight()_ method to make the fight happen.
     */
    void arena();

    /**
     * @brief Prints players stats and each item from his inventory.
     *
     * Calls _m_player->printInventory()_ method.
     */
    void inventory();

    /**
     * @brief Shows after death menu.
     *
     * Prompts user to either start a new game or load game from save file. Calls _newGame()_ or _loadSave()_ method
     * after clearing memory. (deleting _m_player_ and each location from _m_locations_ vector)
     */
    void playerDeath();

    //! pointer to player
    Player* m_player;
    //! vector containing pointer to each location
    std::vector<Location*> m_locations;
    //! pointer to current location
    Location* m_currentLocation;
    //! index of current location in _m_locations_ vector
    int m_currentLocationIdx;
    //! current count of locations
    int m_locationCount;
    //! set containing indexes of neighbour locations
    std::set<std::pair<int, int>> m_neighbours;
    //! bool to end main loop of the game and exit
    bool m_end;


};


#endif //SIMKUOND_GAME_H

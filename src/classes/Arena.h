#ifndef SIMKUOND_ARENA_H
#define SIMKUOND_ARENA_H
#include "Entity.h"
#include "Player.h"
#include "Weapon.h"

class Arena {
public:
    /**
     * @brief Makes fight between _player_ and _entity_
     *
     * Player atacks first. Fight goes on, until someone dies. Method checks, which weapon
     * is being used as primary. If primary is BOW, player shoots between 1 and 5 arrows before
     * entity can attack player. _player_ can use only secondary weapon afterwards. If entity dies
     * method calls _deathAction()_ method of entity.
     *
     * @param   player      _Player_ instance of player
     * @param   entity      _Entity_ instance of entity to attack
     * @return  true        if player won
     * @return  false       if player lost
     */
    static bool fight(Player & player, Entity & entity );

    /**
     * @brief Prints stats of _player_ and _entity_ after each exchange of attacks.
     *
     * @param player    _Player_ to be printed
     * @param entity    _Entity_ to be printed
     */
    static void printStats(Player & player, Entity & entity );

    /**
     * @brief Shows battle menu to player.
     *
     * Player can either continue in fight, change weapons, use potions or make the rest of the fight simulate itself.
     *
     * @param player    _Player_ for using potions and changing weapons
     * @param simulate  _bool*_ pointing to bool which defines if fight is being sumulated or not
     */
    static void playerMenu(Player & player, bool *simulate);

};

#endif //SIMKUOND_ARENA_H

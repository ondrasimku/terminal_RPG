#ifndef SIMKUOND_STRENGTH_H
#define SIMKUOND_STRENGTH_H
#include "../Item.h"
#include <string>

class StrengthPotion : public Item {
public:
    /**
     * @brief Constructs new instance of _StrengthPotion_
     *
     * @param potionPower _double_ power of potion
     */
    explicit StrengthPotion(double potionPower);

    /**
     * @brief Virtual destructor.
     */
    virtual ~StrengthPotion();

    /**
     * @brief prints itself to _ostream_
     *
     * Gets called by base's overloaded << operator.
     *
     * @param os _ostream_ to print itself into
     */
    virtual void print(std::ostream & os) override;

    /**
     * @brief Adds strength to player.
     *
     * @param playerHealth          _double*_ pointing to players _m_strength_
     * @param playerPotionBoost     _double*_ pointing to players _m_potionBoost_
     */
    void use(double* playerStrength, double* playerPotionBoost );

    /**
     * @brief Saves StrengthPotion to file.
     *
     * @param output _fstream_ to write into
     */
    virtual void save(std::fstream &output) override;
private:
    //! power of strength
    double m_power;
};

#endif //SIMKUOND_STRENGTH_H

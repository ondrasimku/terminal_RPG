#ifndef SIMKUOND_HEALTH_H
#define SIMKUOND_HEALTH_H

#include "../Item.h"
#include <string>

class HealthPotion : public Item {
public:
    /**
     * @brief Constructs new instance of _HealthPotion_
     *
     * @param potionPower _double_ power of potion
     */
    explicit HealthPotion(double potionPower);

    /**
     * @brief Virtual destructor.
     */
    virtual ~HealthPotion();

    /**
     * @brief prints itself to _ostream_
     *
     * Gets called by base's overloaded << operator.
     *
     * @param os _ostream_ to print itself into
     */
    virtual void print(std::ostream & os) override;

    /**
     * @brief Adds health to player.
     *
     * @param playerHealth _int*_ pointing to player _m_health_
     */
    void use(int* playerHealth );

    /**
     * @brief Saves HealthPotion to file.
     *
     * @param output _fstream_ to write into
     */
    virtual void save(std::fstream &output) override;
private:
    //! power of health potion
    double m_power;
};

#endif //SIMKUOND_HEALTH_H

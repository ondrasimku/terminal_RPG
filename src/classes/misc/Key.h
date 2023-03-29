#ifndef SIMKUOND_KEY_H
#define SIMKUOND_KEY_H
#include "../Item.h"
#include <string>
#include <fstream>

class Key : public Item {
public:
    /**
     * @briefConstructs new instance of _Key_
     * @param name      _string_ with name of key
     * @param opens     _string_ with name of location this key opens
     */
    Key(const std::string & name, const std::string & opens);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Key();

    /**
     * @brief Returns string with name of location this key opens.
     *
     * @return _string_ with name of location this key opens.
     */
    std::string getOpens() const;

    /**
     * @brief prints itself to _ostream_
     *
     * Gets called by base's overloaded << operator.
     *
     * @param os _ostream_ to print itself into
     */
    virtual void print(std::ostream & os);

    /**
     * @brief Saves Key to file.
     *
     * @param output _fstream_ to write into
     */
    virtual void save(std::fstream &output) override;
private:
    //! name of location this key opens
    std::string m_opens;

};

#endif //SIMKUOND_KEY_H

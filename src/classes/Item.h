#ifndef SIMKUOND_ITEM_H
#define SIMKUOND_ITEM_H
#include <string>
#include <iostream>
#include <ostream>


class Item
{
public:
    //! Type of item
    enum Type { SWORD, AXE, KNIFE, BOW, HEALTH_POTION, STRENGTH_POTION, MISC};


    /**
     * @brief Constructs new _Item_ instance. Get's called when constructing derived classes.
     *
     * Sets _m_name_ and _m_type_
     *
     * @param type  _Type_ of item
     * @param name  _string_ name of item
     */
    Item(const Type & type, const std::string & name);

    /**
     * @brief Virtual method implemented inside each child.
     *
     * Gets called by overloaded << operator
     *
     * @param os _ostream_ to print itself into
     */
    virtual void print(std::ostream & os) = 0;

    /**
     * @brief Overloaded << operator
     *
     * Calls _print()_ method of _item_.
     *
     * @param   os          _ostream_ to print _item_ into
     * @param   item        _Item_ to print
     * @return _ostream_    with printed _item_
     */
    friend std::ostream & operator << (std::ostream & os, Item & item);

    /**
     * @brief Virtual destructor
     */
    virtual ~Item();

    /**
     * @brief Returns item's name
     *
     * @return _string_ with item's _m_name_
     */
    const std::string & getItemName() const { return m_name; }

    /**
     * @brief Returns item's type
     *
     * @return _Type_ with item's _m_type_
     */
    const Type & getItemType() const { return m_type; }

    /**
     * @brief Virtual method implemented inside each child.
     *
     * Save item into _output_ file.
     *
     * @param os _ostream_ to print itself into
     */
    virtual void save(std::fstream &output) = 0;

protected:
    //! name of item
    std::string m_name;
    //! type of item
    Type        m_type;

};

#endif //SIMKUOND_ITEM_H

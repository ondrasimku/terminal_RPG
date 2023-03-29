#include "classes/Item.h"

Item::Item(const Type & type, const std::string &name)
{
    m_name = name;
    m_type = type;
}

Item::~Item() {

}

std::ostream &operator<<(std::ostream &os, Item &item) {
    item.print(os);
    return os;
}

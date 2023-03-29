#include "Hrad.h"
#include "../../Console.h"

Hrad::Hrad(const std::string &name, int idx) : Location(name, idx) {}

Hrad::~Hrad() {

}

void Hrad::showEnterText() {
    Console::clear();
    Console::printFile("texts/Hrad/OnEnter.txt");
}

bool Hrad::canEnter(std::vector<Item *> & inventory, std::vector<Location *> locations) {
    for(auto & item : inventory)
    {
        if(item->getItemType() == Item::MISC)
        {
            Key* klic = dynamic_cast<Key*>(item);
            if(klic->getOpens() == "Komnata")
            {
                return true;
            }
        }
    }
    std::cout << "Musíš prvně zabít Ragnaroka" << std::endl;
    return false;
}
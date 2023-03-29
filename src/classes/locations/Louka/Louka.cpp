#include "Louka.h"
#include "../../Console.h"

Louka::Louka(const std::string &name, int idx) : Location(name, idx) {}

Louka::~Louka() {

}

void Louka::showEnterText() {
    Console::clear();
    if(!m_enemies.empty())
        Console::printFile("texts/Louka/OnEnter.txt");
    else
        std::cout << "Tady jsi už bojoval s Ragnarokem..." << std::endl;
}

bool Louka::canEnter(std::vector<Item *> & inventory, std::vector<Location *> locations) {
    for(auto & location : locations)
    {
        if(location->getName() == "Temný les")
        {
            if(!location->getEnemies().empty())
            {
                std::cout << "Nelze projít lesem, pořád je tam moc nepřátel" << std::endl;
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
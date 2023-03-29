#include "Eriador.h"
#include "../../Console.h"
#include "../../potions/Strength.h"

Eriador::Eriador(const std::string &name, int idx) : Location(name, idx) {}

Eriador::~Eriador() {

}

void Eriador::showEnterText() {
    Console::clear();
    Console::printFile("texts/Eriador/OnEnter.txt");
    if(!m_alreadyEntered)
        std::cout << "\nCestou do Eriadoru jsi našel jeden lektvar síly!" << std::endl;
}

bool Eriador::canEnter(std::vector<Item *> & inventory, std::vector<Location *> locations) {
    for(auto & location : locations)
    {
        if(location->getName() == "cesta do Eriadoru")
        {
            if(location->getEnemies().empty())
            {
                if(!m_alreadyEntered)
                    inventory.push_back(new StrengthPotion(40.0));
                return true;
            }
        }
    }

    std::cout << "Musíš zabít příšery v cestě!" << std::endl;
    return false;
}
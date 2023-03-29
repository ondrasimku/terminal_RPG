#include "Komnata.h"
#include "../../Console.h"
#include "../../Game.h"

Komnata::Komnata(const std::string &name, int idx, bool* endGame) : Location(name, idx) {
    m_endGame = endGame;
}

Komnata::~Komnata() {

}

void Komnata::showEnterText() {
    Console::clear();
    Console::printFile("texts/Komnata/OnEnter.txt");
    if(m_killedRagnarok)
    {
        Console::printFile("texts/Komnata/PrincessDeath.txt");
        *m_endGame = true;
    }
    else
    {
        Console::printFile("texts/Komnata/PrincessAlive.txt");
        *m_endGame = true;
    }
}

bool Komnata::canEnter(std::vector<Item *> & inventory, std::vector<Location *> locations) {
    bool klic = false;
    bool hrad = false;
    bool mec = false;
    for(auto & item : inventory)
    {
        if(item->getItemType() == Item::MISC)
        {
            Key* key = dynamic_cast<Key*>(item);
            if(key->getOpens() == "Komnata")
            {
                klic = true;
            }
        }
        else if(item->getItemName() == "Ragnarokův_meč")
        {
            mec = true;
        }
    }

    for(auto & location : locations)
    {
        if(location->getName() == "Hrad")
        {
            if(location->getEnemies().empty())
            {
                hrad = true;
                break;
            }
        }
    }

    if(hrad && klic)
    {
        if(mec)
            m_killedRagnarok = true;
        else
            m_killedRagnarok = false;
        return true;
    }
    else
    {
        std::cout << "Musíš prvně zabít všechny strážce komnaty" << std::endl;
        return false;
    }
}
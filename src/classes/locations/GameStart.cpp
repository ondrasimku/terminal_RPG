#include "GameStart.h"
#include "../Console.h"

GameStart::GameStart(const std::string &name, int idx) : Location(name, idx) {

}

GameStart::~GameStart() {

}

void GameStart::showEnterText() {
    Console::clear();
    if(!m_alreadyEntered)
    {
        Console::printFile("texts/GameStart/OnEnter.txt");
    }
    else
    {
        std::cout << "Vrátil jsi se na cestu do Eriadoru" << std::endl;
    }
}

bool GameStart::canEnter(std::vector<Item *> &inventory, std::vector<Location *> locations) {
    return true;
}

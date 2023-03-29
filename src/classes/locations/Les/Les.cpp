#include "Les.h"
#include "../../Console.h"

Les::Les(const std::string &name, int idx) : Location(name, idx) {}

Les::~Les() {

}

void Les::showEnterText() {
    Console::clear();
    Console::printFile("texts/Les/OnEnter.txt");
}

bool Les::canEnter(std::vector<Item *> & inventory, std::vector<Location *> locations) {
    return true;
}
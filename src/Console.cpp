#include "classes/Console.h"

void Console::clear() {
#if defined _WIN32
    clrscr();
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::cout<< u8"\033[2J\033[1;1H";
#endif
}

void Console::initRand() {
    srand((unsigned) time(0));
}

void Console::printFile(const std::string &source) {
    std::ifstream file;
    file.open("assets/" + source);
    if(!file)
    {
        std::cerr << "Failed opening the file " << source << " in Console::printFile" << std::endl;
    }
    else
    {
        std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << text << std::endl;
    }
    file.close();

}

int Console::genRand(int from, int to) {
    return rand() % to + from;
}

Console::Console() {}

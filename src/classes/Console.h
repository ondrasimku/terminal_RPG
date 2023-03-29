#ifndef SIMKUOND_CONSOLE_H
#define SIMKUOND_CONSOLE_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>

#if defined _WIN32
#include <conio.h>
#endif


class Console
{
public:
    /**
     * @brief Clears terminal.
     */
    static void clear();

    /**
     * @brief Initializes seed for generating pseudo random numbers.
     */
    static void initRand();

    /**
     * @brief Generates random int in range _from_ _to_
     *
     * @param   from      _int_ lower bound
     * @param   to        _int_ higher bound
     * @return  _int_     generated number
     */
    static int genRand(int from, int to);

    /**
     * @brief Prints file from _source_
     *
     * @param source _string_ with file path
     */
    static void printFile(const std::string & source);
private:
    Console();
};

#endif //SIMKUOND_CONSOLE_H

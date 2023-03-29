#include "Location.h"
#include "../Console.h"

Location::Location(const std::string &name, int idx) {
    m_name = name;
    m_alreadyEntered = false;
    m_idx = idx;
}

Location::~Location() {
    for(auto & enemy : m_enemies)
        delete enemy;
}

void Location::addEnemy(Entity* enemy) {
    m_enemies.push_back(enemy);
}

void Location::addNeighbour(Location* location) {
    m_neighbourLocations.push_back(location);
}

std::vector<Location *> Location::getNeighbours() {
    return m_neighbourLocations;
}

std::string Location::getName() const {
    return m_name;
}

std::vector<Entity *> & Location::getEnemies() {
    return m_enemies;
}

void Location::eraseEnemy(int &idx) {
    delete m_enemies[idx];
    m_enemies.erase(m_enemies.begin()+idx);
}

int Location::getIdx() const {
    return m_idx;
}

void Location::save(std::string fileName) {
    std::fstream saveFile;
    saveFile.open("examples/saves/"+fileName, std::ios::out | std::ios::app);
    if(!saveFile)
    {
        std::cerr << "Error opening save file" << std::endl;
        saveFile.close();
        return;
    }
    saveFile << "LOCATION " << m_idx << " " << m_alreadyEntered << std::endl;
    saveFile << m_name << std::endl;

    for(auto & enemy : m_enemies)
        enemy->save(saveFile);

    saveFile << "ENEMY_END" << std::endl;
    saveFile.close();
}

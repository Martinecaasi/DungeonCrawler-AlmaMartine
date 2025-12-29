#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <string>
#include <vector>
#include <fstream>

#include "Room.hpp"
#include "Character.hpp"
#include "Item.hpp"
#include "Monster.hpp"

class Dungeon {
private:
    Room* roomsHead;
    Room* startRoom;

    std::vector<Character*> characters;
    std::vector<std::string> commands;

    Room* findRoom(const std::string& name) const;
    Character* findCharacter(const std::string& name) const;

    void handleCreate(const std::vector<std::string>& tokens);
    void handleConnect(const std::vector<std::string>& tokens);
    void handlePlace(const std::vector<std::string>& tokens);
    void handleSetStart(const std::vector<std::string>& tokens);
    void handleEnter(const std::vector<std::string>& tokens);
    void handleMove(const std::vector<std::string>& tokens);
    void handleFight(const std::vector<std::string>& tokens);
    void handlePickup(const std::vector<std::string>& tokens);

public:
    Dungeon();
    ~Dungeon();

    void loadFromFile(const std::string& filename);
    void executeCommands();
    void outputFinalState(const std::string& filename) const;
};

#endif
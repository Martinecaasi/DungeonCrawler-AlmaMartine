#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <unordered_set>

#include "Item.hpp"
#include "Monster.hpp"

class Room {
private:
    std::string name;

    Room* next;

    Room* north;
    Room* south;
    Room* east;
    Room* west;

    std::vector<Item*> items;
    std::vector<Monster*> monsters;

private:
    static std::string normalizeDir(const std::string& dir);
    static std::string oppositeDir(const std::string& dir);

    Room* getByDir(const std::string& dir) const;
    void setByDir(const std::string& dir, Room* neighbor);

    static bool reachable(Room* start, Room* target, std::unordered_set<Room*>& visited);

public:
    explicit Room(const std::string& roomName);
    ~Room();

    // Linked list helpers
    Room* getNext() const;
    void setNext(Room* n);

    // Basics
    const std::string& getName() const;

    // Map connections
    bool connect(Room* other, const std::string& direction);

    Room* getNeighbor(const std::string& direction) const;

    // Items
    void addItem(Item* item);
    bool hasItem(const std::string& itemName) const;
    Item* takeItem(const std::string& itemName);

    const std::vector<Item*>& getItems() const;

    // Monsters
    void addMonster(Monster* monster);
    bool hasMonster(const std::string& monsterName) const;
    Monster* getMonster(const std::string& monsterName) const;
    bool removeMonster(const std::string& monsterName);

    const std::vector<Monster*>& getMonsters() const;
};

#endif
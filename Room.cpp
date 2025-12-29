#include "Room.hpp"
#include <algorithm>
#include <cctype>

Room::Room(const std::string& roomName)
    : name(roomName),
      next(nullptr),
      north(nullptr), south(nullptr), east(nullptr), west(nullptr) {}

Room::~Room() {
    for (Item* it : items) {
        delete it;
    }
    items.clear();

    for (Monster* m : monsters) {
        delete m;
    }
    monsters.clear();
}

// ---------- Linked List ----------
Room* Room::getNext() const {
    return next;
}

void Room::setNext(Room* n) {
    next = n;
}

// ---------- Basics ----------
const std::string& Room::getName() const {
    return name;
}

// ---------- Direction Helpers ----------
std::string Room::normalizeDir(const std::string& dir) {
    std::string d = dir;
    for (char& c : d) c = (char)std::tolower((unsigned char)c);

    if (d == "n") return "north";
    if (d == "s") return "south";
    if (d == "e") return "east";
    if (d == "w") return "west";

    return d;
}

std::string Room::oppositeDir(const std::string& dir) {
    const std::string d = normalizeDir(dir);
    if (d == "north") return "south";
    if (d == "south") return "north";
    if (d == "east")  return "west";
    if (d == "west")  return "east";
    return "";
}

Room* Room::getByDir(const std::string& dir) const {
    const std::string d = normalizeDir(dir);
    if (d == "north") return north;
    if (d == "south") return south;
    if (d == "east")  return east;
    if (d == "west")  return west;
    return nullptr;
}

void Room::setByDir(const std::string& dir, Room* neighbor) {
    const std::string d = normalizeDir(dir);
    if (d == "north") north = neighbor;
    else if (d == "south") south = neighbor;
    else if (d == "east") east = neighbor;
    else if (d == "west") west = neighbor;
}

// ---------- Cycle Check ----------
bool Room::reachable(Room* start, Room* target, std::unordered_set<Room*>& visited) {
    if (!start) return false;
    if (start == target) return true;
    if (visited.count(start)) return false;

    visited.insert(start);

    Room* nbs[4] = { start->north, start->south, start->east, start->west };
    for (Room* nb : nbs) {
        if (reachable(nb, target, visited)) return true;
    }
    return false;
}

// ---------- Connections ----------
bool Room::connect(Room* other, const std::string& direction) {
    if (!other) return false;

    const std::string dir = normalizeDir(direction);
    const std::string opp = oppositeDir(dir);
    if (opp.empty()) return false;

    if (getByDir(dir) != nullptr) return false;

    if (north == other || south == other || east == other || west == other) return false;

    {
        std::unordered_set<Room*> visited;
        if (reachable(other, this, visited)) {
            return false;
        }
    }

    // Connect both ways (bidirectional)
    setByDir(dir, other);
    if (other->getByDir(opp) != nullptr) {
        setByDir(dir, nullptr);
        return false;
    }
    other->setByDir(opp, this);

    return true;
}

Room* Room::getNeighbor(const std::string& direction) const {
    return getByDir(direction);
}

// ---------- Items ----------
void Room::addItem(Item* item) {
    if (!item) return;
    items.push_back(item);
}

bool Room::hasItem(const std::string& itemName) const {
    return std::any_of(items.begin(), items.end(), [&](Item* it) {
        return it && it->getName() == itemName;
    });
}

Item* Room::takeItem(const std::string& itemName) {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i] && items[i]->getName() == itemName) {
            Item* picked = items[i];
            items.erase(items.begin() + (long)i);
            return picked;
        }
    }
    return nullptr;
}

const std::vector<Item*>& Room::getItems() const {
    return items;
}

// ---------- Monsters ----------
void Room::addMonster(Monster* monster) {
    if (!monster) return;
    monsters.push_back(monster);
}

bool Room::hasMonster(const std::string& monsterName) const {
    return std::any_of(monsters.begin(), monsters.end(), [&](Monster* m) {
        return m && m->getName() == monsterName;
    });
}

Monster* Room::getMonster(const std::string& monsterName) const {
    for (Monster* m : monsters) {
        if (m && m->getName() == monsterName) return m;
    }
    return nullptr;
}

bool Room::removeMonster(const std::string& monsterName) {
    for (size_t i = 0; i < monsters.size(); ++i) {
        if (monsters[i] && monsters[i]->getName() == monsterName) {
            delete monsters[i];
            monsters.erase(monsters.begin() + (long)i);
            return true;
        }
    }
    return false;
}

const std::vector<Monster*>& Room::getMonsters() const {
    return monsters;
}
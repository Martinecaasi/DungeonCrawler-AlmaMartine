#include "Dungeon.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

Dungeon::Dungeon() {
    roomsHead = nullptr;
    startRoom = nullptr;
}

Dungeon::~Dungeon() {
    while (roomsHead) {
        Room* temp = roomsHead;
        roomsHead = roomsHead->getNext();
        delete temp;
    }

    for (Character* c : characters)
        delete c;
}

void Dungeon::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;

    while (getline(in, line)) {
        if (!line.empty())
            commands.push_back(line);
    }
}

void Dungeon::executeCommands() {
    for (const std::string& cmd : commands) {
        std::stringstream ss(cmd);
        std::vector<std::string> tokens;
        std::string word;

        while (ss >> word)
            tokens.push_back(word);

        if (tokens.empty()) continue;

        if (tokens[0] == "create")
            handleCreate(tokens);
        else if (tokens[0] == "connect")
            handleConnect(tokens);
        else if (tokens[0] == "place")
            handlePlace(tokens);
        else if (tokens[0] == "Set")
            handleSetStart(tokens);
        else if (tokens[0] == "Enter")
            handleEnter(tokens);
        else if (tokens[0] == "Move")
            handleMove(tokens);
        else if (tokens[0] == "Fight")
            handleFight(tokens);
        else if (tokens[0] == "PickUp")
            handlePickup(tokens);
    }
}

Room* Dungeon::findRoom(const std::string& name) const {
    Room* curr = roomsHead;
    while (curr) {
        if (curr->getName() == name)
            return curr;
        curr = curr->getNext();
    }
    return nullptr;
}

Character* Dungeon::findCharacter(const std::string& name) const {
    for (Character* c : characters)
        if (c->getName() == name)
            return c;
    return nullptr;
}


void Dungeon::handleCreate(const std::vector<std::string>& t) {
    if (t[1] == "room") {
        Room* r = new Room(t[2]);
        r->setNext(roomsHead);
        roomsHead = r;
    }
    else {
        Character* c = new Character(t[1], t[2]);
        characters.push_back(c);
    }
}

void Dungeon::handleConnect(const std::vector<std::string>& t) {
    Room* a = findRoom(t[1]);
    Room* b = findRoom(t[2]);
    if (!a || !b) return;
    a->connect(b, t[3]);
}

void Dungeon::handlePlace(const std::vector<std::string>& t) {
    if (t[1] == "monster") {
        Room* r = findRoom(t[3]);
        if (!r) return;
        Monster* m = new Monster(t[2], stoi(t[4]), stoi(t[5]), stoi(t[6]));
        r->addMonster(m);
    }
    else {
        Room* r = findRoom(t[2]);
        if (!r) return;
        Item* i = new Item(t[1], stoi(t[3]), stoi(t[4]), stoi(t[5]));
        r->addItem(i);
    }
}

void Dungeon::handleSetStart(const std::vector<std::string>& t) {
    startRoom = findRoom(t[2]);
}

void Dungeon::handleEnter(const std::vector<std::string>& t) {
    if (!startRoom) return;
    Character* c = findCharacter(t[2]);
    if (c)
        c->setCurrentRoom(startRoom);
}

void Dungeon::handleMove(const std::vector<std::string>& t) {
    Character* c = findCharacter(t[1]);
    if (!c) return;
    c->move(t[2]);
}

void Dungeon::handleFight(const std::vector<std::string>& t) {
    Character* c = findCharacter(t[1]);
    if (!c) return;
    c->fight(t[2]);
}

void Dungeon::handlePickup(const std::vector<std::string>& t) {
    Character* c = findCharacter(t[1]);
    if (!c) return;
    c->pickUp(t[2]);
}


void Dungeon::outputFinalState(const std::string& filename) const {
    std::ofstream out(filename);
    for (Character* c : characters)
        out << c->getStatus() << std::endl;
}
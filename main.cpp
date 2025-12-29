#include "Dungeon.hpp"

int main() {

    Dungeon game;
    game.loadFromFile("input.txt");
    game.executeCommands();
    game.outputFinalState("output.txt");

    return 0;
}
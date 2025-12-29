#include "Dungeon.hpp"

int main() {

    Dungeon game;
    game.loadFromFile("Input.txt");
    game.executeCommands();
    game.outputFinalState("Output.txt");

    return 0;
}
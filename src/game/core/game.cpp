#include "game.h"

#include <iostream>
#include <string>

JupThrCore::Game::Game(TerminalManager& term): term(term), counter(1) {}

void JupThrCore::Game::doStateCalc() {
    this->counter++;

    this->term.write("Yippie: " + std::to_string(counter));
}

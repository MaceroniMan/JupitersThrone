#include "game.h"

#include <lib/luacpp/LuaCpp.hpp>

JupThrCore::Game::Game(TerminalManager& term, JupThrData::Player& playerData): term(term), player(playerData) {
    this->subTimeCounter = 0;
}

void JupThrCore::Game::doStateCalc() {
    this->subTimeCounter++;
    if (this->subTimeCounter == (1000/JupThrGlobal::LOOP_TIME_MS)) {
        this->subTimeCounter = 0;
        this->player.secondsSinceStart++;
    }
}

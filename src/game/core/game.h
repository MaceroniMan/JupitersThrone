#ifndef GAME_H
#define GAME_H

#include "src/engine/terminalmanager.h"
#include "src/game/io/player.h"
#include "src/game/constants.h"

namespace JupThrCore {
class Game;
} // namespace JupThrCore

class JupThrCore::Game
{
public:
    Game(TerminalManager&, JupThrData::Player&);

    void doStateCalc();

private:
    void updateScreen();


    TerminalManager &term;
    JupThrData::Player &player;

    int subTimeCounter;
};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H

#include "src/engine/terminalmanager.h"

namespace JupThrCore {
class Game;
} // namespace JupThrCore

class JupThrCore::Game
{
public:
    Game(TerminalManager&);

    void doStateCalc();

private:
    TerminalManager &term;

    int counter;
};

#endif // GAME_H

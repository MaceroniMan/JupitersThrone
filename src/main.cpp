#include "src/engine/consolewindow.h"
#include "src/engine/terminalmanager.h"
#include "src/game/utils/debug.h"
#include "src/game/utils/colors.h"
#include "src/game/core/game.h"
#include "src/game/io/player.h"
#include "src/game/constants.h"

#include <lib/luacpp/LuaCpp.hpp>

#include <QApplication>
#include <QTimer>

#include <iostream>

using namespace LuaCpp;

int main(int argc, char *argv[])
{
    std::cout << "foobar \n";

    LuaContext ctx;

    std::shared_ptr<Engine::LuaTString> str = std::make_shared<Engine::LuaTString>("world from C++!");

    ctx.AddGlobalVariable("world", str);
    ctx.CompileString("test", "print('Hello '..world); world = 'world from lua!'");
    try {
        ctx.Run("test");
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << '\n';
    }

    std::cout << "Hello " << str->getValue() << "\n";

    // foobar

    JupThrUtils::log("startup", "Jupiters Throne v0.0.1");
    QApplication a(argc, argv);

    JupThrUtils::log("startup", "starting windows");
    ConsoleWindow window;
    TerminalManager term(window);

    window.show();
    term.calculateTerminalDimentions();

    JupThrUtils::log("startup", "starting game loop");

    JupThrData::Player save;
    JupThrCore::Game game(term, save);

    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [&game](){
        game.doStateCalc();
    });
    timer->start(JupThrGlobal::LOOP_TIME_MS);

    term.write(JupThrGraphics::Colors::renderToHtml(JupThrGraphics::Colors::Bold("This is a red test")));

    QObject::connect(&term, &TerminalManager::commandClicked, [&term]( const std::string value ) { term.write(value); });
    QObject::connect(&term, &TerminalManager::enterPressed, [&term]( const std::string value ) { JupThrUtils::log("enter pressed"); term.write(value); });

    QObject::connect(&term, &TerminalManager::escapePressed, [&term]() {
        JupThrUtils::log(std::to_string(term.getTerminalWidth()));
        term.write(std::string(term.getTerminalWidth(), '.'));
    });

    return a.exec();
}

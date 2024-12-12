#ifndef TERMINALMANAGER_H
#define TERMINALMANAGER_H

#include "consolewindow.h"

#include <QMainWindow>
#include <QObject>
#include <vector>

class TerminalManager : public QObject {
    Q_OBJECT

public:
    TerminalManager(ConsoleWindow *window);

    /* Overwrite the content on the screen
     *
     * NOTE: does not do any handling of HTML escape codes
     */
    void write(std::string text);
    // Overwrite the content of the command bar
    void setCommand(std::string command);

    int getTerminalWidth();
    int getTerminalHeight();

public slots:
    void anyKeyPressed(QKeyEvent* content);
    void linkClicked(QString content);
    // Will calculate how many characters the terminal can hold
    void calculateTerminalDimentions();

signals:
    // When the enter key is pressed
    void enterPressed(std::string input);
    // When the tab key is pressed
    void tabPressed(std::string input);
    // When the escape key is pressed
    void escapePressed();
    // When a command (link) is clicked
    void commandClicked(std::string content);

private:
    // Will turn special shortcuts to their HTML equivilant
    QString prettyPrint(QString text);

    ConsoleWindow *window;

    std::vector<QChar> user_input;
    int user_input_pos = 0;

    int terminal_width;
    int terminal_height;
};

#endif // TERMINALMANAGER_H

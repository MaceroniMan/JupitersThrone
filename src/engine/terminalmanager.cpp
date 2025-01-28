#include "terminalmanager.h"

#include <QMainWindow>
#include <QKeyEvent>

TerminalManager::TerminalManager(ConsoleWindow &window): window(window) {

    // connect keyboard and link events through
    QObject::connect(&window, &ConsoleWindow::screenKeyPressed, this, &TerminalManager::anyKeyPressed);
    QObject::connect(&window, &ConsoleWindow::screenLinkClicked, this, &TerminalManager::linkClicked);
    QObject::connect(&window, &ConsoleWindow::screenResized, this, &TerminalManager::calculateTerminalDimentions);
}

// PROPERTIES
int TerminalManager::getTerminalWidth() {
    return this->terminal_width;
}

int TerminalManager::getTerminalHeight() {
    return this->terminal_height;
}

// SLOTS
void TerminalManager::linkClicked(QString content) {
    emit commandClicked(content.toStdString());
}

void TerminalManager::calculateTerminalDimentions() {
    QFont font = this->window.getFont();
    // a simple one character string
    QString str = QString::fromStdString(" ");

    QFontMetrics fm(font);

    // estimate the font size
    // should work *most* of the time
    // using monospace fonts
    int line_height = fm.height();
    int char_width = fm.horizontalAdvance(str);

    QSize output_label_size = this->window.getOutputLabelSize();

    int output_label_width = output_label_size.width();
    int output_label_height = output_label_size.height();

    this->terminal_width = std::floor(output_label_width/char_width);
    this->terminal_height = std::floor(output_label_height/line_height);
}

void TerminalManager::anyKeyPressed(QKeyEvent* event) {
    int key = event->key();
    auto offset = this->user_input.begin() + this->user_input_pos;

    QString qstr;

    switch (key) {
    case (Qt::Key_Backspace):
        if (this->user_input_pos > 0) {
            this->user_input.erase(offset-1);
            this->user_input_pos--;
        }
        break;

    case (Qt::Key_Delete):
        if (this->user_input_pos < this->user_input.size()) {
            this->user_input.erase(offset);
        }
        break;

    case (Qt::Key_Escape):
        emit this->escapePressed();
        break;

    case (Qt::Key_Tab):
        qstr = QString(this->user_input.data(), this->user_input.size());
        emit this->tabPressed(qstr.toStdString());
        break;

    case (Qt::Key_Enter):
    case (Qt::Key_Return):
        qstr = QString(this->user_input.data(), this->user_input.size());
        this->user_input.clear();
        this->user_input_pos = 0;
        emit this->enterPressed(qstr.toStdString());
        break;

    case (Qt::Key_Left):
        if (this->user_input_pos > 0) {
            this->user_input_pos--;
        }
        break;
    case (Qt::Key_Right):
        if (this->user_input_pos < this->user_input.size()) {
            this->user_input_pos++;
        }
        break;

    case (Qt::Key_Up):
        break;
    case (Qt::Key_Down):
        break;

    default:
        if(event->text().toStdString() != "") {
            if (event->modifiers() == Qt::ControlModifier) {
                QChar chr = event->text().at(0);
                if (chr == '=') { // scale window up
                    double newScale = this->window.getScale()+0.2;
                    this->window.setScale(newScale);
                    this->window.scaleApplication();
                } else if (chr == '-') { // scale window down
                    double newScale = this->window.getScale()-0.2;
                    if (newScale > .5) {
                        this->window.setScale(newScale);
                    }
                    this->window.scaleApplication();
                }
            }

            if (event->modifiers() == Qt::NoModifier || event->modifiers() == Qt::ShiftModifier) {
                QChar chr = event->text().at(0);
                this->user_input.insert(offset, chr);

                this->user_input_pos++;
            }
        }
    }

    QString cmd_text = QString(this->user_input.data(), this->user_input.size());

    // split the text into before cursor and the character on the cursor
    QString start = cmd_text.left(this->user_input_pos);
    QString mid_char = cmd_text.mid(this->user_input_pos, 1);

    // split off any text after the cursor
    auto end_offset = cmd_text.size()-this->user_input_pos-1;
    QString end;
    if (end_offset < 0) {
        end = "";
    } else {
        end = cmd_text.last(end_offset);
    }

    // if the cursor is at the end, make it a space for
    // better formatting
    if (mid_char.size() == 0) {
        mid_char = " ";
    }

    // escape the sequences
    start = start.toHtmlEscaped().replace(" ", "&nbsp;");
    mid_char = mid_char.toHtmlEscaped().replace(" ", "&nbsp;");
    end = end.toHtmlEscaped().replace(" ", "&nbsp;");

    this->window.setCommandText(start + "<span style=\"background-color:darkgrey;\">" + mid_char + "</span>" + end);
}

// FUNCTIONS
void TerminalManager::write(std::string text) {
    QString screen_text = QString::fromStdString(text);

    // add the <html> to force qt to render as html text
    this->window.setOutputText("<html>" + screen_text + "</html>");
}

void TerminalManager::setCommand(std::string command) {
    QString qstr = QString::fromStdString(command);

    this->user_input = std::vector<QChar>(qstr.begin(), qstr.end());
    this->user_input_pos = command.length();
}

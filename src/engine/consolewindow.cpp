#include "./ui_consolewindow.h"
#include "consolewindow.h"

#include <QMainWindow>

ConsoleWindow::ConsoleWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ConsoleWindow), scale_factor(1)
{
    ui->setupUi(this);

    this->scaleApplication();

    // translate the linkActivated signal to the screenLinkClicked signal
    QObject::connect(ui->OutputLabel, &QLabel::linkActivated, this, &ConsoleWindow::screenLinkClicked);
}

ConsoleWindow::~ConsoleWindow()
{
    delete this->ui;
}

// PROPERTIES
QFont ConsoleWindow::getFont() {
    QFont font = this->ui->CommandLabel->font();
    return font;
}

QSize ConsoleWindow::getCommandLabelSize() {
    return this->ui->CommandLabel->size();
}

QSize ConsoleWindow::getOutputLabelSize() {
    return this->ui->OutputLabel->size();
}

double ConsoleWindow::getScale() {
    return this->scale_factor;
}

// EVENTS
void ConsoleWindow::keyPressEvent(QKeyEvent* event)
{
    emit screenKeyPressed(event);
}

void ConsoleWindow::resizeEvent(QResizeEvent* event) {
    emit this->screenResized();
}


// FUNCTIONS
void ConsoleWindow::setCommandText(QString text)
{
    this->ui->CommandLabel->setText(text);
}

void ConsoleWindow::setOutputText(QString text)
{
    this->ui->OutputLabel->setText(text);
}

void ConsoleWindow::setScale(double scale_factor) {
    this->scale_factor = scale_factor;
}

void ConsoleWindow::scaleApplication() {
    // calculate the new font size
    double scale = 9*this->scale_factor;

    // make the correct font
    QFont font = this->ui->CommandLabel->font();
    font.setPointSize(scale);
    this->ui->CommandLabel->setFont(font);
    this->ui->OutputLabel->setFont(font);

    // scale the textbox size based on the font size
    this->ui->CommandFrame->setMaximumHeight(3.9*scale);
}

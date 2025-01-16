#include "./ui_consolewindow.h"
#include "consolewindow.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

ConsoleWindow::ConsoleWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::ConsoleWindow), scale_factor(1), alertTimeout(new QTimer(this))
{
    ui->setupUi(this);

    // remove the frame from the viewport
    ui->AlertFrame->setVisible(false);
    // setup the timer for the alert box
    QObject::connect(this->alertTimeout, &QTimer::timeout, this, [this](){this->ui->AlertFrame->setVisible(false);});
    this->alertTimeout->setSingleShot(true);

    // translate the linkActivated signal to the screenLinkClicked signal
    QObject::connect(ui->OutputLabel, &QLabel::linkActivated, this, &ConsoleWindow::screenLinkClicked);

    this->scaleApplication();
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
    this->resizeScreen();

    emit this->screenResized();
}


// FUNCTIONS
void ConsoleWindow::setCommandText(QString text) {
    this->ui->CommandLabel->setText(text);
}

void ConsoleWindow::setOutputText(QString text) {
    this->ui->OutputLabel->setText(text);
}

void ConsoleWindow::setScale(double scale_factor) {
    this->scale_factor = scale_factor;
}

void ConsoleWindow::showAlert(QString text) {
    this->ui->AlertLabel->setText(text);

    this->ui->AlertFrame->setVisible(true);

    // start or restart a 2 second timer
    this->alertTimeout->start(1250);
}

void ConsoleWindow::resizeScreen() {
    int windowWidth = this->ui->centralwidget->width();
    int windowHeight = this->ui->centralwidget->height();

    // the command window is not at all bound to the
    // window, so we need to resize it to always fit
    this->ui->CommandWindow->setFixedWidth(windowWidth);
    this->ui->CommandWindow->setFixedHeight(windowHeight);

    // change the position of the alert frame
    this->ui->AlertFrame->move(
        (windowWidth/2)-100,
        windowHeight-100-(this->ui->AlertFrame->height()/2)
        );
}

void ConsoleWindow::scaleApplication() {
    // calculate the new font size
    double scale = 9*this->scale_factor;

    // make the correct font
    QFont font = this->ui->CommandLabel->font();
    font.setPointSize(scale);
    this->ui->CommandLabel->setFont(font);
    this->ui->OutputLabel->setFont(font);
    this->ui->AlertLabel->setFont(font);

    this->showAlert(QString::number(this->scale_factor*100) + "%");

    // scale the textbox size based on the font size
    this->ui->CommandFrame->setMaximumHeight(3.9*scale);
    this->ui->AlertFrame->setFixedHeight(3.9*scale);

    this->resizeScreen();
}

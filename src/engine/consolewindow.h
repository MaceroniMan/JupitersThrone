#ifndef CONSOLEWINDOW_H
#define CONSOLEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ConsoleWindow;
}
QT_END_NAMESPACE

class ConsoleWindow : public QMainWindow {
    Q_OBJECT

public:
    ConsoleWindow(QWidget *parent = nullptr);
    ~ConsoleWindow();

    void scaleApplication();

    void setCommandText(QString text);
    void setOutputText(QString text);

    void showAlert(QString text);

    QFont getFont();

    QSize getCommandLabelSize();
    QSize getOutputLabelSize();

    void setScale(double scale);
    double getScale();

protected:
    void keyPressEvent(QKeyEvent* event);
    void resizeEvent(QResizeEvent* event);

signals:
    void screenKeyPressed(QKeyEvent* event);
    void screenLinkClicked(QString);
    void screenResized();

private:
    Ui::ConsoleWindow *ui;

    double scale_factor;
    QTimer *alertTimeout;

    void resizeScreen();
};
#endif // CONSOLEWINDOW_H

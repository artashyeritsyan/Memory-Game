#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "board.h"
#include "mainwindow.h"

#include <QDebug>

class Controller : public QObject {
    Q_OBJECT

public:
    Controller();
    ~Controller();

private slots:
    void handleStartCmd(EGameMode gameMode, EGameSize gameSize);
    void handleGameRestartCmd(); // write a definiton
    void handleClick(int buttonIndex);
    void handleScreenUpdateRequest();

    void handleCooldown();

private:
    void startGame();
    void restartGame();

private:
    bool _isTwoPlayer;;
    int _height;
    int _width;

    Board* _board;
    MainWindow* _window;
};

#endif // CONTROLLER_H

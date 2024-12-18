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
    int requestWinnerId();
    int requestPlayerScore(int id);

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

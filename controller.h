#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "board.h"
#include "mainwindow.h"

#include <QDebug>

class Controller : public QObject {
    Q_OBJECT

public:
    Controller();

private slots:
    void handleStartCmd(EGameMode gameMode, EGameSize gameSize);
    void handleGameRestartCmd(); // write a definiton
    void handleClick(int buttonIndex);
    void handleScreenUpdateRequest();

    void handleCooldown();

private:
    void startSinglePlayer();
    void restartGame();

private:
    EGameMode _gameMode;
    int _height;
    int _width;

    Board* _board;
    MainWindow* _window;
};

#endif // CONTROLLER_H

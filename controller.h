#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "board.h"
#include "mainwindow.h"

#include <QDebug>

class Controller : public QObject {
    Q_OBJECT

public:
    Controller();
    void start();

private slots:
    void parseStartCommand(EGameMode gameMode, EGameSize gameSize);
    void handleClick(int buttonIndex);
    void handleScreenUpdateRequest();

    void handleCooldown();

private:
    void startSinglePlayer();

private:
    EGameMode _gameMode;
    int _height;
    int _width;

    Board* _board;
    MainWindow* _window;
};

#endif // CONTROLLER_H

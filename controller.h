#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "board.h"
#include "menu.h"
#include "screen.h"

#include <QDebug>

class Controller : public QObject {
    Q_OBJECT
public:
    Controller(QObject* parent = nullptr);
    void start();

private slots:
    void startSinglePlayer() {
        qDebug() << "Single Player button clicked!";
        board.
    };
    void startTwoPlayer() {qDebug() << "Two Player button clicked!";};
    void showDifficultyMenu(){qDebug() << "Difficulty button clicked!";};
    void showScores(){ qDebug() << "Scores button clicked!";};
    void exitGame(){qDebug() << "Exit button clicked!";};

private:
    Board* board;
    Menu* menu;
    Screen* screen;
};

#endif // CONTROLLER_H

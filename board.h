#ifndef BOARD_H
#define BOARD_H

#include "card.h"

#include <random>
#include <QTimer>
#include <QVector>
#include <QMainWindow>


class Board
{
public:
    Board(int height, int width);
    void updateBoard();
    bool checkCard(int index);
    QVector<Card> getTable();
    int getSteps();
    int getScore();

// signals:
//     void waitCardCooldown();


private:
    void shufflePictures();

private:
    QVector<Card> _table;
    int _firstChosenCardIndex;

    int _score = 0;
    int _steps = 0;
    int cooldownTime = 900;
    QTimer _timer;

    int _size;
};

#endif // BOARD_H

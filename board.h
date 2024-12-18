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
    Board(int height, int width, bool isTwoPlayer = false);
    bool checkCard(int index);
    bool winCheck();

    QVector<Card> getTable();
    int getSteps() const;
    int getScore() const;
    int firstPlayerScore() const;
    int secondPlayerScore() const;
    int getPlayerTurn() const;
    int getWinnerId();

private:
    void shufflePictures();
    void calculateScore();
    void switchTurn();

private:
    QVector<Card> _table;
    int _size;
    int _firstChosenCardIndex;

    int _score = 0;
    int _steps = 0;

    bool _isTwoPlayer;
    int _firstPlayerScore;
    int _secondPlayerScore;
    int _playerTurn;

};

#endif // BOARD_H

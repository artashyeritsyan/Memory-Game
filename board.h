#ifndef BOARD_H
#define BOARD_H

#include "card.h"

#include <QVector>

class Board
{
public:
    Board();
    void updateBoard();
    void checkCard(int index);

private:
    QVector<Card> _table;
    int _firstChosenCardIndex;
};

#endif // BOARD_H

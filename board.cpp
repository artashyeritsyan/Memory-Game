#include "board.h"

Board::Board() : _firstChosenCardIndex(-1) {}

void Board::checkCard(int index)
{
    if (_firstChosenCardIndex == -1) {
        _firstChosenCardIndex = index;
        _table[index].setIsFlipped(true);
    }
    else {
        if (_table[_firstChosenCardIndex].getPictureNumber() == _table[index].getPictureNumber()) {
            _table[_firstChosenCardIndex].setIsGuessed(true);
            _table[index].setIsGuessed(true);
        }
        else {
            _table[_firstChosenCardIndex].setIsGuessed(false);
            _table[index].setIsGuessed(false);
        }
    }
}


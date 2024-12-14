#include "board.h"

Board::Board(int height, int width) : _firstChosenCardIndex(-1)
{
    _size = height * width;
    _table.reserve(_size);
    for (int i = 0; i < _size; ++i) {
        _table.emplace_back();
    }

    shufflePictures();
}

bool Board::checkCard(int index)
{
    if (_firstChosenCardIndex == -1) {
        _firstChosenCardIndex = index;
        _table[index].setIsFlipped(true);
    }
    else {
        ++_steps;
        // sendSteps()

        if (_table[_firstChosenCardIndex].getPictureNumber() == _table[index].getPictureNumber()) {
            _table[_firstChosenCardIndex].setIsGuessed(true);
            _table[index].setIsGuessed(true);

            _firstChosenCardIndex = -1;
            ++_score;
        }
        else {
            _table[_firstChosenCardIndex].setIsGuessed(false);
            _table[index].setIsGuessed(false);

            _table[_firstChosenCardIndex].setIsFlipped(false);
            _table[index].setIsFlipped(false);

            _firstChosenCardIndex = -1;

            // emit waitCardCooldown();
            // TODO: Call updateScreen function and give the table to update screen

            // returns true to call cooldown function from controller. Cause signal doesnt work :(
            return true;
        }
    }
    return false;
    // TODO: Call updateScreen function and give the table to update screen
}

QVector<Card> Board::getTable()
{
    return _table;
}

int Board::getSteps()
{
    return _steps;
}

int Board::getScore()
{
    return _score;
}

void Board::shufflePictures()
{
    int n = _size / 2;
    std::vector<int> pictures;

    for (int i = 1; i <= n; ++i)
    {
        pictures.push_back(i);
        pictures.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pictures.begin(), pictures.end(), g);

    for (int i = 0; i < _size; ++i)
    {
        _table[i].setPictureNumber(pictures[i]);
    }
}


#include "board.h"

Board::Board(int height, int width, bool isTwoPlayer) : _firstChosenCardIndex(-1) {
    _size = height * width;
    _table.reserve(_size);
    _isTwoPlayer = isTwoPlayer;
    _firstPlayerScore = 0;
    _secondPlayerScore = 0;
    _playerTurn = 1;

    for (int i = 0; i < _size; ++i) {
        _table.emplace_back();
    }

    shufflePictures();
}

bool Board::checkCard(int index) {
    bool cardCooldown = false;

    if (_firstChosenCardIndex == -1) {
        _firstChosenCardIndex = index;
        _table[index].setIsFlipped(true);
    }
    else {
        ++_steps;

        if (_table[_firstChosenCardIndex].getPictureNumber() == _table[index].getPictureNumber()) {
            _table[_firstChosenCardIndex].setIsGuessed(true);
            _table[index].setIsGuessed(true);

            calculateScore();
        }
        else {
            _table[_firstChosenCardIndex].setIsGuessed(false);
            _table[index].setIsGuessed(false);

            _table[_firstChosenCardIndex].setIsFlipped(false);
            _table[index].setIsFlipped(false);

            switchTurn();

            // returns true to call cooldown function from controller. Cause signal doesnt work :(
            cardCooldown = true;
        }

        _firstChosenCardIndex = -1;
    }
    return cardCooldown;
}

QVector<Card> Board::getTable() {
    return _table;
}

int Board::getSteps() const {
    return _steps;
}

int Board::getScore() const {
    return _score;
}

bool Board::winCheck() {
    bool isWin = false;
    if (_score == _size / 2) isWin = true;
    return isWin;
}

void Board::shufflePictures() {
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

void Board::calculateScore()
{
    if (_isTwoPlayer) {
        if (_playerTurn == 1)
            ++_firstPlayerScore;
        else
            ++_secondPlayerScore;
    }

    ++_score;
}

void Board::switchTurn()
{
    if (_isTwoPlayer) {
        if (_playerTurn == 1) {
            _playerTurn = 2;
        }
        else {
            _playerTurn = 1;
        }
    }
}

int Board::getPlayerTurn() const
{
    return _playerTurn;
}

int Board::firstPlayerScore() const
{
    return _firstPlayerScore;
}

int Board::secondPlayerScore() const
{
    return _secondPlayerScore;
}

#include "card.h"

Card::Card() : _pictureNumber(-1), _isFlipped(false), _isGuessed(false) {}

int Card::getPictureNumber() const {
    return _pictureNumber;
}

void Card::setPictureNumber(int number) {
    _pictureNumber = number;
}

bool Card::getIsFlipped() const {
    return _isFlipped;
}

void Card::setIsFlipped(bool flipped) {
    _isFlipped = flipped;
}

bool Card::getIsGuessed() const {
    return _isGuessed;
}

void Card::setIsGuessed(bool guessed) {
    _isGuessed = guessed;
}

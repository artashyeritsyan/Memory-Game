#ifndef CARD_H
#define CARD_H

class Card
{
public:
    Card();

    int getPictureNumber() const;
    void setPictureNumber(int number);

    bool getIsFlipped() const;
    void setIsFlipped(bool flipped);

    bool getIsGuessed() const;
    void setIsGuessed(bool guessed);

private:
    int _pictureNumber;
    bool _isFlipped;
    bool _isGuessed;
};

#endif // CARD_H

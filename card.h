#ifndef _CARD_H
#define _CARD_H
#include <iostream>


enum class Suit { Heart, Diamond, Spade, Club};

class Card {
  char value;
  Suit suit;

public:
  Card(char v, Suit s);
  char getValue() const;
  char getSuit() const;
  int give_value() const;
  void printCard() const;
};

#endif

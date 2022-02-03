#ifndef _STRATEGY_H
#define _STRATEGY_H
#include "deck.h"
#include <iostream>
#include <string>


class Card;
class Deck;

class Strategy {
public:
  virtual ~Strategy() = default;
  virtual std::shared_ptr<Card> play(std::shared_ptr<Deck>  deck) = 0;
  virtual std::shared_ptr<Card> discard(std::shared_ptr<Deck>  deck) = 0;
};

#endif

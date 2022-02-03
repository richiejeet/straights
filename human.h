#ifndef _HUMAN_H
#define _HUMAN_H
#include "strategy.h"

class Human : public Strategy {
  std::shared_ptr<Card> play_discard(std::shared_ptr<Deck> deck);
public:
  std::shared_ptr<Card> play(std::shared_ptr<Deck> deck) override;
  std::shared_ptr<Card> discard(std::shared_ptr<Deck> deck) override;
};

#endif

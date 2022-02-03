#ifndef _SIMPLE_COUMPUTER
#define _SIMPLE_COUMPUTER
#include "strategy.h"

class Simple_computer : public Strategy {
  std::shared_ptr<Card> play_discard(std::shared_ptr<Deck> deck);
public:
  std::shared_ptr<Card> play(std::shared_ptr<Deck>  deck) override;
  std::shared_ptr<Card> discard(std::shared_ptr<Deck>  deck) override;
};

#endif

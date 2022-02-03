#include "simplecomputer.h"

std::shared_ptr<Card> Simple_computer::play_discard(std::shared_ptr<Deck> deck) {
  if (deck->empty()) return nullptr;
  return deck->out(0);
}

std::shared_ptr<Card> Simple_computer::play(std::shared_ptr<Deck>  deck) {
  return play_discard(deck);
}

std::shared_ptr<Card> Simple_computer::discard(std::shared_ptr<Deck>  deck) {
  return play_discard(deck);
}

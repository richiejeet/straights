#include "human.h"

std::shared_ptr<Card> Human::play_discard(std::shared_ptr<Deck> deck) {
  std::string s;
  std::cin >> s;
  char ch, suit;
  if (s.length() == 3) {
    ch = '0' + 10;
    suit = s.at(2);
  } else {
    ch = s.at(0);
    suit = s.at(1);
  }
  return deck->find_card(ch, suit);
}

std::shared_ptr<Card> Human::play(std::shared_ptr<Deck> deck) {
  std::shared_ptr<Card> card;
  while (1) {
  card = play_discard(deck);
  if (!card) {
    std::cout << "This is not a legal play." << '\n';
    std::string s;
    std::cin >> s;
    continue;
  } else {
    break;
  }
}
return card;
}

std::shared_ptr<Card> Human::discard(std::shared_ptr<Deck> deck) {
  return play_discard(deck);
}

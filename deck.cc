#include "deck.h"

void Deck::insertCard(std::shared_ptr<Card>card) {
  if (card) deck.emplace_back(card);
}

void Deck::showDeck() const {
  int i = 0;
  for (auto it = deck.begin(); it != deck.end(); ++it) {
    std::cout << " ";
    (*it)->printCard();
    if ((i + 1) % 13 == 0) {
      std::cout << std::endl;
    }
    ++i;
  }
  std::cout << std::endl;
}

void Deck::showCard() const {
  for (auto it = deck.begin(); it != deck.end(); ++it) {
    std::cout << " ";
    char ch = (*it)->getValue();
    if (ch == 58) {
      std::cout << "10";
    } else {
      std::cout << ch;
    }
  }
  std::cout << std::endl;
}

void Deck::shuffle(std::string s) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  if (!s.empty()) {
    seed = std::stoi(s);
  }
  std::default_random_engine rng{seed};
  std::shuffle( deck.begin(), deck.end(), rng );
}

std::shared_ptr<Card> Deck::out(int i) {
  auto it = deck.begin() + i;
  return *it;
}

std::shared_ptr<Card> Deck::find_card(char ch, char suit) const {
  for (auto it = deck.begin(); it != deck.end(); ++it) {
    if ((*it)->getValue() == ch) {
      if ((*it)->getSuit() == suit) {
        return *it;
      }
    }
  }
  return nullptr;
}

void Deck::card_remove(std::shared_ptr<Card>card) {
  for (auto it = deck.begin(); it != deck.end(); ++it) {
    if (card == (*it)) {
      deck.erase(it);
      deck.shrink_to_fit();
      break;
    }
  }
}

bool Deck::empty() const {
  if (deck.empty()) return true;
  return false;
}

int Deck::deck_size() const {
  return deck.size();
}

void Deck::clear_deck() {
  for (auto it = deck.begin(); it != deck.end(); ) {
    deck.erase(it);
  }
  deck.shrink_to_fit();
}

void Deck::remove() {
  auto end = deck.end();
  for (auto it = deck.begin(); it != end; ++it) {
    end = std::remove(it + 1, end, *it);
  }
  deck.erase(end,deck.end());
}

void Deck::insertFront(std::shared_ptr<Card>card) {
  deck.insert(deck.begin(), card);
}

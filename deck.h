#ifndef _DECK_H_
#define _DECK_H_
#include <vector>
#include <memory>
#include <iostream>
#include "card.h"
#include <algorithm>
#include <random>
#include <chrono>

class Deck {

  std::vector<std::shared_ptr<Card>> deck;

  public:
    void insertCard(std::shared_ptr<Card>card);
    void insertFront(std::shared_ptr<Card>card);
    void showDeck() const;
    void shuffle(std::string seed = "");
    std::shared_ptr<Card> out(int i);
    std::shared_ptr<Card> find_card(char ch, char suit) const;
    void card_remove(std::shared_ptr<Card>card);
    bool empty() const;
    int deck_size() const;
    void clear_deck();
    void remove();
    void showCard() const;
};

#endif

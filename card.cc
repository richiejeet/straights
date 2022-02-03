#include "card.h"

Card::Card(char v, Suit s) : value{v}, suit{s} {}

char Card::getValue() const {
  return value;
}

char Card::getSuit() const {
  char suit_;
  if (suit == Suit::Spade) {
    suit_ = 'S';
  } else if (suit == Suit::Diamond) {
    suit_ = 'D';
  } else if (suit == Suit::Club) {
    suit_ = 'C';
  } else {
    suit_ = 'H';
  }
  return suit_;
}

int Card::give_value() const {
  if (value == 'A') {
    return 1;
  } else if (value == 'J') {
    return 11;
  } else if (value == 'Q') {
    return 12;
  } else if (value == 'K') {
    return 13;
  } else {
    return value - '0';\
  }
}

void Card::printCard() const {
  if (value == ':') {
    std::cout << "10";
  } else {
    std::cout << value;
  }
  if (suit == Suit::Spade) {
    std::cout << 'S';
  } else if (suit == Suit::Diamond) {
    std::cout << 'D';
  } else if (suit == Suit::Club) {
    std::cout << 'C';
  } else {
    std::cout << 'H';
  }
}

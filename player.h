#ifndef _PLAYER_H
#define _PLAYER_H
#include "deck.h"
#include <string>
#include <memory>
#include "human.h"
#include "simplecomputer.h"

class Strategy;

class Player {
  int id;
  char player;
  std::shared_ptr<Deck> hand;
  std::shared_ptr<Deck> legal_plays;
  std::shared_ptr<Deck> discards;
  int total = 0;
  std::shared_ptr<Strategy> strategy_;

  void set_strategy(std::shared_ptr<Strategy> strategy);
  void new_total();


public:
  Player(int i, char player_);
  int getTotal(bool b = false);
  void make_hand(std::shared_ptr<Card> card);
  void showHand();
  void showLegalHand();
  int getID();
  bool seven_of_spades();
  void rage_quit();
  void make_legal_plays(std::shared_ptr<Deck> deck);
  bool has_no_cards() const;
  std::shared_ptr<Card> play(std::string s = "");
  void clear_legal_plays();
  char getPlayer() const;
};

#endif

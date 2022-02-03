#ifndef _GAME_H
#define _GAME_H
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "deck.h"
#include "player.h"

const int MAX_SCORE = 80;

class Deck;
class Card;

class Game {
  std::shared_ptr<Deck> gameDeck;
  std::vector<std::shared_ptr<Player>> players;
  std::shared_ptr<Deck> clubs;
  std::shared_ptr<Deck> spades;
  std::shared_ptr<Deck> hearts;
  std::shared_ptr<Deck> diamonds;

  void handMaker(std::shared_ptr<Player> player);
  void make_legal_hands(std::shared_ptr<Player> player);
  bool check_score() const;
  bool next_round() const;
  void showGameDeck();


public:
  Game();
  void gameDeckGeneration();
  void playerGeneration();
  void shuffle(std::string seed = "");
  bool play();
  void tell_winners();
};

#endif

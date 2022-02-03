#include "game.h"


Game::Game() {
  gameDeck = std::make_shared<Deck>();
  clubs = std::make_shared<Deck>();
  spades = std::make_shared<Deck>();
  hearts = std::make_shared<Deck>();
  diamonds = std::make_shared<Deck>();
}

void Game::gameDeckGeneration() {
  for (int i = 0; i < 4; ++i) {
    Suit suit;
    if (i == 0) {
      suit = Suit::Club;
    } else if (i == 1) {
      suit = Suit::Diamond;
    } else if (i == 2) {
      suit = Suit::Heart;
    } else {
      suit = Suit::Spade;
    }
    for (int j = 1; j <= 13; ++j) {
      char ch;
      if (j == 1) {
        ch = 'A';
      } else if (j == 11) {
        ch = 'J';
      } else if (j == 12) {
        ch = 'Q';
      } else if (j == 13) {
        ch = 'K';
      } else {
        ch = j + '0';
      }
      gameDeck->insertCard(std::make_shared<Card>(ch, suit));
    }
  }
}

void Game::showGameDeck() {
  gameDeck->showDeck();
}

void Game::shuffle(std::string seed) {
  gameDeck->shuffle(seed);
}

void Game::handMaker(std::shared_ptr<Player> player) {
  int id = player->getID();
  for (int i = (id - 1) * 13; i < ((id - 1) * 13) + 13; i++) {
    std::shared_ptr<Card> card = gameDeck->out(i);
    player->make_hand(card);
  }
}

void Game::playerGeneration() {
  for (int i = 1; i <= 4; i++) {
    char ch;
    while (1) {
      std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
      std::cin >> ch;
      if ((ch == 'h') || (ch == 'c')) {
        break;
      } else {
        std::cout << "Wrong input" << '\n';
        continue;
      }
    }
    auto player = std::make_shared<Player>(i,ch);
    handMaker(player);
    players.emplace_back(player);
  }
}


void Game::make_legal_hands(std::shared_ptr<Player> player) {
  player->clear_legal_plays();
  player->make_legal_plays(spades);
  player->make_legal_plays(diamonds);
  player->make_legal_plays(clubs);
  player->make_legal_plays(hearts);
}

bool Game::check_score() const {
  bool ans = false;
  for(int i = 0; i < 4; ++i) {
    if (players[i]->getTotal(true) >= MAX_SCORE) {
      ans = true;
    }
  }
  return ans;
}

bool Game::next_round() const {
  for (int i = 0; i < 4; ++i) {
    if (!players[i]->has_no_cards()) {
      return false;
    }
  }
  return true;
}


bool Game::play() {
  do {
    int start = -1;
    int counter = 0;
    for (int i = 0; i < 4; ++i) {
      if (players[i]->seven_of_spades()) {
        start = i;
        break;
      }
    }
    std::cout << "A new round begins. It's Player" << start + 1 << "'s turn to play." << std::endl;
    while (!next_round()) {
      counter = 1;
      while (counter <= 4) {
        std::shared_ptr<Card> card;
        std::cout << "Spades:";
        spades->showCard();
        std::cout << "Hearts:";
        hearts->showCard();
        std::cout << "Diamonds:";
        diamonds->showCard();
        std::cout << "Clubs:";
        clubs->showCard();
        make_legal_hands(players[start]);
        players[start]->showHand();
        players[start]->showLegalHand();
        if (players[start]->getPlayer() == 'h') {
          std::cout << "> ";
          std::string s;
          while (std::cin >> s) {
            if (s == "quit") {
              return false;
            } else if (s == "ragequit") {
              players[start]->rage_quit();
              card = players[start]->play();
              break;
            } else if (s == "deck") {
              showGameDeck();
            } else if ((s == "play") || (s == "discard")) {
              card = players[start]->play(s);
              break;
            } else {
              std::cout << "Wrong command. Try again." << '\n';
              continue;
            }
          }
          if (std::cin.eof()) return false;
        } else {
          card = players[start]->play();
        }
        if (card) {
          char suit = card->getSuit();
          if (suit == 'S') {
            if ((!spades->empty()) && (card->give_value() < (spades->out(0))->give_value())) {
              spades->insertFront(card);
            } else {
              spades->insertCard(card);
            }
          } else if (suit == 'C') {
            if ((!clubs->empty()) && (card->give_value() < (clubs->out(0))->give_value())) {
              clubs->insertFront(card);
            } else {
              clubs->insertCard(card);
            }
          } else if (suit == 'H') {
            if ((!hearts->empty()) && (card->give_value() < (hearts->out(0))->give_value())) {
              hearts->insertFront(card);
            } else {
              hearts->insertCard(card);
            }
          } else {
            if ((!diamonds->empty()) && (card->give_value() < (diamonds->out(0))->give_value())) {
              diamonds->insertFront(card);
            } else {
              diamonds->insertCard(card);
            }
          }
        }
        ++counter;
        if (((counter == 4) && (start == 3)) || (start == 3)) {
          start = 0;
        } else {
          ++start;
        }
      }
    }
    hearts->clear_deck();
    diamonds->clear_deck();
    spades->clear_deck();
    clubs->clear_deck();
    shuffle();
    for (int i = 0; i < 4; ++i) {
      handMaker(players[i]);
    }
  } while (!check_score());
  return true;
}

void Game::tell_winners() {
  std::vector<std::shared_ptr<Player>> v;
  std::shared_ptr<Player> p = players[0];
  v.emplace_back(p);
  for (int i = 1; i < 4; ++i) {
    if (p->getTotal() == players[i]->getTotal()) {
      p = players[i];
      v.emplace_back(p);
    } else if (p->getTotal() > players[i]->getTotal()) {
      if (!v.empty()) {
        for (auto it = v.begin(); it != v.end(); ) {
          v.erase(it);
        }
      }
      p = players[i];
      v.emplace_back(p);
    }
  }
  for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << "Player" << (*it)->getID() << " wins!" << std::endl;
  }
}

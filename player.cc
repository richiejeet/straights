#include "player.h"


Player::Player(int i, char player_) : id {i}, player{player_} {
  if (player_ == 'h') {
    strategy_ = std::make_shared<Human>();
  } else {
    strategy_ = std::make_shared<Simple_computer>();
  }
  hand = std::make_shared<Deck>();
  legal_plays = std::make_shared<Deck>();
  discards = std::make_shared<Deck>();
}

char Player::getPlayer() const {
  return player;
}

int Player::getTotal(bool b) {
  if (b) {
    std::cout << "Player" << id << "'s discards:";
    discards->showDeck();

    new_total();
  }
  return total;
}

void Player::set_strategy(std::shared_ptr<Strategy> strategy) {
  strategy_ = strategy;
}

int Player::getID() {
  return id;
}

void Player::make_hand(std::shared_ptr<Card>card) {
  hand->insertCard(card);
}

void Player::showHand() {
  std::cout << "Your hand:";
  hand->showDeck();
}

bool Player::seven_of_spades() {
  std::shared_ptr<Card> card = hand->find_card('7', 'S');
  if (card) {
    return true;
  }
  return false;
}

void Player::rage_quit() {
  set_strategy(std::make_shared <Simple_computer>());
  player = 'c';
  std::cout << "Player" << id << " ragequits. A computer will now takeover." << '\n';
}

void Player::new_total() {
  int n = discards->deck_size();
  int temp = total;
  int new_ = 0;
  for (int i = 0; i < n; ++i) {
    new_ += (discards->out(i))->give_value();
  }

  total = temp + new_;
  std::cout << "Player" << id << "'s score: " << temp << " + " << new_;
  std::cout << " = " << total << std::endl;
  discards->clear_deck();
}

void Player::make_legal_plays(std::shared_ptr<Deck> deck) {
  if (!deck->empty()) {
    int n = deck->deck_size();
    int first = 0;
    int last = 0;
    if (n == 1) {
      first = (deck->out(0))->give_value();
      last = first;
    } else {
      first = (deck->out(0))->give_value();
      last = (deck->out(n - 1))->give_value();

    }
    char ch = (deck->out(0))->getSuit();
    int num = hand->deck_size();
    for (int i = 0; i < num; ++i) {
      if ((hand->out(i))->getSuit() == ch) {
        int p = (hand->out(i))->give_value();
        if ((p + 1 == first) || (p - 1 == last)) {
          legal_plays->insertCard(hand->out(i));
        }
      }
    }
  } else {
    for (int i = 1; i <= 4; ++i) {
      char ch;
      if (i == 1) {
        ch = 'S';
        std::shared_ptr<Card> card = hand->find_card('7', ch);
        legal_plays->insertCard(card);
        if (card) break;
      } else if (i == 2) {
        ch = 'H';
        std::shared_ptr<Card> card = hand->find_card('7', ch);
        legal_plays->insertCard(card);
      } else if (i == 3) {
        ch = 'D';
        std::shared_ptr<Card> card = hand->find_card('7', ch);
        legal_plays->insertCard(card);
      } else {
        ch = 'C';
        std::shared_ptr<Card> card = hand->find_card('7', ch);
        legal_plays->insertCard(card);
      }
    }
  }
  legal_plays->remove();
}



bool Player::has_no_cards() const {
  return hand->empty();
}

std::shared_ptr<Card> Player::play(std::string s) {
  if (legal_plays->empty()) {
    if (s.empty()){
      std::shared_ptr<Card> card = strategy_->discard(hand);
      hand->card_remove(card);
      discards->insertCard(card);
      std::cout << "Player" << id << " discards ";
      card->printCard();
      std::cout << std::endl;
      return nullptr;
    } else {
      while (1) {
        if (s == "discard") {
          std::shared_ptr<Card> card = strategy_->discard(hand);
          if (!card) {
            std::cout << "You do not have this card in your hand. Try again." << '\n';
            continue;
          }
          hand->card_remove(card);
          discards->insertCard(card);
          std::cout << "Player" << id << " discards ";
          card->printCard();
          std::cout << std::endl;
          return nullptr;
        } else {
          std::cout << "Wrong command. Try again." << '\n';
          std::cin >> s;
        }
      }
    }
  } else {
    if (player == 'h') {
      while (1){
        if (s == "discard") {
          std::cout << "You have a legal play." << '\n';
          std::cin >> s;
        } else if (s == "play") {
          std::shared_ptr<Card> card = strategy_->play(legal_plays);
          hand->card_remove(card);
          legal_plays->card_remove(card);
          std::cout << "Player" << id << " plays ";
          card->printCard();
          std::cout << std::endl;
          return card;
        } else {
          std::cout << "Wrong command. Try Again. You have to play or discard." << '\n';
          std::cin >> s;
        }
        std::cin >> s;
      }
    } else {
      std::shared_ptr<Card> card = strategy_->play(legal_plays);
      hand->card_remove(card);
      legal_plays->card_remove(card);
      std::cout << "Player" << id << " plays ";
      card->printCard();
      std::cout << std::endl;
      return card;
    }
  }
}

void Player::showLegalHand() {
  std::cout << "Legal plays:";
  legal_plays->showDeck();
}

void Player::clear_legal_plays() {
  if (legal_plays) {
    if (!legal_plays->empty()){
      legal_plays->clear_deck();
    }
  }
}

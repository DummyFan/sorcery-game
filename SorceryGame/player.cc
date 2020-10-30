#include <string>
#include <iostream>
#include <sstream>
#include "player.h"
#include <utility>
#include "prng.h"

using namespace std;

Player::Player(string name, vector<string> hand, vector<string> deck, int magic, int magicCap, int health):
  name{name}, hand{hand}, deck{deck}, magic{magic}, magicCap{magicCap}, health{health} {}

string Player::getName() const {
  return name;
}

int Player::getMagic() const {
  return magic;
}

void Player::useMagic(int num) {
  magic -= num;
}

int Player::getHealth() const {
  return health;
}

void Player::setHealth(int newHealth) {
  health = newHealth;
}

int Player::handCards() const {
  return hand.size();
}

std::string Player::getCard(int index) {
  return hand[index - 1];
}

void Player::addHand(string cardName) {
  hand.push_back(cardName);
}

void Player::discard(int index) {
  hand.erase(hand.begin() + index - 1);
}

bool Player::deckEmpty() {
  if (deck.size() == 0) {
    return true;
  }
  return false;
}

void Player::draw() {
  string drew = deck[0];
  hand.push_back(drew);
  deck.erase(deck.begin());
}
  
void Player::shuffle() {
  PRNG prng;
  for (unsigned int i = 0; i < deck.size(); i++) {
    int num = prng( deck.size() );
    swap(deck[i], deck[num-1]);
  }
}

void Player::incMagic() {
  magicCap++;
}

void Player::restoreMagic() {
  magic = magicCap;
}

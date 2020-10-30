#include "spell.h"
#include "board.h"
#include <iostream>
#include <fstream>
using namespace std;

Spell::Spell() {}

Spell::Spell(string name, int cost, string description):
     Card{name, cost}, effect{effect} {}

Spell::Spell(const Spell &other): Card{other}, effect{other.effect} {}

void Spell::banish(Board *target) {
  target->removeRitual();
}

void Spell::banish(Board *target, int index) {
  target->killMinion(index);
}

void Spell::unsummon(Board *target, int index) {
  target->returnMinion(index);
}

void Spell::recharge(Board *target) {
  target->chargeRitual(3);
}

void Spell::raiseDead(Board *target) {
  target->reviveMinion();
}

void Spell::blizzard(Board *active, Board *nonActive) {
  active->damageAllMinion(2);
  nonActive->damageAllMinion(2);
}
 
void Spell::playCard(Board *first, Board *second) {
  string cardName = this->getName();
  if (cardName == "Banish") {
    banish(second);
  } else if (cardName == "Raise Dead") {
    raiseDead(first);
  } else if (cardName == "Blizzard") {
    blizzard(first, second);
  } else if (cardName == "Recharge") {
    recharge(first);
  }
}

void Spell::playCard(Board *target, int index) {
  string cardName = this->getName();
  if (cardName == "Banish") {
    banish(target, index);
  } else if (cardName == "Unsummon") {
    unsummon(target, index);
  }
}

string Spell::printCard(int line) {
  string retval;
  ifstream file("spells.txt");
  int height = 11;
  int cardNum;
  if (getName() == "Banish") {
    cardNum = 0;
  } else if (getName() == "Unsummon") {
    cardNum = 1;
  } else if (getName() == "Recharge") {
    cardNum = 2;
  } else if (getName() == "Disenchant") {
    cardNum = 3;
  } else if (getName() == "Raise Dead") {
    cardNum = 4;
  } else if (getName() == "Blizzard") {
    cardNum = 5;
  } 

  for (int i = 0; i < cardNum*height; i++) {
    getline(file, retval);
  }
  for (int i = 1; i <= height; i++) {
    getline(file, retval);
    if (i == line) {
      return retval;
    }
  }
  return "";
}

Spell::~Spell() {}
  

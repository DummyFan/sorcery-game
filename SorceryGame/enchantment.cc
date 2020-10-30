#include "enchantment.h"
#include <fstream>
#include "board.h"
using namespace std;

Enchantment::Enchantment() {}

Enchantment::Enchantment(string name, int cost, int enAttack, int enDefense, bool multi):
     Card{name, cost}, enAttack{enAttack}, enDefense{enDefense}, multi{multi} {}

Enchantment::Enchantment(Enchantment &other): 
     Card{other}, enAttack{other.enAttack}, enDefense{other.enDefense}, multi{other.multi} {}

void Enchantment::enchant(Minion &m) const {
  if (multi) {
    m.setAttack(m.getAttack() * enAttack);
    m.setDefense(m.getDefense() * enDefense);
  } else {
    m.setAttack(m.getAttack() + enAttack);
    m.setDefense(m.getDefense() + enDefense);
  }
}

void Enchantment::haste(Minion &m) const {
  m.setAction(m.getAction() + 1);
}

void Enchantment::magicFatigue(Minion &m) const {
  m.setACost(m.getACost() + 2);
}

void Enchantment::silence(Minion &m) const {
  m.removeAbility();
}

void Enchantment::playCard(Board *first, Board *second) {}

void Enchantment::playCard(Board *target, int index) {
  Minion *temp = target->getMinion(index);
  if (getName() == "Giant Strength" || getName() == "Enrage") {
    enchant(*temp);
  } else if (getName() == "Haste") {
    haste(*temp);
  } else if (getName() == "Magic Fatigue") {
    magicFatigue(*temp);
  } else if (getName() == "Silence") {
    silence(*temp);
  }
}

string Enchantment::printCard(int line) {
  string retval;
  ifstream file("enchantments.txt");
  int height = 11;
  int cardNum;
  if (getName() == "Giant Strength") {
    cardNum = 0;
  } else if (getName() == "Enrage") {
    cardNum = 1;
  } else if (getName() == "Haste") {
    cardNum = 2;
  } else if (getName() == "Magic Fatigue") {
    cardNum = 3;
  } else if (getName() == "Silence") {
    cardNum = 4;
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

Enchantment::~Enchantment() {}


#include "ritual.h"
#include "board.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

Ritual::Ritual() {}

Ritual::Ritual(string name, int cost, Trigger tAbility, int aCost, int charge):
         Card{name, cost}, tAbility{tAbility}, aCost{aCost}, charge{charge} {}

Ritual::Ritual(const Ritual &other): Card{other},
         tAbility{other.tAbility}, aCost{other.aCost}, charge{other.charge} {}

void Ritual::playCard(Board *first, Board *second) {
  first->playRitual(*this);
}
 
void Ritual::playCard(Board *target, int index) {}

string Ritual::printCard(int line) {
  string retval;
  ifstream file("rituals.txt");
  int height = 11;
  int cardNum;
  if (getName() == "Dark Ritual") {
    cardNum = 0;
  } else if (getName() == "Aura of Power") {
    cardNum = 1;
  } else if (getName() == "Standstill") {
    cardNum = 2;
  }

  for (int i = 0; i < cardNum*height; i++) {
    getline(file, retval);
  }
  for (int i = 1; i <=height; i++) {
    getline(file, retval);
    if (line == 10) {
      ostringstream oss;
      oss << "|                         |" << setw(4) << right << charge << " |";
      retval = oss.str();
      return retval;
    } else if (i == line) {
      return retval;
    }
  }
  return "";
}

void Ritual::addCharge(int charges) {
  charge += charges;
}

void Ritual::activate(Minion &m, Player &p, Board *current) {
  if (aCost <= charge) {
    if (getName() == "Dark Ritual") {
      if (current->playerName() == p.getName()) {
        tAbility.gainMagic(p);
        charge -= aCost;
      }
    } else if (getName() == "Aura of Power") {
      if (current->playerName() == p.getName()) {
        tAbility.enchant(m);
        charge -= aCost;
      }
    } else if (getName() == "Standstill") {
      tAbility.destory(m);
      charge -= aCost;
    }
  }
}

string Ritual::getTriggerType() const {
  return tAbility.getType();
}

Ritual::~Ritual() {}

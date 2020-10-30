#include "minion.h"
#include "board.h"
#include "ability.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

Minion::Minion() {}

Minion::Minion(string name, int cost, int attack, int defense, Trigger *tAbility,
               Ability *aAbility, int action, int actRemain):
      Card{name, cost}, attack{attack}, defense{defense}, tAbility{tAbility},
       aAbility{aAbility}, action{action}, actRemain{actRemain} {}

Minion::Minion(const Minion &other): 
      Card{other}, attack{other.attack}, defense{other.defense}, tAbility{other.tAbility},
       aAbility{other.aAbility}, action{other.action}, actRemain{other.actRemain} {}

int Minion::getAttack() const {
  return attack;
}

int Minion::getDefense() const {
  return defense;
}

int Minion::getAction() const {
  return action;
}

int Minion::getACost() const {
  return aAbility->getCost();
}

void Minion::setAttack(int newAttack) {
  attack = newAttack;
}

void Minion::setDefense(int newDefense) {
  defense = newDefense;
}

void Minion::setAction(int newAction) {
  action = newAction;
}

void Minion::setACost(int newCost) {
  aAbility->setCost(newCost);
}

void Minion::restoreAction() {
  actRemain = action;
}

string Minion::getTriggerType() const{
  if (tAbility) {
    return tAbility->getType();
  }
  string retval = "";
  return retval;
}

void Minion::activate(Minion &m, Player &p, Board *current) {
  if (getName() == "Bone Golem") {
    tAbility->enchant(*this);
  } else if (getName() == "Fire Elemental") {
    if (current->playerName() != p.getName()) {
      tAbility->dealDmg(m);
    }
  } else if (getName() == "Potion Seller") {
    if (current->playerName() == p.getName()) {
      for (int i = 1; i <= current->nom(); i++) {
        Minion *temp = current->getMinion(i);
        tAbility->enchant(*temp);
      }
    }
  }
}

void Minion::useAbility(Board *current, Minion &target) {
  if (actRemain > 0) {
    if (aAbility->useAbility(*this, current, target)) {
      actRemain--;
    }
  } else {
    cout << "This minion has no more action points" << endl;
  }
}

void Minion::removeAbility() {
  aAbility = nullptr;
}

void Minion::attackPlayer(Player *other) {
  if (actRemain > 0) {
    int newHealth = other->getHealth();
    newHealth -= getAttack();
    other->setHealth(newHealth);
    actRemain--;
  } else {
    cout << "This minion has no more action points" << endl;
  }
}

void Minion::attackMinion(Board *first, Board *second, Minion *other, int ind1, int ind2) {
  defense -= other->attack;
  other->defense -= attack;
  if (defense <= 0) first->killMinion(ind1);
  if (other->defense <= 0) second->killMinion(ind2);
}

void Minion::playCard(Board *first, Board *second) {
  first->playMinion(*this);
}

void Minion::playCard(Board *target, int index) {}

string Minion::printCard(int line) {
  ostringstream theLine;
  string retval;
  if (line == 1||line == 3||line == 5||line == 11) {
    retval = "|-------------------------------|";
  } else if (line == 2) {
    theLine << "| " << setw(24) << left << getName() << "|";
    theLine << setw(4) << right << getCost() << " |";
    retval = theLine.str();
  } else if (line == 4) {
    retval = "|                        Minion |";
  } else if (line == 6||line == 7||line == 8) {
    if (tAbility) {
      int start = line - 6;
      string eff = tAbility->getEffect();
      int len = eff.length();
      if (start * 29 < len) {
        theLine << "| " << setw(29) << left << eff.substr(start*29, 29) << " |";
      } else {
        theLine << "|                               |";
      }
      retval = theLine.str();
    } else if (aAbility) {
      int start = line - 6;
      string eff = aAbility->getEffect();
      if (start == 0) {
        theLine << "| " << setw(4) << left << aAbility->getCost() << "| ";
        theLine << setw(23) << left << eff.substr(start*23, 23) << " |";
      } else if (start == 1) {
        theLine << "|------ " << setw(23) << left << eff.substr(start*23, 23) << " |";
      } else {
        theLine << "|                               |";
      }
      retval = theLine.str();
    } else {
      retval = "|                               |";
    }
  } else if (line == 9) {
    retval = "|------                   ------|";
  } else if (line == 10) {
    theLine << "| " << setw(4) << left << getAttack();
    theLine << "|                   |" << setw(4) << right << getDefense() << " |";
    retval = theLine.str();
  }
  return retval;
}
  
Minion::~Minion() {}

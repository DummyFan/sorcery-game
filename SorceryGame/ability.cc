#include "ability.h"
#include "board.h"
using namespace std;

Ability::Ability() {}

Ability::Ability(int aCost, string effect): aCost{aCost}, effect{effect} {}

int Ability::getCost() const {
  return aCost;
}

void Ability::setCost(int newCost) {
  aCost = newCost;
}

string Ability::getEffect() const {
  return effect;
}

void Ability::dealDmg(Minion &m) const {
  m.setDefense(m.getDefense() - 1);
}

void Ability::summon(Board *current, int num) const {
  for (int i = 0; i < num; i++) {
    Minion airElemental = {"Air Elemental", 0, 1, 1};
    current->playMinion(airElemental);
  }
}

bool Ability::useAbility(Minion &m, Board *current, Minion &target) const {
  int space = 5 - current->nom();
  if (m.getName() == "Novice Pyromancer") {
    dealDmg(target);
  } else if (m.getName() == "Apprentice Summoner") {
    if (space >= 1) {
      summon(current, 1);
    } else {
      return false;
    }
  } else if (m.getName() == "Master Summoner") {
    if (space > 3) space = 3;
    if (space >= 1) {
      summon(current, space);
    } else {
      return false;
    }
  }
  return true;
}

Ability::~Ability() {}

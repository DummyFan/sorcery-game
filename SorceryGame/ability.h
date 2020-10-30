#ifndef ABILITY_H
#define ABILITY_H
#include "minion.h"
//#include "board.h"
#include <string>

class Board;

class Ability {
  int aCost;
  std::string effect;
 public:
  Ability();
  Ability(int aCost, std::string effect);
  int getCost() const;
  void setCost(int newCost);
  std::string getEffect() const;
  void dealDmg(Minion &m) const;
  void summon(Board *current, int num) const;
  bool useAbility(Minion &m, Board *current, Minion &target) const;
  ~Ability();
};

#endif

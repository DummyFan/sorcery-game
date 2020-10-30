#ifndef SPELL_H
#define SPELL_H
#include <string>
#include "card.h"

class Board;

class Spell: public Card {
  std::string effect;
  void banish(Board *target);
  void banish(Board *target, int index);
  void unsummon(Board *target, int index);
  void recharge(Board *target);
  void disenchant(Board *target, int index);
  void raiseDead(Board *target);
  void blizzard(Board *active, Board *nonActive);
 public:
  Spell();
  Spell(std::string name, int cost, std::string effect);
  Spell(const Spell &other);
  void playCard(Board *first, Board *second);
  void playCard(Board *target, int index);
  std::string printCard(int line);
  ~Spell();
};

#endif

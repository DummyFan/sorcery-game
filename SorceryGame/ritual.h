#ifndef RITUAL_H
#define RITUAL_H
#include "card.h"
#include "trigger.h"

class Ritual: public Card {
  Trigger tAbility;
  int aCost;
  int charge;
 public:
  Ritual();
  Ritual(std::string name, int cost, Trigger tAbility, int aCost, int charge);
  Ritual(const Ritual &other);
  void playCard(Board *first, Board *second);
  void playCard(Board *target, int index);
  std::string printCard(int line);
  void addCharge(int charges);
  void activate(Minion &m, Player &p, Board *current);
  std::string getTriggerType() const;
  ~Ritual();
};

#endif

#ifndef MINION_H
#define MINION_H
#include <string>
#include "card.h"
#include "player.h"

class Trigger;
class Ability;

class Minion: public Card {
  int attack;
  int defense;
  Trigger *tAbility;
  Ability *aAbility;
  int action;
  int actRemain;
 public:
  Minion();
  Minion(std::string name, int cost, int attack, int defense, Trigger *tAbility = nullptr,
         Ability *aAbility = nullptr, int action = 1, int actRemain = 0);
  Minion(const Minion &other);
  int getAttack() const;
  int getDefense() const;
  int getAction() const;
  int getACost() const;
  void setAttack(int newAttack);
  void setDefense(int newDefense);
  void setAction(int newAction);
  void setACost(int newCost);
  void restoreAction();
  std::string getTriggerType() const;
  void activate(Minion &m, Player &p, Board *current);
  void useAbility(Board *current, Minion &target);
  void removeAbility();
  void attackPlayer(Player *other);
  void attackMinion(Board *first, Board *second, Minion *other, int ind1, int ind2);
  void playCard(Board *first, Board *second); 
  void playCard(Board *target, int index);
  std::string printCard(int line);
  ~Minion();
};

#endif

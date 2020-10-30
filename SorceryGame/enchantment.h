#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include "card.h"
#include "minion.h"
#include <string>

class Enchantment: public Card {
  int enAttack;
  int enDefense;
  bool multi;
 public:
  Enchantment();
  Enchantment(std::string name, int cost, int enAttack, int enDefense, bool multi = false);
  Enchantment(Enchantment &other);
  void enchant(Minion &m) const;
  void haste(Minion &m) const;
  void magicFatigue(Minion &m) const;
  void silence(Minion &m) const;
  void playCard(Board *first, Board *second);
  void playCard(Board *target, int index);
  std::string printCard(int line);
  ~Enchantment();
};

#endif
  

#ifndef TRIGGER_H
#define TRIGGER_H
#include <string>
#include "minion.h"
#include "player.h"

class Trigger {
  std::string type;
  std::string effect;
  int enAttack;
  int enDefense;
  int dmg;
 public:
  Trigger();
  Trigger(std::string type, std::string effect, int enAttack = 0, int enDefense = 0, int dmg = 0);
  Trigger(const Trigger &other);
  std::string getType() const;
  std::string getEffect() const;
  void enchant(Minion &m) const;
  void dealDmg(Minion &m) const;
  void gainMagic(Player &p) const;
  void destory(Minion &m) const;
  void takeAction();
  ~Trigger();
};

#endif


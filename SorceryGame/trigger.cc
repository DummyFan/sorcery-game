#include "trigger.h"
using namespace std;

Trigger::Trigger() {}

Trigger::Trigger(string type, string effect, int enAttack, int enDefense, int dmg):
        type{type}, effect{effect}, enAttack{enAttack}, enDefense{enDefense}, dmg{dmg} {}

Trigger::Trigger(const Trigger &other): type{other.type}, effect{other.effect}, enAttack{other.enAttack},
        enDefense{other.enDefense}, dmg{other.dmg} {}

string Trigger::getType() const {
  return type;
}

string Trigger::getEffect() const {
  return effect;
}

void Trigger::enchant(Minion &m) const {
  int newAttack = m.getAttack() + enAttack;
  int newDefense = m.getDefense() + enDefense;
  m.setAttack(newAttack);
  m.setDefense(newDefense);
}

void Trigger::dealDmg(Minion &m) const {
  int newDefense = m.getDefense() - dmg;
  m.setDefense(newDefense);
}

void Trigger::gainMagic(Player &p) const {
  p.incMagic();
}

void Trigger::destory(Minion &m) const {
  m.setDefense(0);
}

Trigger::~Trigger() {}

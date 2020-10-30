#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "card.h"
#include "minion.h"
#include "ritual.h"
#include <vector>

class Board {
  Player *boardOwner;
  std::vector<Minion> boardMinions;
  std::vector<Minion> graveyard;
  std::vector<Ritual> r;
 public:
  Board(Player *boardOwner, std::vector<Minion> boardMinions, std::vector<Minion> graveyard, std::vector<Ritual> r);
  std::string playerName() const;
  Player *getPlayer() const;
  int playerHealth() const;
  int playerMagic() const;
  int nom() const;
  void playMinion(Minion m);
  Minion *getMinion(int index);
  void restoreAllMinion();
  void killMinion(int index);
  void reviveMinion();
  void returnMinion(int index);
  void enchantMinion(int index);
  void damageAllMinion(int damage);
  void checkDeadMinion();
  void playRitual(Ritual rtl);
  Ritual *getRitual();
  void chargeRitual(int charges);
  void removeRitual();
  void printFirstBoard();
  void printSecondBoard();
  void displayBoard(Board A, Board B);
  void freeGarbage();
};

#endif

  

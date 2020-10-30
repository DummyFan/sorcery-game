#ifndef CARD_H
#define CARD_H
#include <string>

class Board;

class Card {
  std::string name;
  int cost;
 public:
  Card();
  Card(std::string name, int cost);
  std::string getName() const;
  int getCost() const;
  virtual void playCard(Board *first, Board *second) = 0;
  virtual void playCard(Board *target, int index) = 0;
  virtual std::string printCard(int line) = 0; 
  virtual ~Card() = 0;
};

#endif

#include <string>
#include "card.h"
using namespace std;

Card::Card() {};

Card::Card(string name, int cost): 
  name{name}, cost{cost} {}

  string Card::getName() const {
    return name;
  }

  int Card::getCost() const {
    return cost;
  }

Card::~Card() {}

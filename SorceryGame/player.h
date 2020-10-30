#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

class Player {
  std::string name;
  std::vector<std::string> hand;
  std::vector<std::string> deck;
  int magic;
  int magicCap;
  int health;
 public:
  Player(std::string name, std::vector<std::string> hand, std::vector<std::string> deck, int magic = 3, int magicCap = 3, int health = 20);
  std::string getName() const;
  int getMagic() const;
  void useMagic(int num);
  int getHealth() const;
  void setHealth(int newHealth);
  int handCards() const;
  std::string getCard(int index);
  void addHand(std::string cardName);
  void discard(int index);
  bool deckEmpty();
  void draw();
  void shuffle();
  void incMagic();
  void restoreMagic();
};
 
#endif

#include <vector>
#include "board.h"
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <iomanip>
#include <map>
#include "trigger.h"
#include "ability.h"
using namespace std;

std::map <string, Minion> minionCards;

Trigger *mlp11 = new Trigger{"MLP", "Gain +1/+1 whenever a minion leaves play."};
Trigger *mep1 = new Trigger{"MEP", "Whenever an opponent's minion enters play, deal 1 damage to it."};
Trigger *eot01 = new Trigger{"EOT", "At the end of your turn, all your minions gain +0/+1."};
Ability *dmg1 = new Ability{1, "Deal 1 damage to target minion"};
Ability *summon11 = new Ability{1, "Summon a 1/1 air elemental"};
Ability *summon13 = new Ability{2, "Summon up to three 1/1 air elementals"};

Board::Board(Player *boardOwner, vector<Minion> boardMinions, vector<Minion> graveyard, vector<Ritual> r): 
       boardOwner{boardOwner}, boardMinions{boardMinions}, graveyard{graveyard}, r{r} {}

string Board::playerName() const {
  return boardOwner->getName();
}

Player *Board::getPlayer() const {
  return boardOwner;
}

int Board::playerHealth() const {
  return boardOwner->getHealth();
}

int Board::playerMagic() const {
  return boardOwner->getMagic();
}

int Board::nom() const {
  return boardMinions.size();
}

void Board::playMinion(Minion m) {
  boardMinions.push_back(m);
}

Minion *Board::getMinion(int index) {
  return &boardMinions[index-1];
}

void Board::restoreAllMinion() {
  for (int i = 0; i < nom(); i++) {
    boardMinions[i].restoreAction();
  }
}

void Board::killMinion(int index) {
  minionCards["Air Elemental"] = {"Air Elemental", 0, 1, 1};
  minionCards["Earth Elemental"] = {"Earth Elemental", 3, 4, 4};
  minionCards["Bone Golem"] = {"Bone Golem", 2, 1, 3, mlp11};
  minionCards["Fire Elemental"] = {"Fire Elemental", 2, 2, 2, mep1};
  minionCards["Potion Seller"] = {"Potion Seller", 2, 1, 3, eot01};
  minionCards["Novice Pyromancer"] = {"Novice Pyromancer", 1, 0, 1, nullptr, dmg1};
  minionCards["Apprentice Summoner"] = {"Apprentice Summoner", 1, 1, 1, nullptr, summon11};
  minionCards["Master Summoner"] = {"Master Summoner", 3, 2, 3, nullptr, summon13};


  string minionName = boardMinions[index-1].getName();
  Minion m = minionCards[minionName];
  graveyard.push_back(m);
  boardMinions.erase(boardMinions.begin() + index - 1);
}

void Board::reviveMinion() {
  boardMinions.push_back(std::move((graveyard[graveyard.size()-1])));
  graveyard.pop_back();
  (boardMinions.end()-1)->setDefense(1);
}

void Board::returnMinion(int index) {
  string minionName = (boardMinions.begin() + index - 1)->getName();
  boardMinions.erase(boardMinions.begin() + index - 1);
  if (boardOwner->handCards() < 5) {
    boardOwner->addHand(minionName);
  }
}

void Board::damageAllMinion(int damage) {
  for (unsigned int i = 0; i < boardMinions.size(); i++) {
    int defense = boardMinions[i].getDefense();
    defense -= damage;
    boardMinions[i].setDefense(defense);
    if (boardMinions[i].getDefense() <= 0) {
      killMinion(i+1);
    }
  }
}

void Board::checkDeadMinion() {
  for (unsigned int i = 0; i < boardMinions.size(); i++) {
    if (boardMinions[i].getDefense() <= 0) {
      killMinion(i+1);
    }
  }
}

void Board::playRitual(Ritual rtl) {
  if (r.size() > 0) {
    r.pop_back();
  }
  r.push_back(rtl);
}

Ritual *Board::getRitual() {
  if (r.size() > 0) {
    return &(r[r.size()-1]);
  }
  return nullptr;
}

void Board::chargeRitual(int charges) {
  if (r.size() > 0) {
    r[r.size()-1].addCharge(charges);
  }
}

void Board::removeRitual() {
  if (r.size() > 0) {
    r.pop_back();
  }
}

void Board::printFirstBoard() {
  string boarder = "|-------------------------------|";
  string empty = "                                 ";
  string space = "|                               |";

  for (int i = 1; i <= 11; i++) {
    ostringstream oss;
    string output;
    int nor = r.size();
    if (i == 1||i == 11) {
      oss << "|";
      if (nor > 0) {
        oss << r[nor-1].printCard(i);
      } else {
        oss << boarder;
      }
      oss << empty << boarder << empty;
      if (graveyard.size() > 0) {
        oss << graveyard[graveyard.size() - 1].printCard(i);
      } else {
        oss << space;
      }
      oss << "|";
      output = oss.str();
    } else if (i == 4) {
      oss << "|";
      if (nor > 0) {
        oss << r[nor-1].printCard(i);
      } else {
        oss << space;
      }
      oss << empty << "|";
      int ws = (31 - playerName().length())/2;
      string nameLine;
      for (int j = 0; j < ws; j++) { 
        nameLine += " ";
      }
      nameLine += playerName();
      oss << left << setw(31) << nameLine << "|" << empty;
      if (graveyard.size() > 0) {
        oss << graveyard[graveyard.size() - 1].printCard(i);
      } else {
        oss << space;
      }
      oss << "|";
      output = oss.str();
    } else if (i == 9) {
      oss << "|";
      if (nor > 0) {
        oss << r[nor-1].printCard(i);
      } else {
        oss << space;
      }
      oss << empty << "|------                   ------|" << empty;
      if (graveyard.size() > 0) {
        oss << graveyard[graveyard.size() - 1].printCard(i);
      } else {
        oss << space;
      }
      oss << "|";
      output = oss.str();
    } else if (i == 10) {
      int mag = boardOwner->getMagic();
      oss << "|";
      if (nor > 0) {
        oss << r[nor-1].printCard(i);
      } else {
        oss << space;
      }
      oss << empty << "|" << setw(4) << right << playerHealth() << " |                   | ";
      oss << setw(4) << left << mag << "|" << empty;
      if (graveyard.size() > 0) {
        oss << graveyard[graveyard.size() - 1].printCard(i);
      } else {
        oss << space;
      }
      oss << "|";
      output = oss.str();
    } else {
      oss << "|";
      if (nor > 0) {
        oss << r[nor-1].printCard(i);
      } else {
        oss << space;
      }
      oss << empty << space << empty;
      if (graveyard.size() > 0) {
        oss << graveyard[graveyard.size() - 1].printCard(i);
        
      } else {
        oss << space;
      }
      oss << "|";
      output = oss.str();
    }
    cout << output << endl;
  }
}

void Board::printSecondBoard() {
  string boarder = "|-------------------------------|";
  string space = "|                               |";

  for (int i = 1; i <= 11; i++) {
    ostringstream oss;
    string output;
    int minionSpace = 5 - boardMinions.size();
    oss << "|";
    for (unsigned int j = 0; j < boardMinions.size(); j++) {
      oss << boardMinions[j].printCard(i);
    }
    for (int j = 0; j < minionSpace; j++) {
      if (i == 1||i == 11) {
        oss << boarder;
      } else {
        oss << space;
      }
    }
    oss << "|";
    output = oss.str();
    cout << output << endl;
  }  
}

void displayBoard(Board A, Board B) {
  string boarder = "|-------------------------------|";
  string empty = "                                 ";
  string space = "|                               |";
  cout << setfill('-') << setw(167) << "" << endl;

  A.printFirstBoard();
  A.printSecondBoard();
  
  cout << "|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
  cout << "|                                                                 _____                                                                                               |" << endl;
  cout << "|                                                                / ____|                                                                                              |" << endl;
  cout << "|                                                               | (___   ___  _ __ ___ ___ _ __ _   _                                                                 |" << endl;
  cout << "|                                                                \\___ \\ / _ \\| '__/ __/ _ \\ '__| | | |                                                                |" << endl;
  cout << "|                                                                ____) | (_) | | | (_|  __/ |  | |_| |                                                                |" << endl;
  cout << "|                                                               |_____/ \\___/|_|  \\___\\___|_|   \\__, |                                                                |" << endl;
  cout << "|                                                                                                __/ |                                                                |" << endl;
  cout << "|                                                                                               |___/                                                                 |" << endl;
  cout << "|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

  B.printSecondBoard();
  B.printFirstBoard();
  cout << setfill('-') << setw(167) << "" << endl;
}

void freeGarbage() {
  delete mlp11;
  delete mep1;
  delete eot01;
  delete dmg1;
  delete summon11;
  delete summon13;
}

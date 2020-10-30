#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "board.h"
#include "player.h"
#include "card.h"
#include "minion.h"
#include "spell.h"
#include "ritual.h"
#include "trigger.h"
#include "ability.h"
#include "cardLibrary.h"
#include "enchantment.h"
#include <map>
using namespace std;

vector<string> loadDeck(string file) {
  vector<string> deck;
  ifstream deckFile (file);
  string cardName;
  while (getline(deckFile, cardName)) {
    deck.push_back(cardName);
  }
  return deck;
}

void displayBoard(Board A, Board B);

void freeGarbage();

void checkTrigger(string type, Minion *m, Player *a, Player *b, Board *current, Board *other) {
  Ritual *rA = current->getRitual();
  Ritual *rB = other->getRitual();
  Minion *temp;
  if (rA && (rA->getTriggerType() == type)) {
    rA->activate(*m, *a, current);
  }

  for (int i = 1; i <= current->nom(); i++) {
    temp = current->getMinion(i);
    if (temp->getTriggerType() == type) {
      temp->activate(*m, *a, current);
    }
  }

  if (rB && (rB->getTriggerType() == type)) {
    rB->activate(*m, *b, current);   
  }

  for (int i = 1; i <= other->nom(); i++) {
    temp = other->getMinion(i);
    if (temp->getTriggerType() == type) temp->activate(*m, *b, current);
  }
}  

int main(int argc, char *argv[]) {
  std::map <string, Card*> allCards;
  std::map <string, Minion> minionCards;

  allCards["Air Elemental"] = &airElemental;
  allCards["Earth Elemental"] = &earthElemental;
  allCards["Bone Golem"] = &boneGolem;
  allCards["Fire Elemental"] = &fireElemental;
  allCards["Potion Seller"] = &potionSeller;
  allCards["Novice Pyromancer"] = &novicePyromancer;
  allCards["Apprentice Summoner"] = &apprenticeSummoner;
  allCards["Master Summoner"] = &masterSummoner;
  allCards["Banish"] = &banish;
  allCards["Unsummon"] = &unsummon;
  allCards["Recharge"] = &recharge;
  allCards["Disenchant"] = &disenchant;
  allCards["Raise Dead"] = &raiseDead;
  allCards["Blizzard"] = &blizzard;
  allCards["Dark Ritual"] = &darkRitual;
  allCards["Aura of Power"] = &auraOfPower;
  allCards["Standstill"] = &standstill;
  allCards["Giant Strength"] = &giantStrength;
  allCards["Enrage"] = &enrage;
  allCards["Haste"] = &haste;
  allCards["Magic Fatigue"] = &magicFatigue;
  allCards["Silence"] = &silence;

  string nameA, nameB;
  vector<string> deck1 = loadDeck("default.deck");
  vector<string> deck2 = loadDeck("default.deck");
  bool testing = false;

  for (int i = 1; i < argc; i++) {
    string theArg = argv[i];
    if (theArg == "-init") {
      string initSetting = argv[i+1];
      ifstream Setting (initSetting);
      if (Setting.is_open()) {
        getline(Setting, nameA);
        getline(Setting, nameB);
        ofstream input ("Input.txt");
        string line;
        while (getline(Setting, line)) {
          input << line << endl;
        }
      }
      Setting.close();
    } else if (theArg == "-deck1") {
      deck1 = loadDeck(argv[i+1]);
    } else if (theArg == "-deck2") {
      deck2 = loadDeck(argv[i+1]);
    } else if (theArg == "-testing") {
      cout << "Test mode enabled" << endl;
      testing = true;
    } else if (theArg == "-graphics") {
      cout << "Graphics is not implemented" << endl;
    }
  }

  vector<string> handA;
  vector<string> handB;
  Player PlayerA = {nameA, handA, deck1};
  Player PlayerB = {nameB, handB, deck2};
  vector<Minion> minionA;
  vector<Minion> minionB;
  vector<Minion> graveyardA;
  vector<Minion> graveyardB;
  vector<Ritual> rA;
  vector<Ritual> rB;
  Board boardA = {&PlayerA, minionA, graveyardA, rA};
  Board boardB = {&PlayerB, minionB, graveyardB, rB};

  if (!testing) {
    PlayerA.shuffle();
    PlayerB.shuffle();
    PlayerB.shuffle();
  }
  for (int i = 0; i < 5; i++) {
    PlayerA.draw();
    PlayerB.draw();
  }

  cout << "Game starts!" << endl;

  string cmd;
  Player *currentPlayer = &PlayerA;
  Player *otherPlayer = &PlayerB;
  Board *currentBoard = &boardA;
  Board *otherBoard = &boardB;

  cout << "It's " << currentPlayer->getName() << "'s turn" << endl;
  currentPlayer->incMagic();
  currentPlayer->restoreMagic();
  Minion *recentM;
  while (getline(cin, cmd)) {
    if (cmd == "help") {
      cout << "Commands: help -- Display this message." << endl;
      cout << "          end  -- End the current player's turn." << endl;
      cout << "          quit -- End the game." << endl;
      cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
      cout << "          attack minion -- Orders minion to attack the opponent." << endl;
      cout << "          play card [target-player target-card] -- Play card, optionally targing" << endl;
      cout << "                                              target-card owned by target-player" << endl;
      cout << "          use minion [target-player target-card] -- Use minion's special ability," << endl;
      cout << "                          optionally targeting target-card owned by target-player" << endl;
      cout << "          inspect minion -- View a minion's card and all enchantments on that minion" << endl;
      cout << "          hand -- Describe all cards in your hand." << endl;
      cout << "          board -- Describe all cards on the board." << endl;
    } else if (cmd == "end") {
      checkTrigger("EOT", recentM, currentPlayer, otherPlayer, currentBoard, otherBoard);

      currentPlayer = (currentPlayer == &PlayerA)? &PlayerB : &PlayerA;
      currentBoard = (currentBoard == &boardA)? &boardB : &boardA;
      otherPlayer = (otherPlayer == &PlayerA)? &PlayerB : &PlayerA;
      otherBoard = (otherBoard == &boardA)? &boardB : &boardA;

      cout << "It's " << currentPlayer->getName() << "'s turn" << endl;
      currentPlayer->incMagic();
      currentBoard->restoreAllMinion(); 
      checkTrigger("SOT", recentM, currentPlayer, otherPlayer, currentBoard, otherBoard);
      currentPlayer->restoreMagic();
      
      if (currentPlayer->deckEmpty()) {
        cout << "Your deck is empty" << endl;
        continue;
      }
      if (currentPlayer->handCards() < 5) {
        currentPlayer->draw();
      }
    } else if (cmd == "quit") {
      cout << "Game terminated." << endl;
      break;
    } else if (cmd == "draw" && testing) {
      if (currentPlayer->deckEmpty()) {
        cout << "Your deck is empty" << endl;
        continue;
      }
      if (currentPlayer->handCards() < 5) {
        currentPlayer->draw();
      }
    } else if (cmd == "hand") {
      for (int i = 1; i <= 11; i++) {
        ostringstream oss;
        for (int j = 1; j <= currentPlayer->handCards(); j++) {
          oss << allCards[currentPlayer->getCard(j)]->printCard(i);
        }
        string prt = oss.str();
        cout << prt << endl;
      }
    } else if (cmd == "board") {
      displayBoard(boardA, boardB);
    } else {
      istringstream iss (cmd);
      string arg;
      iss >> arg;
      if (arg == "attack") {
        int minionI;
        int minionJ;
        iss >> minionI;
        if (minionI > currentBoard->nom() || minionI < 1) {
          cout << "Invalid index, please try again." << endl;
          continue;
        }
        if (iss >> minionJ) {
          if (minionJ > otherBoard->nom() || minionJ < 1) {
            cout << "Invalid index, please try again." << endl;
            continue;
          }

          Minion *other = otherBoard->getMinion(minionJ);
          (currentBoard->getMinion(minionI))->attackMinion(currentBoard, otherBoard, other, minionI, minionJ);
        } else {
          (currentBoard->getMinion(minionI))->attackPlayer(otherPlayer);
        }
        if (otherPlayer->getHealth() <= 0) {
          cout << currentPlayer->getName() << " wins!" << endl;
          cout << "Game terminated" << endl;
          break;
        }
      } else if (arg == "play") {
        int minionNum = currentBoard->nom();
        int cardI;
        int tar_player;
        int tar_card;
        iss >> cardI;
        if (cardI < 1 || cardI > currentPlayer->handCards()) {
          cout << "Invalid index, please try again." << endl;
          continue;
        }
        string cardPlayed = currentPlayer->getCard(cardI);
        if (allCards[cardPlayed]->getCost() > currentPlayer->getMagic()) {
          cout << "Not enough magic, try another command" << endl;
          continue;
        }
        if (iss >> tar_player) {
          iss >> tar_card;
          if (tar_card > otherBoard->nom() || tar_card < 1) {
            cout << "Invalid index, please try again." << endl;
            continue;
          }
          if (tar_player == 1) {
            allCards[cardPlayed]->playCard(&boardA, tar_card);
          } else {
            allCards[cardPlayed]->playCard(&boardB, tar_card);
          }
        } else {
          allCards[cardPlayed]->playCard(currentBoard, otherBoard);
        }
        if (currentBoard->nom() > minionNum) {
          recentM = currentBoard->getMinion(currentBoard->nom());
          checkTrigger("MEP", recentM, currentPlayer, otherPlayer, currentBoard, otherBoard);
        }
        currentBoard->checkDeadMinion();
        otherBoard->checkDeadMinion();
        currentPlayer->discard(cardI);
        currentPlayer->useMagic(allCards[cardPlayed]->getCost());
      } else if (arg == "use") {
        int minionNum = currentBoard->nom();
        int cardI;
        int tar_player;
        int tar_card;
        iss >> cardI;
        if (cardI < 1 || cardI > currentPlayer->handCards()) {
          cout << "Invalid index, please try again." << endl;
          continue;
        }
        Minion *minionUsed = currentBoard->getMinion(cardI);
        if (minionUsed->getACost() > currentPlayer->getMagic()) {
          cout << "Not enough magic, try another command" << endl;
          continue;
        }
        if (iss >> tar_player) {
          iss >> tar_card;
          if (tar_card > otherBoard->nom() || tar_card < 1) {
            cout << "Invalid index, please try again." << endl;
            continue;
          }
          if (tar_player == 1) {
            minionUsed->useAbility(&boardA, *(boardA.getMinion(tar_card)));
          } else {
            minionUsed->useAbility(&boardB, *(boardB.getMinion(tar_card)));
          }
        } else {
          minionUsed->useAbility(currentBoard, *minionUsed);
        }
        if (currentBoard->nom() > minionNum) {
          recentM = currentBoard->getMinion(currentBoard->nom());
          checkTrigger("MEP", recentM, currentPlayer, otherPlayer, currentBoard, otherBoard);
        }
        currentBoard->checkDeadMinion();
        otherBoard->checkDeadMinion();
        currentPlayer->useMagic(minionUsed->getACost());
      } else if (arg == "inspect") {
        int cardI;
        iss >> cardI;
        cout << "Inspecting minion " << cardI << endl;
      } else if (arg == "discard" && testing) {
        int cardI;
        iss >> cardI;
        currentPlayer->discard(cardI);
      } else {
        cout << "Invalid command, please try again. Type -help for explanation of commands" << endl;
        continue;
      }
    }
  }
  freeGarbage();
}


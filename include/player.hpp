#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "main.hpp"

namespace CATAN {

// Class for storing information about each player
class Player {
private:
  int resources[NUM_RESOURCES]; // stores the number or resource cards
  int hand;                     // for non-resource cards
  int score;
  int countCards();
  void removeCard();
  void offerTrade(Player *);

public:
  Player();
  void clearHand();
  void runTurn();
  bool checkCost(const int *);
  void getResource(Resources, int);
  void acceptTrade(Player *, int *, int *);
};
}

#endif
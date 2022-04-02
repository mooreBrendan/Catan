#include "main.hpp"

using namespace CATAN;

// TODO: actually handle trade offer
// handles being offered a trade
void Player::acceptTrade(Player *trader, int *from, int *to) {}

// TODO: actually handle offering a trade
// handlse offering a trade
void Player::offerTrade(Player *) {}

// returns how many of a resource the player has
void Player::getResource(Resources resource, int num) {
  resources[resource] += num;
}

// count how many resource cards a player has
int Player::countCards() {
  int sum = 0;
  for (int i = 0; i < NUM_RESOURCES; i++) {
    sum += resources[i];
  }
  return sum;
}

// handles the user having to remove half of their hand if it is too large
void Player::clearHand() {
  int cardCount = countCards();
  if (cardCount >= 7) {
    // remove half of hand
    for (int i = 0; i < cardCount / 2; i++) {
      removeCard();
    }
  }
}

// TODO: actually prompt user to delete their cards
// prompts user to remove a card
void Player::removeCard() {}

// checks if player can afford a purchase
bool Player::checkCost(const int *cost) {
  for (int i = 0; i < NUM_RESOURCES; i++) {
    if (resources[i] < cost[i]) {
      return false;
    }
  }
  for (int i = 0; i < NUM_RESOURCES; i++) {
    resources[i] -= cost[i];
  }
  return true;
}

// handles the player initialization
Player::Player() {
  for (int i = 0; i < NUM_RESOURCES; i++) {
    resources[i] = 0;
  }
}

// TODO: actually hanlde each players turn
// runs each player's turn, handling prompt
void Player::runTurn() {}
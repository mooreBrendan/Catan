#include "main.hpp"

using namespace CATAN;

int main() {
  // create game object & setup
  Game g;

  // prompt users for initial setup
  g.playerBoardSetup();

  // handle turns until game over
  while (!g.isOver()) {
    g.run();
  }

  // display who won
  g.handleWinner();
  return 0;
}
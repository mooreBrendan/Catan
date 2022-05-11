#ifndef GAME_HPP
#define GAME_HPP

#include "main.hpp"

namespace CATAN {
// Class for storing information about the game
class Game {
private:
  Tile *tiles;
  Player *players;
  Node *nodes;
  bool ended;
  int numPlayers;
  int numTiles;
  int numNodes;
  int hist[11];
  int playerTurn;
  void deal();
  void initTileArray();
  void initTileGraph();
  void initTileRolls();
  void initTileResources();
  Node *getNewNodePointer();

public:
  Game();
  ~Game();
  void generateBoard();
  int askNumPlayers();
  void playerBoardSetup();
  bool isOver();
  void handleWinner();
  int roll();
  void run();
  void save();
  void load();
};
}

#endif
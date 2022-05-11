#include "main.hpp"

using namespace CATAN;
// checks if game is over
bool Game::isOver() { return ended; }

// prompt the creator for the number of players
int Game::askNumPlayers() {
  // TODO: actually prompt for number
  return 4;
}

// creates the array to store the tles
void Game::initTileArray() {
  // calculate the neccesary number of tiles
  numTiles = 2 * SIDE_LENGTH - 1; // calcualte for mid row

  // rows decreasing in size to top&bot row
  for (int i = 0; i < SIDE_LENGTH; i++) {
    numTiles += 2 * (SIDE_LENGTH + i); // add tiles for top AND bottom
  }

#ifdef DEBUG
  // debugging print statements
  std::cout << "Tile size: " << sizeof(Tile) << std::endl;
  std::cout << "Node size: " << sizeof(Node) << std::endl;
  std::cout << "Node* size: " << sizeof(Node *) << std::endl;
  std::cout << "Edge size: " << sizeof(Edge) << std::endl;
  std::cout << "Edge* size: " << sizeof(Edge *) << std::endl;
#endif

  // create the array
  int temp = sizeof(Tile) * numTiles; // DEBUG: not necessary, need to remove
  tiles = new Tile[numTiles];
}

// DEBUG: not needed, can remove with testing
/*
void Game::initTileGraph() {
  int index = 0; // stores the current working index w/o calculations
  int prevIndex = -1;
  Node *tempNode; // stores the node to be merged

  // increasing size
  for (int i = 0; i < SIDE_LENGTH; i++) {
    // initialize top-left & top node
    tiles[index].addPoint(0, getNewNodePointer());
    if (prevIndex < 0) { // merge above tiles with the new tiles
      tiles[index].addPoint(1, getNewNodePointer());
      tempNode = getNewNodePointer();
      tiles[index].addPoint(2, tempNode);
      for (int j = 1; j < SIDE_LENGTH + i; j++) {
        tiles[index + j].addPoint(0, tempNode);
        tiles[index + j].addPoint(1, getNewNodePointer());
        tempNode = getNewNodePointer();
        tiles[index].addPoint(2, tempNode);
      }
    } else {
      // top
      tempNode = getNewNodePointer();
      tiles[index].addPoint(1, tempNode);
      tiles[prevIndex].addPoint(4, tempNode);
      // top-left
      tempNode = getNewNodePointer();
      tiles[index].addPoint(2, tempNode);
      tiles[prevIndex].addPoint(5, tempNode);
      for (int j = 1; j < SIDE_LENGTH + i; j++) {
        // top-right
        tiles[index + j].addPoint(0, tempNode);
        // top
        tempNode = getNewNodePointer();
        tiles[index + j].addPoint(1, tempNode);
        tiles[prevIndex + j].addPoint(4, tempNode);
        // top-left
        tempNode = getNewNodePointer();
        tiles[index].addPoint(2, tempNode);
        tiles[prevIndex + j].addPoint(5, tempNode);
      }
    }

    prevIndex = index;
    index += SIDE_LENGTH + i;
  }
  // add bottom-left & bottom-right nodes of middle row
  tiles[prevIndex].addPoint(3, getNewNodePointer());
  tiles[index - 1].addPoint(5, getNewNodePointer());

  // decreasing size
  for (int i = 0; i < SIDE_LENGTH - 1; i++) {
    for (int j = SIDE_LENGTH - 1; j >= 0; j++) {
      // top-right
      tempNode = getNewNodePointer();
      tiles[index + j].addPoint(0, tempNode);
      tiles[prevIndex + j].addPoint(4, tempNode);
      for (int j = 1; j < SIDE_LENGTH + i; j++) {
        // top
        tempNode = getNewNodePointer();
        tiles[index + j].addPoint(1, tempNode);
        tiles[prevIndex + j].addPoint(5, tempNode);
        tiles[prevIndex + j + 1].addPoint(3, tempNode);

        // top-left
        tempNode = getNewNodePointer();
        tiles[index].addPoint(2, tempNode);
        tiles[prevIndex + j + 1].addPoint(4, tempNode);
      }
    }

    // add bottom nodes
    tiles[prevIndex].addPoint(3, getNewNodePointer());
    for (int i = 0; i < SIDE_LENGTH; i++) {
      tiles[prevIndex + i].addPoint(4, getNewNodePointer());
      tempNode = getNewNodePointer();
      tiles[prevIndex + i].addPoint(5, tempNode);
      tiles[prevIndex + i + 1].addPoint(3, tempNode);
    }
  }
}
*/

// lays out the tiles and their neighbors
void Game::initTileGraph() {
  // create first tile
  int currInd, prevInd;
  tiles[0].genNodes();
  currInd = 1;

  // create first row, add neighbor to left
  for (int i = 1; i < SIDE_LENGTH; i++) {
    tiles[currInd].addNeighbor(tiles[i - 1], 5);
    tiles[currInd].genNodes();
    currInd++;
  }
  prevInd = SIDE_LENGTH;

  // create 2nd-mid rows, add neighbors to left,and tops
  for (int i = 1; i < SIDE_LENGTH; i++) {
    // create first tile in row, nothing to left
    tiles[currInd].addNeighbor(tiles[prevInd], 1);
    tiles[currInd].genNodes();
    currInd++;

    // create rest of row adding left and tops
    for (int j = 1; j < SIDE_LENGTH + i; j++) {
      tiles[currInd].addNeighbor(tiles[currInd - 1], 5);
      tiles[currInd].addNeighbor(tiles[prevInd], 0);
      tiles[currInd].addNeighbor(tiles[prevInd + 1], 1);
      tiles[currInd].genNodes();
      prevInd++;
      currInd++;
    }
  }

  // create row one below mid->bottom, left and tops, different order
  for (int i = 1; i < SIDE_LENGTH; i++) {
    // create first tile, nothing to left
    tiles[currInd].addNeighbor(tiles[prevInd], 0);
    tiles[currInd].addNeighbor(tiles[prevInd + 1], 1);
    currInd++;
    prevInd++;

    // create rest of row, left and tops, tops shifted from above
    for (int j = 0; j < SIDE_LENGTH * 2 - 1; j++) {
      tiles[currInd].addNeighbor(tiles[currInd - 1], 5);
      tiles[currInd].addNeighbor(tiles[prevInd], 0);
      tiles[currInd].addNeighbor(tiles[prevInd + 1], 1);
      currInd++;
      prevInd++;
    }
  }

// forming edges
#ifdef DEBUG
  std::cout << "forming edges" << std::endl;
#endif
  for (int i = 0; i < numNodes; i++) {
    tiles[i].formEdges();
  }
}

// sets the resource that each tile has
void Game::initTileResources() {
  int possibleTiles[NUM_RESOURCES];
  int res, ind;

  // create array of tiles with max number of resources
  int maxResources = (int(numTiles / NUM_RESOURCES) + 1) * NUM_RESOURCES;
  for (int i = 0; i < NUM_RESOURCES; i++) {
    possibleTiles[i] = maxResources;
  }

  // for each tile, get a random resource, and set that resource
  for (int i = 0; i < numTiles; i++) {
    do {
      res = rand() % NUM_RESOURCES;
    } while (possibleTiles[res] <= 0);
    tiles[i].setResource(static_cast<Resources>(res)); // convert to enum
    possibleTiles[res]--;
  }

  // set robber starting location
  ind = rand() % numTiles;
  tiles[ind].setResource(none);
  tiles[ind].setRobber(true);
}

// sets the dice roll where tile gives out resources
void Game::initTileRolls() {
  int ind;
  // go through each tile and roll a random number for that tile
  for (int i = 0; i < numTiles; i++) {
    ind = rand() % 11;
    tiles[ind].setRollNum(ind + 1);
  }
}

// runs each players turn
void Game::run() {
  // roll and give out resources to all players
  int turnRoll = roll();
  for (int i = 0; i < numTiles; i++) {
    tiles[i].giveResources();
  }

  // handle player turns
  players[playerTurn].runTurn();

  // increment player turn
  playerTurn = (playerTurn + 1) % numPlayers;
}

// runs the sub tasks for generating the game board
void Game::generateBoard() {
  initTileArray();
  initTileGraph();
  initTileResources();
  initTileRolls();
}

// rolls two dice
int Game::roll() {
  int dice1, dice2;
  dice1 = (rand() % 6) + 1;
  dice2 = (rand() % 6) + 1;
  hist[dice1 + dice2 - 1]++; // add to histogram
  return dice1 + dice2;
}

// runs the initial moves by players
void Game::playerBoardSetup() {
  for (int i = 0; i < numPlayers; i++) {
    // TODO: prompt each user for board setup
  }
}

// a game object that handles creation and running of Catan
Game::Game() {
  // set basic variables
  ended = false;
  playerTurn = 0;

  srand(time(NULL)); // seed the random number generator to get new games

  // initialize player objects
  numPlayers = askNumPlayers();
  players = new Player[numPlayers];
  for (int i = 0; i < numPlayers; i++) {
    players[i] = Player();
  }
  // DEBUG: shuffle players
  std::shuffle(players, players + numPlayers, std::default_random_engine(0));

  // initialize the histogram of rolls, to be displayed at end of game
  for (int i = 0; i < 11; i++) {
    hist[i] = 0;
  }

  // call function to inialize board
  generateBoard();
}

// TODO: handle saving
// handles saving the game
void Game::save() {}

// TODO: handle loading save data
// handles loading the game
void Game::load() {}

// handles what happens when the game is over
void Game::handleWinner() {
  // TODO: handle player win
  std::cout << "a player has won" << std::endl;
}

// destroys the object and frees dynamically created items
Game::~Game() {
  free(players);
  delete tiles;
  //  free(nodes);
}
#ifndef TILES_HPP
#define TILES_HPP

#include "main.hpp"

namespace CATAN {

class Node;
class Edge;

// limits what the resource values can be
// count returns the number of elements in the enum
enum Resources : const int { none = -1, logs, wool, stone, bricks, wheat };

// Class for handling the tiles in Catan
// Tile Node layout, edges go between node of same index and one more mod 6
//			_____
//		 /0   1\
//		|5    2|
//		\4   3/
//     -----
class Tile {
private:
  Resources resource;
  int rollNum;
  bool hasRobber;
  Node *nodes[NUM_SIDES];
  Edge *edges[NUM_SIDES];

public:
  Tile();
  ~Tile();
  void genNodes();
  void formEdges();
  void addNeighbor(Tile, int);
  void setRollNum(int);
  void setResource(Resources);
  int getResource();
  void giveResources();
  void setRobber(bool);
  Node *getNode(int);
  void addSide(int, Edge *); // attach a side
  void addPoint(int, Node *);
};

//*************************************************************************************************************************

class Node {
private:
  Player *player;
  int teir;
  Edge **edges;
  int numEdges;

public:
  Node();
  int alreadyConnected(Node *);
  void giveResource(Resources);
  void setPlayer(Player *);
  void upgrade();
  void addEdge(Edge *);
};

//*************************************************************************************************************************

class Edge {
private:
  Player *player;
  Node *nodes[2];

public:
  Edge(Node *, Node *);
  void setPlayer(Player *);
  Node *getNode(int);
};
}
#endif
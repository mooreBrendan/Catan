#include "main.hpp"

using namespace CATAN;

/*****************************************************************
*****************************************************************
    ███      ▄█   ▄█          ▄████████    ▄████████
▀█████████▄ ███  ███         ███    ███   ███    ███
   ▀███▀▀██ ███▌ ███         ███    █▀    ███    █▀
    ███   ▀ ███▌ ███        ▄███▄▄▄       ███
    ███     ███▌ ███       ▀▀███▀▀▀     ▀███████████
    ███     ███  ███         ███    █▄           ███
    ███     ███  ███▌    ▄   ███    ███    ▄█    ███
   ▄████▀   █▀   █████▄▄██   ██████████  ▄████████▀
                 ▀
*****************************************************************
*****************************************************************/

int Tile::getResource() { return resource; }
void Tile::setResource(Resources r) { resource = r; }
void Tile::setRollNum(int r) { rollNum = r; }
Node *Tile::getNode(int ind) { return nodes[ind]; }
void Tile::addPoint(int point, Node *node) { nodes[point] = node; }
void Tile::addSide(int side, Edge *edge) { edges[side] = edge; }
void Tile::setRobber(bool state) { hasRobber = state; }

void Tile::giveResources() {
  Resources r = none;
  if (hasRobber || resource == r)
    return;
  for (int i = 0; i < NUM_SIDES; i++) {
    nodes[i]->giveResource(resource);
  }
}

Tile::Tile() {
  Resources r = none;
  resource = r;
  hasRobber = false;
  for (int i = 0; i < NUM_SIDES; i++) {
    edges[i] = nullptr;
    nodes[i] = nullptr;
  }
}

void Tile::addNeighbor(Tile neighbor, int side) {
  int dif = NUM_SIDES / 2;
#ifdef DEBUG
  std::out << side << ":" << (side + dif + 1) % NUM_SIDES << std::endl;
  std::out << side + 1 << ":" << (side + dif - 1) % NUM_SIDES << std::endl;
#endif
  nodes[side] = neighbor.getNode((side + dif + 1) % NUM_SIDES);
  nodes[side + 1] = neighbor.getNode((side + dif - 1) % NUM_SIDES);
}

void Tile::genNodes() {
  for (int i = 0; i < NUM_SIDES; i++) {
    if (nodes[i] == nullptr) {
      nodes[i] = new Node();
    }
  }
}

void Tile::formEdges() {
  for (int i = 0; i < NUM_SIDES; i++) {
    try {
      Edge(nodes[i], nodes[i + 1]);
    } catch (const char *) {
      ;
    }
  }
  try {
    Edge(nodes[0], nodes[NUM_SIDES - 1]);
  } catch (const char *) {
    ;
  }
}

Tile::~Tile() {
  for (int i = 0; i < NUM_SIDES; i++) {
    if (nodes[i] != nullptr)
      free(nodes[i]);
    if (edges[i] != nullptr)
      free(edges[i]);
  }
}

/*****************************************************************
*****************************************************************
 ███▄▄▄▄    ▄██████▄  ████████▄     ▄████████    ▄████████
███▀▀▀██▄ ███    ███ ███   ▀███   ███    ███   ███    ███
███   ███ ███    ███ ███    ███   ███    █▀    ███    █▀
███   ███ ███    ███ ███    ███  ▄███▄▄▄       ███
███   ███ ███    ███ ███    ███ ▀▀███▀▀▀     ▀███████████
███   ███ ███    ███ ███    ███   ███    █▄           ███
███   ███ ███    ███ ███   ▄███   ███    ███    ▄█    ███
 ▀█   █▀   ▀██████▀  ████████▀    ██████████  ▄████████▀
*****************************************************************
*****************************************************************/

// handles creating a node
Node::Node() {
  player = nullptr;
  teir = 0;
}

// gives a resource to the owner of a node
void Node::giveResource(Resources resource) {
  if (player == nullptr)
    return;
  player->getResource(resource, teir);
}

// set who owns the node
void Node::setPlayer(Player *pl) {
  TOWN_COST;
  // TODO: check player has cards
  player = pl;
  teir = 1;
}

// upgrade the town on a node
void Node::upgrade() {
  CITY_COST;
  if (teir == 1) {
    // TODO: check player has cards
    teir += 1;
  }
}

// add an edge to the node
void Node::addEdge(Edge *edge) {
  // increment number of edges
  numEdges++;

  // initialize a larger array to store the nodes
  Edge **newEdges = new Edge *[numEdges];
  for (int i; i < numEdges - 1; i++) {
    newEdges[i] = edges[i];
  }
  // add new edge
  newEdges[numEdges - 1] = edge;

  // delete the old array and make the new array active
  delete edges;
  edges = newEdges;
}

// check if node already has a connection to another node
int Node::alreadyConnected(Node *node) {
  for (int i = 0; i < numEdges; i++) {
    if (edges[i]->getNode(1) == node || edges[i]->getNode(2) == node) {
      return 1;
    }
  }
  return 0;
}

/*************************************************************
**************************************************************
   ▄████████ ████████▄     ▄██████▄     ▄████████    ▄████████
  ███    ███ ███   ▀███   ███    ███   ███    ███   ███    ███
  ███    █▀  ███    ███   ███    █▀    ███    █▀    ███    █▀
 ▄███▄▄▄     ███    ███  ▄███         ▄███▄▄▄       ███
▀▀███▀▀▀     ███    ███ ▀▀███ ████▄  ▀▀███▀▀▀     ▀███████████
  ███    █▄  ███    ███   ███    ███   ███    █▄           ███
  ███    ███ ███   ▄███   ███    ███   ███    ███    ▄█    ███
  ██████████ ████████▀    ████████▀    ██████████  ▄████████▀
**************************************************************
*************************************************************/

// creates an edge between two nodes
Edge::Edge(Node *N1, Node *N2) {
  // check if already connected
  if (N1->alreadyConnected(N2)) {
    throw "already exists";
  }

  // initialize edge and attach it to nodes
  player = nullptr;
  nodes[1] = N1;
  N1->addEdge(this);
  nodes[2] = N2;
  N2->addEdge(this);
}

// sets the owner of the edge
void Edge::setPlayer(Player *pl) {
  ROAD_COST;
  // TODO: remove cost from player
  player = pl;
}

// returns anode at position 1 or 2
Node *Edge::getNode(int pos) {
  return pos < 1 || pos > 2 ? nullptr : nodes[pos];
}

#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "bits/stdc++.h"

#define NUM_SIDES 6
#define SIDE_LENGTH 3
#define NUM_RESOURCES 5
#define TOWN_COST const int townCost[] = {1, 1, 1, 0, 1}
#define CITY_COST const int cityCost[] = {1, 1, 0, 0, 1}
#define ROAD_COST const int roadCost[] = {0, 0, 1, 1, 0}

namespace CATAN {

// limits what the resource values can be
// count returns the number of elements in the enum
enum Resources : const int { none = -1, logs, wool, stone, bricks, wheat };
}

#include "player.hpp"
#include "tiles.hpp"
#include "game.hpp"

#endif
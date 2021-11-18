#ifndef GRID_H
#define GRID_H

#include "Coord.hpp"

struct GridNode {
  Coord coord;
  int dist;
};

const int neighborX[] = {-1, 0, 1, -1, 1, -1,  0,  1};
const int neighborY[] = { 1, 1, 1,  0, 0, -1, -1, -1};

class Grid {
  public:
    Grid(int n, int m): n(n), m(m) {};

    int findShortestPath(Coord source, Coord dest);

  private:
    bool isValidCoord(int x, int y);

    int n, m;
};


#endif
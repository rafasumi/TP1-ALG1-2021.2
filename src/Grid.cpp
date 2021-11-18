#include "Grid.hpp"
#include <queue>

bool Grid::isValidCoord(int x, int y) {
  return ((x >= 0) && (x < n) && (y >= 0) && (y < m));
}

int Grid::findShortestPath(Coord source, Coord dest) {
  bool** visited = new bool*[n];
  for (int i = 0; i < n; i++) 
    visited[i] = new bool[m];
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      visited[i][j] = false;
    }
  }

  visited[source.x()][source.y()] = true;

  std::queue<GridNode> queue;

  GridNode src = {source, 0};
  queue.push(src);

  while (!queue.empty()) {
    GridNode curr = queue.front();
    Coord coord = curr.coord;

    if (coord.x() == dest.x() && coord.y() == dest.y())
      return (curr.dist - 1);

    queue.pop();

    for (int i = 0; i < 8; i++) {
      int x = coord.x() + neighborX[i];
      int y = coord.y() + neighborY[i];

      if (isValidCoord(x, y) && !visited[x][y]) {
        visited[x][y] = true;
        GridNode neighbor = { Coord(x, y), curr.dist + 1 };
        queue.push(neighbor);
      }
      
    }
  }

  for (int i = 0; i < m; i++) 
    delete[] visited[i];
  delete[] visited;

  return -1;
}

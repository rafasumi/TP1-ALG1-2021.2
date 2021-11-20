#include "Grid.hpp"
#include <queue>

bool Grid::isValidCoord(int x, int y) {
  return ((x >= 0) && (x < n) && (y >= 0) && (y < m));
}

int Grid::findShortestPath(Coord source, Coord dest) {
  // visited é uma matriz booleana de tamanho NxM que representa se uma determinada posição no grid
  // já foi visitada. De início, todos os valores são setados como falsos
  bool** visited = new bool*[n];
  for (int i = 0; i < n; i++) 
    visited[i] = new bool[m];
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      visited[i][j] = false;
    }
  }

  // A coordenada da origem é marcada como visitada
  visited[source.x()][source.y()] = true;

  // Esta fila contém as próximas posições (nós) que devem ser visitados na busca em largura
  std::queue<GridNode> queue;

  // O nó de origem é o primeiro a ser inserido na fila com distância 0.
  GridNode src = {source, 0};
  queue.push(src);

  while (!queue.empty()) {
    GridNode curr = queue.front();
    Coord coord = curr.coord;

    // Verifica se o nó da iteração atual é o de destino. Se sim, retorna a distância
    // do nó atual menos 1, já que a distância considera o número de nós andados entre
    // a origem e o destino.
    if (coord.x() == dest.x() && coord.y() == dest.y())
      return (curr.dist - 1);

    queue.pop();

    // O for itera por todos os vizinhos do nó atual, utilizando os arrays auxiliares
    // neighborX e neighbor Y
    for (int i = 0; i < 8; i++) {
      int x = coord.x() + neighborX[i];
      int y = coord.y() + neighborY[i];

      // Se o vizinho em questão estiver em uma coordenada válida e não tiver sido visitado ainda,
      // é marcado como visitado e adicionado à fila. A distância é incrementada em 1 em relação ao
      // nó da iteração atual do while.
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

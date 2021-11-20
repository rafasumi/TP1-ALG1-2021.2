#ifndef GRID_H
#define GRID_H

#include "Coord.hpp"

// Struct usado para modelar um nó no grid (um "quadrado") na função de shortest path.
// Esse componente tem uma coordenada e uma distância até o nó de origem da busca.
struct GridNode {
  Coord coord;
  int dist;
};

// Array usado para saber os valores que devem ser somados ao valor de X de uma coordenada no grid
// para se obter todos os seus 8 vizinhos possíveis. Cada valor em uma posição i está diretamente
// relacionado com o valor na posição i de neighborY.
const int neighborX[] = {-1, 0, 1, -1, 1, -1,  0,  1};

// Array usado para saber os valores que devem ser somados ao valor de Y de uma coordenada no grid 
// para se obter todos os seus 8 vizinhos possíveis. Cada valor em uma posição i está diretamente
// relacionado com o valor na posição i de neighborX.
const int neighborY[] = { 1, 1, 1,  0, 0, -1, -1, -1};

// Classe que representa o grid no qual os clientes e lojas e estão.
class Grid {
  public:
    Grid(int n, int m): n(n), m(m) {};

    // Função que acha o menor caminho entre duas coordenadas aplicando um algoritmo de BFS (Breadth-first search).
    int findShortestPath(Coord source, Coord dest);

  private:
    // Função auxiliar para checar se uma coordenada é válida, ou seja, se está dentro dos limites do grid.
    bool isValidCoord(int x, int y);

    int n, m;
};


#endif
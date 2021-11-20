#ifndef COORD_H
#define COORD_H

// Classe que representa a coordenada de uma entidade (loja ou cliente) no grid de tamanho NxM.
class Coord {
  public:
    Coord() {
      this->_x = -1;
      this->_y = -1;
    }

    Coord(int x, int y) {
      this->_x = x;
      this->_y = y;
    }

    int x() {
      return this->_x;
    }

    int y() {
      return this->_y;
    }

  private:
    int _x, _y;

  friend class Client;
  friend class Store;
};

#endif

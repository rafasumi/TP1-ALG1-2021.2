#ifndef STORE_H
#define STORE_H

#include <vector>
#include "Coord.hpp"

class Client;

class Store {
  public:
    Store(int id, int capacity, int x, int y);

    int getId();
    Coord getCoord();
    int proposedClientsQty();

    // Adiciona um cliente no vetor scheduledClients e atualiza o agendamento do cliente.
    void scheduleClient(Client* client);

    // Decrementa o valor de scheduledClients.
    void removeClient();

    // Indica que está sendo feita uma proposta a um cliente. Equivale a incrementar a variável proposedClients.
    void proposeToClient();

    // Verifica se a loja atingiu a sua capacidade. Ou seja, se o número de clientes agendados é igual à capacidade.
    bool isFull();

  private:
    int id;
    int capacity;
    Coord coord;

    // Contador para o número de clientes agendados para a loja.
    int scheduledClients;

    // Atributo que indica a quantidade de clientes para os quais uma loja já fez proposta.
    int proposedClients;
};


#endif
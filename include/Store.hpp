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
    std::vector<int> getScheduledClients();
    int proposedClientsQty();

    // Adiciona um cliente no vetor scheduledClients.
    void scheduleClient(Client* client);

    // Remove um cliente do vetor scheduledClients a patir de seu ID.
    void removeClient(int clientId);

    // Indica que está sendo feita uma proposta a um cliente. Equivale a incrementar a variável proposedClients.
    void proposeToClient();

    // Verifica se a loja atingiu a sua capacidade. Ou seja, se o número de clientes agendados é igual à capacidade.
    bool isFull();

  private:
    int id;
    int capacity;
    Coord coord;

    // Vetor com os IDs de todos os clientes agendados para a loja.
    std::vector<int> scheduledClients;

    // Atributo que indica a quantidade de clientes para os quais uma loja já fez proposta.
    int proposedClients;
};


#endif
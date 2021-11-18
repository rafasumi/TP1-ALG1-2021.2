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

    void scheduleClient(Client* client);
    void removeClient(int clientId);
    void proposeToClient();
    bool isFull();

  private:
    int id;
    int capacity;
    Coord coord;
    std::vector<int> scheduledClients;
    int proposedClients;
};


#endif
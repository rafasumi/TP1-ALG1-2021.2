#include "Store.hpp"
#include "Client.hpp"
#include <algorithm>

Store::Store(int id, int capacity, int x, int y) {
  this->id = id;
  this->capacity = capacity;
  this->coord._x = x;
  this->coord._y = y;
  this->proposedClients = 0;
}

int Store::getId() {
  return this->id;
}

Coord Store::getCoord() {
  return this->coord;
}

std::vector<int> Store::getScheduledClients() {
  return this->scheduledClients;
}

int Store::proposedClientsQty() {
  return this->proposedClients;
}

void Store::scheduleClient(Client* client) {
  this->scheduledClients.push_back(client->getId());
  client->scheduleStore(this->id);
}

void Store::removeClient(int clientId) {
  std::vector<int>::iterator it = std::find(this->scheduledClients.begin(), this->scheduledClients.end(), clientId);
  this->scheduledClients.erase(it);
}

void Store::proposeToClient() {
  this->proposedClients++;
}

bool Store::isFull() {
  return (int)this->scheduledClients.size() == capacity;
}

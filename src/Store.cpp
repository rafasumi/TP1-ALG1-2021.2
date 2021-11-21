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

int Store::proposedClientsQty() {
  return this->proposedClients;
}

void Store::scheduleClient(Client* client) {
  this->scheduledClients++;
  client->scheduleStore(this->id);
}

void Store::removeClient() {
  this->scheduledClients--;
}

void Store::proposeToClient() {
  this->proposedClients++;
}

bool Store::isFull() {
  return this->scheduledClients == capacity;
}

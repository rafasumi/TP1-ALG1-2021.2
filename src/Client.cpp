#include "Client.hpp"
#include <cmath>

Client::Client(int id, int age, std::string state, std::string payment, int x, int y, int storeQty) {
  this->id = id;
  this->age = age;
  this->state = state;
  this->payment = payment;
  this->coord._x = x;
  this->coord._y = y;
  this->ticket = calculateTicket();
  this->scheduledStore = -1;
  this->storeDistances = new int[storeQty];
}

Client::~Client() {
  delete[] this->storeDistances;
}

float Client::calculateTicket() {
  int state_score = state_scores.find(this->state)->second;
  float payment_score = payment_scores.find(this->payment)->second;

  return (std::abs(60 - this->age) + state_score) / payment_score;
}

int Client::getId() {
  return this->id;
}

float Client::getTicket() {
  return this->ticket;
}

int Client::getScheduledStore() {
  return this->scheduledStore;
}

int* Client::getDistances() {
  return this->storeDistances;
}

void Client::setDistances(Grid grid, std::vector<Store*> stores) {
  for (Store* store : stores) {
    int shortestPath = grid.findShortestPath(this->coord, store->getCoord());
    storeDistances[store->getId()] = shortestPath;
  }
}

void Client::scheduleStore(int storeId) {
  this->scheduledStore = storeId;
}

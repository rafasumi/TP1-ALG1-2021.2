#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include "Coord.hpp"
#include "Grid.hpp"
#include "Client.hpp"
#include "Store.hpp"
#include "utils.hpp"

int main(int argc, char const* argv[]) {
  std::ifstream inputFile(argv[1]);
  const char* delim = " ";
  std::string line;

  getline (inputFile, line);
  int n = std::stoi(std::strtok(const_cast<char*>(line.c_str()), delim));
  int m = std::stoi(std::strtok(NULL, delim));

  Grid grid = Grid(n, m);

  int capacity, x, y;
  getline (inputFile, line);
  int storeQty = std::stoi(line);
  std::vector<Store*> stores;
  
  for (int i = 0; i < storeQty; i++) {
    getline (inputFile, line);
    capacity = std::stoi(std::strtok(const_cast<char*>(line.c_str()), delim));
    x = std::stoi(std::strtok(NULL, delim));
    y = std::stoi(std::strtok(NULL, delim));

    Store* store = new Store(i, capacity, x, y);
    stores.push_back(store);
  }

  std::multimap<float, int, std::greater<float>> clientPreferencesMap;

  int age;
  std::string state, payment;
  getline (inputFile, line);
  int clientQty = std::stoi(line);
  std::vector<Client*> clients;

  for (int i = 0; i < clientQty; i++) {
    getline (inputFile, line);
    age = std::stoi(std::strtok(const_cast<char*>(line.c_str()), delim));
    state = std::strtok(NULL, delim);
    payment = std::strtok(NULL, delim);
    x = std::stoi(std::strtok(NULL, delim));
    y = std::stoi(std::strtok(NULL, delim));

    Client* client = new Client(i, age, state, payment, x, y, storeQty);
    client->setPreferences(grid, stores);
    clients.push_back(client);

    clientPreferencesMap.insert(std::pair<float, int>(client->getTicket(), client->getId()));
  }

  inputFile.close();

  std::vector<int> clientPreferences;
  for (auto it : clientPreferencesMap) {
    clientPreferences.push_back(it.second);
  }

  std::vector<std::vector<int>> matching = utils::stableMatching(stores, clients, clientPreferences);

  utils::printResults(matching);

  for (Client* client : clients)
    delete client;
  
  for (Store* store : stores)
    delete store;

  return 0;
}

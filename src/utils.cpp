#include "utils.hpp"
#include <cstring>
#include <deque>
#include <algorithm>
#include <iostream>

void swapStores(std::vector<std::vector<int>>* matching, int oldStore, int newStore, int clientId) {
  auto it = std::find(matching->at(oldStore).begin(), matching->at(oldStore).end(), clientId);
  matching->at(oldStore).erase(it);
  
  matching->at(newStore).push_back(clientId);
}

bool notInQueue(std::deque<Store*> queue, Store* store) {
  return std::find(queue.begin(), queue.end(), store) == queue.end();
}

std::vector<std::vector<int>> utils::stableMatching(
  std::vector<Store*> stores,
  std::vector<Client*> clients,
  std::vector<int> clientPreferences
) {
  bool* matchedClients = new bool[clients.size()];
  std::memset(matchedClients, false, clients.size());

  std::vector<std::vector<int>> matching(stores.size());

  std::deque<Store*> storesQueue;
  for (Store* store : stores)
    storesQueue.push_back(store);

  while(!storesQueue.empty()) {
    Store* store = storesQueue.front(); 
    if (store->isFull() || (store->proposedClientsQty() >= (int)clientPreferences.size())) {
      storesQueue.pop_front();
      continue;
    }

    int clientId = clientPreferences.at(store->proposedClientsQty());
    Client* client = clients.at(clientId);

    store->proposeToClient();
    bool storeIsCloser = client->getPreferences()[store->getId()] < client->getPreferences()[client->getScheduledStore()];
    bool sameDistanceButLowerId = 
      client->getPreferences()[store->getId()] == client->getPreferences()[client->getScheduledStore()] &&
      store->getId() < client->getScheduledStore();

    if (!matchedClients[clientId]) {
      matching[store->getId()].push_back(clientId);
      
      store->scheduleClient(client);
      
      matchedClients[clientId] = true;
    } else if (storeIsCloser || sameDistanceButLowerId) {
      swapStores(&matching, client->getScheduledStore(), store->getId(), clientId);

      stores.at(client->getScheduledStore())->removeClient(clientId);
      if (notInQueue(storesQueue, stores.at(client->getScheduledStore())))
        storesQueue.push_back(stores.at(client->getScheduledStore()));
      
      store->scheduleClient(client);
    }
  }

  delete[] matchedClients;

  return matching;
}

void utils::printResults(std::vector<std::vector<int>> matching) {
  int count = 0;
  for (auto store : matching) {
    std::cout << count << std::endl;
    for (int client : store) {
      std::cout << client << " ";
    }

    count++;

    std::cout << std::endl;
  }

  std::cout << std::endl;
}

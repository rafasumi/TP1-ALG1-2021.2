#include "utils.hpp"
#include <cstring>
#include <deque>
#include <algorithm>
#include <iostream>

// Função auxiliar que troca a loja na qual um cliente está agendado.
void swapStores(std::vector<std::vector<int>>* matching, int oldStore, int newStore, int clientId) {
  auto it = std::find(matching->at(oldStore).begin(), matching->at(oldStore).end(), clientId);
  matching->at(oldStore).erase(it);
  
  matching->at(newStore).push_back(clientId);
}

// Função auxiliar que verifica se uma determinada loja já está na fila do casamento estável.
bool notInQueue(std::deque<Store*> queue, Store* store) {
  return std::find(queue.begin(), queue.end(), store) == queue.end();
}

std::vector<std::vector<int>> utils::stableMatching(
  std::vector<Store*> stores,
  std::vector<Client*> clients,
  std::vector<int> clientsPreferenceList
) {
  // Vetor de vetores que é utilizado para representar o casamento
  std::vector<std::vector<int>> matching(stores.size());

  // Fila (double-ended queue) que contém as lojas que ainda devem/podem fazer propostas
  std::deque<Store*> storesQueue;
  for (Store* store : stores)
    storesQueue.push_back(store);

  while (!storesQueue.empty()) {
    Store* store = storesQueue.front();
    // Verifica se a loja da iteração atual já atingiu o seu limite máximo de clientes ou se já propôs
    // para todos os clientes. Se sim, a loja é retirada da fila e o while vai para a próxima iteração
    if (store->isFull() || (store->proposedClientsQty() >= (int)clientsPreferenceList.size())) {
      storesQueue.pop_front();
      continue;
    }

    // Pega o cliente com maior preferência para o qual a loja ainda não propôs. Esse índice é obtido pelo
    // atributo proposedClients de Store, já que se a loja propôs para i clientes, o próximo cliente para o
    // qual ela não propôs está na posição i+1
    int clientId = clientsPreferenceList.at(store->proposedClientsQty());
    Client* client = clients.at(clientId);

    // Incrementa o valor de proposedClients para a loja em questão
    store->proposeToClient();

    // Estas duas variáveis booleanas representam as condições para as quais um cliente deve aceitar trocar de loja
    bool storeIsCloser = client->getDistances()[store->getId()] < client->getDistances()[client->getScheduledStore()];
    bool sameDistanceButLowerId = 
      client->getDistances()[store->getId()] == client->getDistances()[client->getScheduledStore()] &&
      store->getId() < client->getScheduledStore();

    // Se o cliente ainda não foi alocado, ele imediatamente aceita a proposta da loja
    if (client->getScheduledStore() == -1) {
      matching[store->getId()].push_back(clientId);

      store->scheduleClient(client);
    } else if (storeIsCloser || sameDistanceButLowerId) {
      // Se pelo menos uma das duas condições é válida, o cliente troca para a loja da iteração atual
      swapStores(&matching, client->getScheduledStore(), store->getId(), clientId);

      stores.at(client->getScheduledStore())->removeClient();

      // A loja é adicionada à fila se já não estiver nela
      if (notInQueue(storesQueue, stores.at(client->getScheduledStore())))
        storesQueue.push_back(stores.at(client->getScheduledStore()));
      
      store->scheduleClient(client);
    }
  }

  return matching;
}

void utils::printResults(std::vector<std::vector<int>> matching) {
  int storeCount = 0;
  int clientCount;
  
  for (auto store : matching) {
    std::cout << storeCount << std::endl;
    clientCount = 0;
    for (int client : store) {
      clientCount++;
      std::cout << client;
      if (clientCount < (int)store.size()) std::cout << " ";
    }

    storeCount++;

    std::cout << std::endl;
  }

  std::cout << std::endl;
}

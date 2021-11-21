#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Coord.hpp"
#include "Grid.hpp"
#include "Client.hpp"
#include "Store.hpp"
#include "utils.hpp"

// Função main do programa. É responsável pela leitura do arquivo de input, por instanciar objetos e variáveis
// e pela chamada de funções necessárias para a realização do casamento entre lojas e clientes
int main(int argc, char const* argv[]) {
  // Faz a leitura da primeira linha, que contém o tamanho do grid
  int n, m;
  std::cin >> n >> m;
  Grid grid = Grid(n, m);

  int capacity, x, y;
  // Vetor que contém todas as lojas informadas no input
  std::vector<Store*> stores;
  
  // Faz a leitura das linhas referentes às lojas
  int storeQty;
  std::cin >> storeQty;
  for (int i = 0; i < storeQty; i++) {
    std::cin >> capacity >> x >> y;

    Store* store = new Store(i, capacity, x, y);
    stores.push_back(store);
  }

  // Foi escolhida a estrutura de multimap pois ela insere os elementos de forma ordenada
  // considerando uma determinada chave, no caso o ticket de cada cliente. Dessa forma, a
  // lista de preferência fica ordenada e, como a forma de desempate é a ordem de inserção,
  // os clientes com menor ID terão maior preferência.
  std::multimap<float, int, std::greater<float>> clientsPreferenceMap;

  int age; 
  std::string state, payment;
  // Vetor que contém todos os clientes informados no input
  std::vector<Client*> clients;

  // Faz a leitura das linhas referentes aos clientes
  int clientQty;
  std::cin >> clientQty;
  for (int i = 0; i < clientQty; i++) {
    std::cin >> age >> state >> payment >> x >> y;

    Client* client = new Client(i, age, state, payment, x, y, storeQty);
    // Calcula as distâncias entre o cliente e todas as lojas do problema
    client->setDistances(grid, stores);
    clients.push_back(client);

    clientsPreferenceMap.insert(std::pair<float, int>(client->getTicket(), client->getId()));
  }

  // O vetor extrai os IDs do multimap clientsPreferenceMap para serem usados no casamento estável 
  std::vector<int> clientsPreferenceList;
  for (auto it : clientsPreferenceMap) {
    clientsPreferenceList.push_back(it.second);
  }

  std::vector<std::vector<int>> matching = utils::stableMatching(stores, clients, clientsPreferenceList);

  utils::printResults(matching);

  for (Client* client : clients)
    delete client;
  
  for (Store* store : stores)
    delete store;

  return 0;
}

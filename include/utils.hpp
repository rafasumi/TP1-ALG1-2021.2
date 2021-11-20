#include <vector>
#include "Client.hpp"
#include "Store.hpp"

namespace utils {
  // Função que realiza o casamento estável para um vetor de lojas e um vetor de clientes. Também recebe a lista (ordenada)
  // de preferências de clientes para as lojas.
  std::vector<std::vector<int>> stableMatching(
    std::vector<Store*> stores,
    std::vector<Client*> clients,
    std::vector<int> clientsPreferenceList
  );

  void printResults(std::vector<std::vector<int>> matching);
}

#include <vector>
#include "Client.hpp"
#include "Store.hpp"

namespace utils {
  std::vector<std::vector<int>> stableMatching(
    std::vector<Store*> stores,
    std::vector<Client*> clients,
    std::vector<int> clientPreferences
  );

  void printResults(std::vector<std::vector<int>> matching);
}

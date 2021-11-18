#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <map>
#include <vector>
#include "Grid.hpp"
#include "Coord.hpp"
#include "Store.hpp"

const std::map<std::string, int> state_scores = {
  {"MG",  0},
  {"PR", 10},
  {"SP", 20},
  {"SC", 30},
  {"RJ", 40},
  {"RN", 50},
  {"RS", 60},
};

const std::map<std::string, int> payment_scores = {
  {"DINHEIRO", 1},
  {"DEBITO",   2},
  {"CREDITO",  3},
};

class Client{
  public:
    Client(int id, int age, std::string state, std::string payment, int x, int y, int storeQty);
    ~Client();

    int getId();
    float getTicket();
    int getScheduledStore();
    int* getPreferences();

    void setPreferences(Grid grid, std::vector<Store*> stores);
    void scheduleStore(int storeId);

  private:
    float calculateTicket();

    int id;
    int age;
    std::string state;
    std::string payment;
    Coord coord;
    float ticket;
    int scheduledStore;
    int* storePreferences;
};

#endif

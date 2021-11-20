#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <map>
#include <vector>
#include "Grid.hpp"
#include "Coord.hpp"
#include "Store.hpp"

// Mapa usado para associar cada estado a seu score.
const std::map<std::string, int> state_scores = {
  {"MG",  0},
  {"PR", 10},
  {"SP", 20},
  {"SC", 30},
  {"RJ", 40},
  {"RN", 50},
  {"RS", 60},
};

// Mapa usado para associar cada meio de pagamento a seu score.
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
    int* getDistances();
    
    // Popula o array storeDistances aplicando o algoritmo de shortest paths para um vetor com todas as lojas.
    void setDistances(Grid grid, std::vector<Store*> stores);
    void scheduleStore(int storeId);

  private:
    // Função auxiliar para calcular o ticket de um cliente considerando a fórmula passada.
    float calculateTicket();

    int id;
    int age;
    std::string state;
    std::string payment;
    Coord coord;
    float ticket;
    
    // Atributo que representa o da ID loja para o qual um cliente foi agendado. Por padrão é -1.
    int scheduledStore;
    
    // Array dinâmico de inteiros que contém as distâncias de um cliente para cada loja.
    // O inteiro na posição i representa a distância do cliente até a loja de ID i.
    int* storeDistances;
};

#endif

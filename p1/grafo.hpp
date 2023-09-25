#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

typedef std::vector<double> Vertice;

class Grafo {
  public:
    Grafo(const std::string&);
    Grafo() = default;
    std::string CaminoBFS(const int, const int) const;
    std::string CaminoDFS(const int, const int) const;
    void Print() const;
  private:
    int n_{0}, m_{0};
    std::vector<Vertice> distancias_;
    void build_(const std::string&);
    bool dfs_(const int, std::stack<int>&, std::vector<int>&, std::vector<double>&, std::vector<bool>&, int&, int&) const;
    std::string camino_predecesores_(const std::vector<int>&, const int) const;
};
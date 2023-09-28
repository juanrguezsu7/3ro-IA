/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial
 *
 * @author Juan Rodríguez Suárez. alu0101477596@ull.edu.es
 * @date 28. septiembre .2023
 * @brief Práctica 1 de Inteligencia Artificial. Búsquedas en amplitud y profundidad.
 * @file grafo.hpp Contiene la declaración de la clase Grafo.
 */

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

typedef std::vector<double> Vertice;

/**
 * @brief Representa un grafo.
 */
class Grafo {
  public:
    Grafo(const std::string&);
    Grafo() = default;
    //std::string CaminoBFS(const int, const int) const;
    //std::string CaminoDFS(const int, const int) const;
    double GetDistancia(const int, const int) const;
    std::vector<int> GetSucesores(const int) const;
    int GetVertices() const {return n_;}
    int GetArcos() const {return m_;}
    void Print() const;
  private:
    int n_{0}, m_{0};
    std::vector<Vertice> distancias_;
    void build_(const std::string&);
    //bool dfs_(const int, std::stack<int>&, std::vector<int>&, std::vector<double>&, std::vector<bool>&, int&, int&) const;
    //std::string camino_predecesores_(const std::vector<int>&, const int) const;
};
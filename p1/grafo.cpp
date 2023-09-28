/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial
 *
 * @author Juan Rodríguez Suárez. alu0101477596@ull.edu.es
 * @date 28. septiembre .2023
 * @brief Práctica 1 de Inteligencia Artificial. Búsquedas en amplitud y profundidad.
 * @file grafo.cpp Contiene la implementación de la clase Grafo.
 */

#include "grafo.hpp"

/**
 * @brief Constructor de Grafo mediante un fichero de entrada.
 * @param kNombreFicheroEntrada Nombre del fichero de datos de entrada.
 */
Grafo::Grafo(const std::string& kNombreFicheroEntrada) {
  build_(kNombreFicheroEntrada);
}

/**
 * @brief Construye el Grafo a partir del fichero de entrada.
 * @param kNombreFicheroEntrada Nombre del fichero de datos de entrada.
 */
void Grafo::build_(const std::string& kNombreFicheroEntrada) {
  std::ifstream fichero_entrada{kNombreFicheroEntrada};
  std::string distancia;
  fichero_entrada >> n_;
  distancias_.resize(n_);
  for (auto& vertice : distancias_) {
    vertice.resize(n_, 0);
  }
  int vertice_actual{0}, vertice_destino{1};
  while (fichero_entrada >> distancia) {
    if (vertice_destino == n_) {
      ++vertice_actual;
      vertice_destino = vertice_actual + 1;
    }
    distancias_[vertice_actual][vertice_destino] = std::stod(distancia);
    distancias_[vertice_destino][vertice_actual] = std::stod(distancia);
    ++vertice_destino;
    if (std::stod(distancia) > 0) ++m_;
  }
}

/**
 * @brief Devuelve la distancia entre dos vértices directamente conectados.
 * @param kVerticeInicial Vértice inicial.
 * @param kVerticeFinal Vertice final.
 * @return Distancia entre los dos vértices.
 */
double Grafo::GetDistancia(const int kVerticeInicial, const int kVerticeFinal) const {
  return distancias_[kVerticeInicial - 1][kVerticeFinal - 1];
}

/**
 * @brief Devuelve los sucesores de un vértice.
 * @param kVertice Vértice a calcular sus sucesores.
 * @return Los sucesores del vértice elegido.
 */
std::vector<int> Grafo::GetSucesores(const int kVertice) const {
  std::vector<int> sucesores;
  for (int i{0}; i < n_; ++i) {
    if (distancias_[kVertice - 1][i] > 0) sucesores.emplace_back(i + 1);
  }
  return sucesores;
}

/**
 * @brief Imprime por pantalla la matriz de distancias del Grafo.
 */
void Grafo::Print() const {
  for (auto& vertice : distancias_) {
    for (auto& distancia : vertice) {
      std::cout << distancia << ' ';
    }
    std::cout << '\n';
  }
}
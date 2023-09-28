/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial
 *
 * @author Juan Rodríguez Suárez. alu0101477596@ull.edu.es
 * @date 28. septiembre .2023
 * @brief Práctica 1 de Inteligencia Artificial. Búsquedas en amplitud y profundidad.
 * @file arbol.hpp Contiene la declaración de la clase Arbol.
 */

#pragma once

#include "nodo.hpp"
#include "grafo.hpp"

#include <string>
#include <algorithm>
#include <queue>

/**
 * @brief Representa un árbol de búsqueda.
 */
class Arbol {
  public:
    Arbol(const Grafo& kGrafo) : grafo_{kGrafo} {}
    Nodo* GenerarNodo(const int, const double, Nodo* kPadre = nullptr);
    bool BFS(const int, const int);
    bool DFS(const int, const int);
    std::string GetCamino() const;
    double GetDistanciaCamino() const;
    std::string GetGenerados() const;
    std::string GetAnalizados() const;
    ~Arbol();
  private:
    Nodo* head_{nullptr};
    Nodo* nodo_final_{nullptr};
    Grafo grafo_;
    std::vector<Nodo*> nodos_generados_;
    std::vector<Nodo*> nodos_analizados_;
    void destroy_();
};
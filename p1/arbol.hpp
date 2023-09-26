#pragma once

#include "nodo.hpp"
#include "grafo.hpp"

#include <string>
#include <algorithm>
#include <queue>

class Arbol {
  public:
    Arbol(const Grafo& kGrafo) : grafo_{kGrafo} {}
    Nodo* CrearNodo(const int, const double, Nodo* kPadre = nullptr);
    bool BFS(const int, const int);
    bool DFS(const int, const int);
    std::string GetCamino() const;
    double GetDistanciaCamino() const;
    int GetGenerados() const {return nodos_generados_;}
    int GetAnalizados() const {return nodos_analizados_;}
    ~Arbol();
  private:
    Nodo* head_{nullptr};
    Nodo* nodo_final_{nullptr};
    Grafo grafo_;
    int nodos_generados_{1}, nodos_analizados_{0};  
    std::vector<Nodo*> nodos_creados_;
    void destroy_();
};
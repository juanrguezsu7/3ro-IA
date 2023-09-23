#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>

typedef std::vector<double> Vertice;

class Grafo {
  public:
    Grafo(const std::string&);
    Grafo() = default;
    std::string CaminoBFS(const int, const int) const;
    void CaminoDFS(const int, const int) const;
    void Print() const;
  private:
    int n_{0}, m_{0};
    std::vector<Vertice> distancias_;
    void build_(const std::string&);
    std::string camino_predecesores_(const std::vector<int>&, const int) const;
};

Grafo::Grafo(const std::string& kNombreFicheroEntrada) {
  build_(kNombreFicheroEntrada);
}

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

std::string Grafo::camino_predecesores_(const std::vector<int>& kPredecesores, const int kVerticeObjetivo) const {
  std::string camino{};
  int predecesor_actual{kVerticeObjetivo};
  while (predecesor_actual != kPredecesores[predecesor_actual]) {
    camino = std::to_string(predecesor_actual + 1) + "->" + camino;
    predecesor_actual = kPredecesores[predecesor_actual];
  }
  camino = '{' + std::to_string(predecesor_actual + 1) + "->" + camino;
  camino.pop_back();
  camino.pop_back();
  camino += '}';
  return camino;
}

std::string Grafo::CaminoBFS(const int kVerticeInicial, const int kVerticeObjetivo) const {
  std::string resultado;
  resultado += "Vertices: " + std::to_string(n_) + "  Aristas: " + std::to_string(m_) + "  Inicial: " + std::to_string(kVerticeInicial) + "  Final: " + std::to_string(kVerticeObjetivo) + "  ";
  int inicial{kVerticeInicial - 1}, objetivo{kVerticeObjetivo - 1};
  std::vector<bool> visitados_;
  visitados_.resize(n_, false);
  std::queue<int> almacen;
  almacen.emplace(inicial);
  std::vector<int> predecesores;
  predecesores.resize(n_, -1);
  predecesores[inicial] = inicial;
  std::vector<double> distancias_totales;
  distancias_totales.resize(n_, -1);
  distancias_totales[inicial] = 0;
  int vertices_generados{1}, vertices_analizados{0};
  while (!almacen.empty()) {
    int vertice_actual = almacen.front();
    ++vertices_analizados;
    if (vertice_actual == objetivo) {
      resultado += "Camino encontrado: " + camino_predecesores_(predecesores, objetivo) + "  Distancia: " + std::to_string(distancias_totales[vertice_actual]) + "  Generados: " + std::to_string(vertices_generados) + "  Analizados: " + std::to_string(vertices_analizados);
      return resultado;
    }
    almacen.pop();
    visitados_[vertice_actual] = true;
    for (int i{0}; i < n_; ++i) {
      if (!visitados_[i] && distancias_[vertice_actual][i] > 0) {
        distancias_totales[i] = distancias_totales[vertice_actual] + distancias_[vertice_actual][i];
        almacen.emplace(i);
        ++vertices_generados;
        predecesores[i] = vertice_actual;
      }
    }
  }
  resultado += "Camino no encontrado.\tGenerados: " + std::to_string(vertices_generados) + "\tAnalizados: " + std::to_string(vertices_analizados);
  return resultado;
}

void Grafo::CaminoDFS(const int, const int) const {
  
}

void Grafo::Print() const {
  for (auto& vertice : distancias_) {
    for (auto& distancia : vertice) {
      std::cout << distancia << ' ';
    }
    std::cout << '\n';
  }
}
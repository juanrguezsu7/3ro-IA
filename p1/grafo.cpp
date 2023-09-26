#include "grafo.hpp"

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

double Grafo::GetDistancia(const int kVerticeInicial, const int kVerticeFinal) const {
  return distancias_[kVerticeInicial - 1][kVerticeFinal - 1];
}

std::vector<int> Grafo::GetSucesores(const int kVertice) const {
  std::vector<int> sucesores;
  for (int i{0}; i < n_; ++i) {
    if (distancias_[kVertice - 1][i] > 0) sucesores.emplace_back(i + 1);
  }
  return sucesores;
}

void Grafo::Print() const {
  for (auto& vertice : distancias_) {
    for (auto& distancia : vertice) {
      std::cout << distancia << ' ';
    }
    std::cout << '\n';
  }
}

/*std::string Grafo::camino_predecesores_(const std::vector<int>& kPredecesores, const int kVerticeObjetivo) const {
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
  resultado += "(BFS) Vertices: " + std::to_string(n_) + "  Aristas: " + std::to_string(m_) + "  Inicial: " + std::to_string(kVerticeInicial) + "  Final: " + std::to_string(kVerticeObjetivo) + "  ";
  int inicial{kVerticeInicial - 1}, objetivo{kVerticeObjetivo - 1};
  std::vector<bool> visitados;
  visitados.resize(n_, false);
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
    visitados[vertice_actual] = true;
    for (int i{0}; i < n_; ++i) {
      if (!visitados[i] && distancias_[vertice_actual][i] > 0) {
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

bool Grafo::dfs_(const int kVerticeObjetivo, std::stack<int>& almacen, std::vector<int>& predecesores, std::vector<double>& distancias_totales, std::vector<bool>& visitados, int& vertices_generados, int& vertices_analizados) const {
  if (almacen.empty()) return false;
  ++vertices_analizados;
  int vertice_actual{almacen.top()};
  if (vertice_actual == kVerticeObjetivo) return true;
  almacen.pop();
  visitados[vertice_actual] = true;
  for (int i{0}; i < n_; ++i) {
    if (!visitados[i] && distancias_[vertice_actual][i] > 0) {
      distancias_totales[i] = distancias_totales[vertice_actual] + distancias_[vertice_actual][i];
      almacen.push(i);
      ++vertices_generados;
      predecesores[i] = vertice_actual;
    }
  }
  return dfs_(kVerticeObjetivo, almacen, predecesores, distancias_totales, visitados, vertices_generados, vertices_analizados);
}

std::string Grafo::CaminoDFS(const int kVerticeInicial, const int kVerticeObjetivo) const {
  std::string resultado;
  resultado += "(DFS) Vertices: " + std::to_string(n_) + "  Aristas: " + std::to_string(m_) + "  Inicial: " + std::to_string(kVerticeInicial) + "  Final: " + std::to_string(kVerticeObjetivo) + "  ";
  int inicial{kVerticeInicial - 1}, objetivo{kVerticeObjetivo - 1};
  std::vector<bool> visitados;
  visitados.resize(n_, false);
  std::stack<int> almacen;
  almacen.emplace(inicial);
  std::vector<int> predecesores;
  predecesores.resize(n_, -1);
  predecesores[inicial] = inicial;
  std::vector<double> distancias_totales;
  distancias_totales.resize(n_, -1);
  distancias_totales[inicial] = 0;
  int vertices_generados{1}, vertices_analizados{0};
  if (dfs_(objetivo, almacen, predecesores, distancias_totales, visitados, vertices_generados, vertices_analizados)) {
    resultado += "Camino encontrado: " + camino_predecesores_(predecesores, objetivo) + "  Distancia: " + std::to_string(distancias_totales[objetivo]) + "  Generados: " + std::to_string(vertices_generados) + "  Analizados: " + std::to_string(vertices_analizados);

  } else {
    resultado += "***Camino no encontrado***  Generados: " + std::to_string(vertices_generados) + "  Analizados: " + std::to_string(vertices_analizados);
  }
  return resultado;
}*/
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial
 *
 * @author Juan Rodríguez Suárez. alu0101477596@ull.edu.es
 * @date 28. septiembre .2023
 * @brief Práctica 1 de Inteligencia Artificial. Búsquedas en amplitud y profundidad.
 * @file arbol.cpp Contiene la implementación de la clase Arbol.
 */

#include "arbol.hpp"

/**
 * @brief Genera un nodo dinámicamente con un valor, una distancia para llegar a él y un nodo padre.
 * @param kKey Valor asociado al nodo (representativo).
 * @param kDistancia Distancia para llegar al nodo.
 * @param kPadre Puntero al nodo padre.
 * @return Puntero al nodo generado.
 */
Nodo* Arbol::GenerarNodo(const int kNumeroNodo, const double kDistancia, Nodo* kPadre) {
  Nodo* nodo{new Nodo{kNumeroNodo, kDistancia, kPadre}};
  nodos_generados_.emplace_back(nodo);
  return nodo;
}

/**
 * @brief Realiza un recorrido en amplitud hasta encontrar el valor objetivo.
 * @param kNodoInicial Valor del nodo inicial.
 * @param kNodoFinal Valor del nodo final.
 * @return true sí encontró un camino, false si no.
 */
bool Arbol::BFS(const int kNodoInicial, const int kNodoFinal) {
  // Limpiar el árbol anterior.
  destroy_();
  // Inicializar variables.
  head_ = GenerarNodo(kNodoInicial, 0);
  std::vector<int> sucesores;
  std::queue<Nodo*> almacen;
  Nodo* nodo_actual;
  int numero_nodo_actual;
  double distancia_nodo_actual;
  // Colocamos el nodo inicial en la cola.
  almacen.emplace(head_);
  // Mientras haya nodos en la cola y no se haya alcanzado el nodo final que se ejecute el algoritmo de búsqueda en amplitud.
  while (!almacen.empty()) {
    // Sacamos un nodo de la cola para analizarlo.
    nodo_actual = almacen.front();
    almacen.pop();
    numero_nodo_actual = nodo_actual->GetNumero();
    distancia_nodo_actual = nodo_actual->GetDistancia();
    // Analizando el nodo actual.
    nodos_analizados_.emplace_back(nodo_actual);
    if (numero_nodo_actual == kNodoFinal) {
      nodo_final_ = nodo_actual;
      return true;
    }
    // Observamos los sucesores del nodo actual.
    sucesores = grafo_.GetSucesores(numero_nodo_actual);
    for (auto sucesor : sucesores) {
      // Si un sucesor no está en la rama lo añadimos al árbol.
      if (!nodo_actual->NodoEnRama(sucesor)) {
        almacen.emplace(GenerarNodo(sucesor, distancia_nodo_actual + grafo_.GetDistancia(numero_nodo_actual, sucesor), nodo_actual));
      }
    }
  }
  return false;
}

/**
 * @brief Realiza un recorrido en profundidad hasta encontrar el valor objetivo.
 * @param kNodoInicial Valor del nodo inicial.
 * @param kNodoFinal Valor del nodo final.
 * @return true sí encontró un camino, false si no.
 */
bool Arbol::DFS(const int kNodoInicial, const int kNodoFinal) {
  // Limpiar el árbol anterior.
  destroy_();
  // Inicializar variables.
  head_ = GenerarNodo(kNodoInicial, 0);
  std::vector<int> sucesores;
  std::stack<Nodo*> almacen;
  Nodo* nodo_actual;
  int numero_nodo_actual;
  double distancia_nodo_actual;
  // Colocamos el nodo inicial en la pila.
  almacen.emplace(head_);
  // Mientras haya nodos en la pila y no se haya alcanzado el nodo final que se ejecute el algoritmo de búsqueda en profundidad.
  while (!almacen.empty()) {
    // Sacamos un nodo de la pila para analizarlo.
    nodo_actual = almacen.top();
    almacen.pop();
    numero_nodo_actual = nodo_actual->GetNumero();
    distancia_nodo_actual = nodo_actual->GetDistancia();
    // Analizando el nodo actual.
    nodos_analizados_.emplace_back(nodo_actual);
    if (numero_nodo_actual == kNodoFinal) {
      nodo_final_ = nodo_actual;
      return true;
    }
    // Observamos los sucesores del nodo actual.
    sucesores = grafo_.GetSucesores(numero_nodo_actual);
    for (auto sucesor : sucesores) {
      // Si un sucesor no está en la rama lo añadimos al árbol.
      if (!nodo_actual->NodoEnRama(sucesor)) {
        almacen.emplace(GenerarNodo(sucesor, distancia_nodo_actual + grafo_.GetDistancia(numero_nodo_actual, sucesor), nodo_actual));
      }
    }
  }
  return false;
}

/**
 * @brief Calcula el camino desde el nodo final hasta el inicial y lo devuelve en un formato imprimible.
 * @return Cadena con el camino.
 */
std::string Arbol::GetCamino() const {
  std::string camino;
  Nodo* nodo_actual{nodo_final_};
  while (nodo_actual != nullptr) {
    camino += std::to_string(nodo_actual->GetNumero());
    camino += ">";
    nodo_actual = nodo_actual->GetPadre();
  }
  if (camino.length() > 0) {
    camino.pop_back();
  }
  std::reverse(camino.begin(), camino.end());
  camino += "}";
  camino.insert(camino.begin(), 1, '{');
  return camino;
}

/**
 * @brief Calcula el coste del camino obtenido.
 * @return Coste del camino.
 */
double Arbol::GetDistanciaCamino() const {
  if (nodo_final_ == nullptr) return -1;
  return nodo_final_->GetDistancia();
}

/**
 * @brief Devuelve el conjunto de los nodos generados en un formato imprimible.
 * @return Cadena con los nodos generados.
 */
std::string Arbol::GetGenerados() const {
  std::string generados{'{'};
  for (auto nodo : nodos_generados_) {
    generados += std::to_string(nodo->GetNumero()) + ", ";
  }
  if (generados.length() > 1) {
    for (int i{0}; i < 2; ++i) generados.pop_back();
  }
  generados += "}";
  return generados;
}

/**
 * @brief Devuelve el conjunto de los nodos analizados en un formato imprimible.
 * @return Cadena con los nodos analizados.
 */
std::string Arbol::GetAnalizados() const {
  std::string analizados{'{'};
  for (auto nodo : nodos_analizados_) {
    analizados += std::to_string(nodo->GetNumero()) + ", ";
  }
  if (analizados.length() > 1) {
    for (int i{0}; i < 2; ++i) analizados.pop_back();
  }
  analizados += "}";
  return analizados;
}

/**
 * @brief Limpia toda la memoria empleada en la creación de los nodos y reasigna las variables del Arbol a su valor inicial.
 */
void Arbol::destroy_() {
  head_ = nullptr;
  nodo_final_ = nullptr;
  nodos_analizados_.clear();
  for (auto nodo : nodos_generados_) delete nodo;
  nodos_generados_.clear();
}

/**
 * @brief Destructor de Arbol.
 */
Arbol::~Arbol() {
  destroy_();
}
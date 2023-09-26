#include "arbol.hpp"

Nodo* Arbol::CrearNodo(const int kNumeroNodo, const double kDistancia, Nodo* kPadre) {
  Nodo* nodo{new Nodo{kNumeroNodo, kDistancia, kPadre}};
  nodos_creados_.emplace_back(nodo);
  return nodo;
}

bool Arbol::BFS(const int kNodoIncial, const int kNodoFinal) {
  // Limpiar el árbol anterior.
  destroy_();
  // Inicializar variables.
  head_ = CrearNodo(kNodoIncial, 0);
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
    ++nodos_analizados_;
    if (numero_nodo_actual == kNodoFinal) {
      nodo_final_ = nodo_actual;
      return true;
    }
    // Observamos los sucesores del nodo actual.
    sucesores = grafo_.GetSucesores(numero_nodo_actual);
    for (auto sucesor : sucesores) {
      // Si un sucesor no está en la rama lo añadimos al árbol.
      if (!nodo_actual->NodoEnRama(sucesor)) {
        almacen.emplace(CrearNodo(sucesor, distancia_nodo_actual + grafo_.GetDistancia(numero_nodo_actual, sucesor), nodo_actual));
        ++nodos_generados_;
      }
    }
  }
  return false;
}

bool Arbol::DFS(const int kNodoIncial, const int kNodoFinal) {
  destroy_();
  head_->GetNumero() = kNodoIncial;
  return false;
}

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

double Arbol::GetDistanciaCamino() const {
  if (nodo_final_ == nullptr) return -1;
  return nodo_final_->GetDistancia();
}

void Arbol::destroy_() {
  for (auto nodo : nodos_creados_) delete nodo;
}

Arbol::~Arbol() {
  destroy_();
}
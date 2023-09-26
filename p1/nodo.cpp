#include "nodo.hpp"

bool Nodo::NodoEnRama(const int kNodoABuscar) const {
  if (numero_nodo_ == kNodoABuscar) return true;
  if (GetPadre() == nullptr) return false;
  return GetPadre()->NodoEnRama(kNodoABuscar);
}
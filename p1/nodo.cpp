/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial
 *
 * @author Juan Rodríguez Suárez. alu0101477596@ull.edu.es
 * @date 28. septiembre .2023
 * @brief Práctica 1 de Inteligencia Artificial. Búsquedas en amplitud y profundidad.
 * @file nodo.cpp Contiene la implementación de la clase Nodo.
 */

#include "nodo.hpp"

/**
 * @brief Calcula si un Nodo dado está en la rama del Nodo actual.
 * @param kNodoABuscar Nodo a buscar en la rama.
 * @return true si el nodo está en la rama, false si no.
 */
bool Nodo::NodoEnRama(const int kNodoABuscar) const {
  if (numero_nodo_ == kNodoABuscar) return true;
  if (GetPadre() == nullptr) return false;
  return GetPadre()->NodoEnRama(kNodoABuscar);
}
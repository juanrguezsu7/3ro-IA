/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial
 *
 * @author Juan Rodríguez Suárez. alu0101477596@ull.edu.es
 * @date 28. septiembre .2023
 * @brief Práctica 1 de Inteligencia Artificial. Búsquedas en amplitud y profundidad.
 * @file nodo.hpp Contiene la declaración de la clase Nodo.
 */

#pragma once

/**
 * @brief Representa un nodo de un árbol de búsqueda.
 */
class Nodo {
  public:
    Nodo(const int kNumeroNodo, const double kDistancia, const int kProfundidad, Nodo* kPadre) : numero_nodo_{kNumeroNodo}, distancia_{kDistancia}, profundidad_{kProfundidad}, padre_{kPadre} {};
    Nodo* GetPadre() const {return padre_;}
    Nodo*& GetPadre() {return padre_;}
    int GetNumero() const {return numero_nodo_;};
    int& GetNumero() {return numero_nodo_;}
    int GetProfundidad() const {return profundidad_;}
    int& GetProfundidad() {return profundidad_;}
    double GetDistancia() const {return distancia_;}
    double& GetDistancia() {return distancia_;}
    bool NodoEnRama(const int) const;
    ~Nodo() {}
  private:
    int numero_nodo_, profundidad_;
    double distancia_;
    Nodo* padre_{nullptr};
    
};
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial
 *
 * @author Juan Rodríguez Suárez. alu0101477596@ull.edu.es
 * @date 28. septiembre .2023
 * @brief Práctica 1 de Inteligencia Artificial. Búsquedas en amplitud y profundidad.
 * @file menu.hpp Contiene la declaración de la clase Menu.
 */

#pragma once

#include "arbol.hpp"

#include <string>
#include <fstream>
#include <iostream>

/**
 * @brief Representa un menú interactivo.
 */
class Menu {
  public:
    Menu();
    void CargarGrafo();
    void MostrarBFS();
    void MostrarDFS();
    void MostrarOpciones();
  private:
    Grafo grafo_;
    std::ofstream output_file_;
    int id_camino_{1};
};
#pragma once

#include "grafo.hpp"

#include <string>
#include <fstream>
#include <iostream>

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
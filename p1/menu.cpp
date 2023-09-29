/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Inteligencia Artificial
 *
 * @author Juan Rodríguez Suárez. alu0101477596@ull.edu.es
 * @date 28. septiembre .2023
 * @brief Práctica 1 de Inteligencia Artificial. Búsquedas en amplitud y profundidad.
 * @file menu.cpp Contiene la implementación de la clase Menu.
 */

#include "menu.hpp"

/**
 * @brief Constructor de Menu.
 */
Menu::Menu() {
  CargarGrafo();
}

/**
 * @brief Carga un Grafo desde un fichero de datos de entrada.
 */
void Menu::CargarGrafo() {
  std::string nombre;
  while (true) { 
    try {
      std::cout << "Introduzca nombre de archivo de grafo: ";
      std::cin >> nombre;
      grafo_ = Grafo{nombre};
    } catch (const std::length_error& exc) {
      std::cout << "ERROR: Introduzca un nombre de archivo valido.\n";
      continue;
    }
    break;
  }
}

/**
 * @brief Imprime al fichero de salida de datos el camino en amplitud.
 */
void Menu::MostrarBFS() {
  Arbol arbol_busqueda{grafo_};
  int vertice_inicial, vertice_final;
  std::cout << "\tVertice inicial: ";
  std::cin >> vertice_inicial;
  std::cout << "\tVertice final: ";
  std::cin >> vertice_final;
  arbol_busqueda.BFS(vertice_inicial, vertice_final);
  output_file_ << "ID-" << id_camino_ << "\t(BFS) Vertices: " << grafo_.GetVertices() << "  Aristas: " << grafo_.GetArcos() << "  Inicial: " << vertice_inicial << "  Final: " << vertice_final << "  Camino: " << arbol_busqueda.GetCamino() << "  Distancia: " << arbol_busqueda.GetDistanciaCamino() << "  Profundidad: " << arbol_busqueda.GetProfundidad() << "  Generados: " << arbol_busqueda.GetGenerados() << "  Analizados: " << arbol_busqueda.GetAnalizados() << '\n';
  ++id_camino_;
  output_file_.flush();
}

/**
 * @brief Imprime al fichero de salida de datos el camino en profundidad.
 */
void Menu::MostrarDFS() {
  Arbol arbol_busqueda{grafo_};
  int vertice_inicial, vertice_final;
  std::cout << "\tVertice inicial: ";
  std::cin >> vertice_inicial;
  std::cout << "\tVertice final: ";
  std::cin >> vertice_final;
  arbol_busqueda.DFS(vertice_inicial, vertice_final);
  output_file_ << "ID-" << id_camino_ << "\t(DFS) Vertices: " << grafo_.GetVertices() << "  Aristas: " << grafo_.GetArcos() << "  Inicial: " << vertice_inicial << "  Final: " << vertice_final << "  Camino: " << arbol_busqueda.GetCamino() << "  Distancia: " << arbol_busqueda.GetDistanciaCamino() << "  Profundidad: " << arbol_busqueda.GetProfundidad() << "  Generados: " << arbol_busqueda.GetGenerados() << "  Analizados: " << arbol_busqueda.GetAnalizados() << '\n';
  ++id_camino_;
  output_file_.flush();
}

/**
 * @brief Imprime por pantalla las diferentes opciones del Menu.
 */
void Menu::MostrarOpciones() {
  std::string nombre;
  std::cout << "Introduzca nombre de archivo de salida de datos: ";
  std::cin >> nombre;
  output_file_.open(nombre, std::ios_base::out | std::ios_base::trunc);
  char input;
  while (true) {
    std::cout << "1) Cargar grafo desde fichero.\n";
    std::cout << "2) Camino con recorrido en amplitud.\n";
    std::cout << "3) Camino con recorrido en profundidad.\n";
    std::cout << "0) Salir.\n\n";
    std::cout << "Introduzca una opción: ";
    std::cin >> input;
    switch (input) {
      case '0':
        return;
      case '1':
        CargarGrafo();
        break;
      case '2':
        MostrarBFS();
        break;
      case '3':
        MostrarDFS();
        break;
      default:
        break;
    }
  }
}
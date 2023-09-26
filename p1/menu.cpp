#include "menu.hpp"

Menu::Menu() {
  CargarGrafo();
}

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

void Menu::MostrarBFS() {
  Arbol arbol_busqueda{grafo_};
  int vertice_inicial, vertice_final;
  std::cout << "\tVertice inicial: ";
  std::cin >> vertice_inicial;
  std::cout << "\tVertice final: ";
  std::cin >> vertice_final;
  arbol_busqueda.BFS(vertice_inicial, vertice_final);
  output_file_ << "ID-" << id_camino_ << "\t(BFS) Vertices: " << grafo_.GetVertices() << "  Aristas: " << grafo_.GetArcos() << "  Inicial: " << vertice_inicial << "  Final: " << vertice_final << "  Camino: " << arbol_busqueda.GetCamino() << "  Distancia: " << arbol_busqueda.GetDistanciaCamino() << "  Generados: " << arbol_busqueda.GetGenerados() << "  Analizados: " << arbol_busqueda.GetAnalizados() << '\n';
  ++id_camino_;
  output_file_.flush();
}

void Menu::MostrarDFS() {
  Arbol arbol_busqueda{grafo_};
  int vertice_inicial, vertice_final;
  std::cout << "\tVertice inicial: ";
  std::cin >> vertice_inicial;
  std::cout << "\tVertice final: ";
  std::cin >> vertice_final;
  arbol_busqueda.DFS(vertice_inicial, vertice_final);
  output_file_ << "ID-" << id_camino_ << "\t(DFS) Vertices: " << grafo_.GetVertices() << "  Aristas: " << grafo_.GetArcos() << "  Inicial: " << vertice_inicial << "  Final: " << vertice_final << "  Camino: " << arbol_busqueda.GetCamino() << "  Distancia: " << arbol_busqueda.GetDistanciaCamino() << "  Generados: " << arbol_busqueda.GetGenerados() << "  Analizados: " << arbol_busqueda.GetAnalizados() << '\n';
  ++id_camino_;
  output_file_.flush();
}

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
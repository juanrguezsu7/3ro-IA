"""
Módulo que contiene la clase Arbol y Nodo.

:file: arbol.py
:author: Juan Rodríguez Suárez
:date: 14/10/2023
"""

class Nodo:
  """
  Clase que representa un nodo del arbol de búsqueda.
  """

  def __init__(self, coordenadas, coste_acumulado, coste_heuristico, padre) -> None:
    """
    Inicializa un nodo del arbol de búsqueda.
    
    :param coordenadas: Coordenadas del nodo.
    :param coste_acumulado: Coste acumulado del nodo.
    :param coste_heuristico: Coste heurístico del nodo.
    :param padre: Nodo padre del nodo.
    :return:
    """

    self.coordenadas = coordenadas
    self.coste_acumulado = coste_acumulado
    self.coste_heuristico = coste_heuristico
    self.padre = padre

  def __str__(self) -> str:
    """
    Representación en cadena del nodo.

    :return: Representación en cadena del nodo.
    """

    return self.coordenadas

  def CosteTotal(self) -> int:
    """
    Coste total del nodo, es decir, la suma del coste acumulado hasta ahora y el coste heurístico.

    :return: Coste total del nodo.
    """

    return self.coste_acumulado + self.coste_heuristico

class Arbol:
  """
  Clase que representa el arbol de búsqueda.
  """

  def __init__(self, coordenadas_head, coste_heuristico_head) -> None:
    """
    Inicializa el arbol de búsqueda.

    :param coordenadas_head: Coordenadas del nodo inicial.
    :param coste_heuristico_head: Coste heurístico del nodo inicial.
    :return:
    """

    self.generados = []
    self.analizados = []
    self.final = None
    self.head = self.CrearNodo(coordenadas_head, 0, coste_heuristico_head, None)
  
  def CrearNodo(self, coordenadas, coste_acumulado, coste_heuristico, padre) -> Nodo:
    """
    Crea un nuevo nodo.

    :param coordenadas: Coordenadas del nodo.
    :param coste_acumulado: Coste acumulado del nodo.
    :param coste_heuristico: Coste heurístico del nodo.
    :param padre: Nodo padre del nodo.
    :return: Nuevo nodo.
    """

    nuevo_nodo = Nodo(coordenadas, coste_acumulado, coste_heuristico, padre)
    self.generados.append(nuevo_nodo.coordenadas)
    return nuevo_nodo
  
  def GetCamino(self) -> list:
    """
    Devuelve el camino desde el nodo inicial hasta el nodo final.

    :return: Camino desde el nodo inicial hasta el nodo final.
    """

    camino = []
    nodo_actual = self.final
    while nodo_actual != None:
      camino.append(nodo_actual.coordenadas)
      nodo_actual = nodo_actual.padre
    camino.reverse()
    return camino
    
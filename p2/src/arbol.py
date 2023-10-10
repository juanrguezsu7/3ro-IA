class Nodo:
  def __init__(self, coordenadas, coste_acumulado, coste_heuristico, padre) -> None:
    self.coordenadas = coordenadas
    self.coste_acumulado = coste_acumulado
    self.coste_heuristico = coste_heuristico
    self.padre = padre

  def __str__(self) -> str:
    return self.coordenadas

  def CosteTotal(self) -> int:
    return self.coste_acumulado + self.coste_heuristico

class Arbol:
  def __init__(self, coordenadas_head, coste_heuristico_head) -> None:
    self.generados = []
    self.analizados = []
    self.final = None
    self.head = self.CrearNodo(coordenadas_head, 0, coste_heuristico_head, None)
  
  def CrearNodo(self, coordenadas, coste_acumulado, coste_heuristico, padre) -> Nodo:
    nuevo_nodo = Nodo(coordenadas, coste_acumulado, coste_heuristico, padre)
    self.generados.append(nuevo_nodo.coordenadas)
    return nuevo_nodo
  
  def GetCamino(self) -> list:
    camino = []
    nodo_actual = self.final
    while nodo_actual != None:
      camino.append(nodo_actual.coordenadas)
      nodo_actual = nodo_actual.padre
    camino.reverse()
    return camino
    
"""
Módulo que representa un laberinto.

:file: laberinto.py
:author: Juan Rodríguez Suárez
:date: 14/10/2023
"""

from arbol import Arbol

COSTE_HORIZONTAL_VERTICAL = 3 # Coste de moverse en horizontal o vertical.
COSTE_DIAGONAL = 7 # Coste de moverse en diagonal.

class Laberinto:
  """
  Clase que representa un laberinto.
  """

  def __init__(self) -> None:
    """
    Inicializa un laberinto.
    """

    self.CargarLaberinto()
    self.id_camino = 0
    self.arbol = None
    self.solucionado = False
    self.funcion_heuristica = self.DistanciaManhattan
  
  def __str__(self) -> str:
    """
    Representación en cadena del laberinto.

    :return: Representación en cadena del laberinto.
    """

    resultado = ""
    for fila in self.laberinto: resultado += fila.replace('0', '⬜').replace('1', '⬛').replace('3', "E ").replace('4', "S ") + '\n'
    else: return resultado[:-1]
  
  def GetEntrada(self) -> tuple:
    """
    Devuelve las coordenadas de la entrada del laberinto.

    :return: Coordenadas de la entrada del laberinto.
    """

    for i in range(self.filas):
      for j in range(self.columnas):
        if self.laberinto[i][j] == '3': return (i + 1, j + 1)
    return (0, 0)
  
  def GetSalida(self) -> tuple:
    """
    Devuelve las coordenadas de la salida del laberinto.

    :return: Coordenadas de la salida del laberinto.
    """

    for i in range(self.filas):
      for j in range(self.columnas):
        if self.laberinto[i][j] == '4': return (i + 1, j + 1)
    return (0, 0)

  def AEstrella(self) -> bool:
    """
    Algoritmo de búsqueda A* sobre el laberinto para encontrar el camino óptimo.

    :return: True si se ha encontrado el camino, False en caso contrario.
    """
    
    self.solucionado = False # Reseteamos el estado del laberinto
    self.id_camino += 1 # Aumentar ID del camino.
    self.arbol = Arbol(self.GetEntrada(), self.funcion_heuristica(self.GetEntrada())) # Creando el Arbol con el nodo inicial que se corresponde a la casilla de salida.
    nodos_abiertos = {self.GetEntrada(): self.arbol.head} # Lo añadimos a la lista de nodos abiertos.
    nodos_cerrados = {} # Inicializamos la lista de nodos cerrados.
    while len(nodos_abiertos) > 0: # Mientras haya nodos en la lista de nodos abiertos.
      nodo_actual = min(nodos_abiertos.values(), key = lambda nodo: nodo.CosteTotal()) # Encontramos el nodo con menor coste de la lista.
      nodos_abiertos.pop(nodo_actual.coordenadas) # Lo sacamos de la lista de nodos abiertos.
      nodos_cerrados.update({nodo_actual.coordenadas: nodo_actual}) # Lo añadimos a la lista de nodos cerrados.
      self.arbol.analizados.append(nodo_actual.coordenadas) # Analizamos y si las coordenadas del nodo coinciden con la salida, hemos encontrado el camino.
      if nodo_actual.coordenadas == self.GetSalida():
        self.arbol.final = nodo_actual 
        self.solucionado = True 
        return True 
      for casilla_adyacente in self.CasillasAdyacentes(nodo_actual.coordenadas): # Recorremos los vecinos de la casilla actual.
        coste_movimiento = COSTE_HORIZONTAL_VERTICAL # Calculamos el coste del movimiento según sea recto o diagonal.
        if abs(casilla_adyacente[0] - nodo_actual.coordenadas[0]) == 1 and abs(casilla_adyacente[1] - nodo_actual.coordenadas[1]) == 1: coste_movimiento = COSTE_DIAGONAL
        if any(coordenadas == casilla_adyacente for coordenadas in nodos_abiertos.keys()): # Si las coordenadas de la casilla vecina actual coinciden con algún nodo de nodos abiertos comprobar si hay que actualizarlo.
          nuevo_coste = nodo_actual.coste_acumulado + coste_movimiento # Calculamos el nuevo coste que tendría el nodo desde el nodo actual.
          if nuevo_coste < nodos_abiertos[casilla_adyacente].coste_acumulado: # Si el nuevo coste es menor que el coste actual, actualizar su coste acumulado y su padre.
            nodos_abiertos[casilla_adyacente].coste_acumulado = nuevo_coste
            nodos_abiertos[casilla_adyacente].padre = nodo_actual
        elif any(coordenadas == casilla_adyacente for coordenadas in nodos_cerrados.keys()): # Comprobar que las coordenadas de la casilla vecina actual no están en la lista de nodos cerrados.
          pass
        else: # Si no está en ninguna de las listas, generar un nuevo nodo.
          nodos_abiertos.update({casilla_adyacente: self.arbol.CrearNodo(casilla_adyacente, nodo_actual.coste_acumulado + coste_movimiento, self.funcion_heuristica(casilla_adyacente), nodo_actual)})
    return False

  def EscribirInstancia(self, fichero_salida) -> None:
    """
    Escribe en el fichero de salida la instancia del camino hacia la salida.

    :param fichero_salida: Fichero de salida.
    :return:
    """

    if self.solucionado:
      fichero_salida.write(f"ID {self.id_camino}    Filas: {self.filas}  Columnas: {self.columnas}  Entrada: {self.GetEntrada()}  Salida: {self.GetSalida()}  Camino: {self.arbol.GetCamino()}  Coste: {self.arbol.final.coste_acumulado}  Generados: {self.arbol.generados}  Analizados: {self.arbol.analizados}\n")
    else:
      fichero_salida.write(f"ID {self.id_camino}    Filas: {self.filas}  Columnas: {self.columnas}  Entrada: {self.GetEntrada()}  Salida: {self.GetSalida()}  Camino no encontrado  Generados: {self.arbol.generados}  Analizados: {self.arbol.analizados}\n")
    fichero_salida.write(self.GetLaberintoSolucion())
    fichero_salida.flush()

  def CargarLaberinto(self) -> None:
    """
    Carga el laberinto desde un fichero de datos.

    :return:
    """

    fichero_entrada = input("Introduca un fichero de datos del laberinto: ")
    while True:
      try:
        fichero_datos = open(fichero_entrada)
        break
      except OSError:
        fichero_entrada = input("Introduca un fichero de datos válido: ")
    self.filas = int(fichero_datos.readline())
    self.columnas = int(fichero_datos.readline())
    self.laberinto = fichero_datos.read().replace(' ', '').split('\n')
    fichero_datos.close()
  
  def CambiarEntradaSalida(self) -> None:
    """
    Cambia la entrada y la salida del laberinto.

    :return:
    """

    nueva_fila = int(input("Introduzca la nueva fila de la entrada: "))
    nueva_columna = int(input("Introduzca la nueva columna de la entrada: "))
    self.SetCelda(self.GetEntrada(), '1')
    self.SetCelda((nueva_fila, nueva_columna), '3')
    nueva_fila = int(input("Introduzca la nueva fila de la salida: "))
    nueva_columna = int(input("Introduzca la nueva columna de la salida: "))
    self.SetCelda(self.GetSalida(), '1')
    self.SetCelda((nueva_fila, nueva_columna), '4')
  
  def SetCelda(self, coordenadas, valor) -> None:
    """
    Cambia el valor de una celda del laberinto.

    :param coordenadas: Coordenadas de la celda.
    :param valor: Nuevo valor de la celda.
    :return:
    """

    fila = self.laberinto[coordenadas[0] - 1]
    self.laberinto[coordenadas[0] - 1] = fila[:coordenadas[1] - 1] + valor + fila[coordenadas[1]:]
  
  def GetCelda(self, coordenadas) -> str:
    """
    Devuelve el valor de una celda del laberinto.

    :param coordenadas: Coordenadas de la celda.
    :return: Valor de la celda.
    """

    return self.laberinto[coordenadas[0] - 1][coordenadas[1] - 1]
  
  def CambiarFuncionHeuristica(self) -> None:
    """
    Cambia la función heurística del algoritmo de búsqueda.

    :return:
    """

    print("1) Distancia Manhattan\n2) Distancia Euclideana\n")
    opcion = input("Elegir opción: ")
    if opcion == '1':
      self.funcion_heuristica = self.DistanciaManhattan
    elif opcion == '2':
      self.funcion_heuristica = self.DistanciaEuclideana
   
  def GetFuncionHeuristica(self) -> str:
    """
    Devuelve la función heurística del algoritmo de búsqueda.

    :return: Función heurística del algoritmo de búsqueda.
    """

    if self.funcion_heuristica == self.DistanciaManhattan:
      return "Distancia Manhattan"
    elif self.funcion_heuristica == self.DistanciaEuclideana:
      return "Distancia Euclideana"
  
  def DistanciaManhattan(self, coordenadas_inicial) -> int:
    """
    Calcula la distancia Manhattan entre dos puntos.

    :param coordenadas_inicial: Coordenadas del punto inicial.
    :return: Distancia Manhattan entre los dos puntos.
    """

    coordenadas_salida = self.GetSalida()
    return (abs(coordenadas_inicial[0] - coordenadas_salida[0]) + abs(coordenadas_inicial[1] - coordenadas_salida[1])) * COSTE_HORIZONTAL_VERTICAL
  
  def DistanciaEuclideana(self, coordenadas_inicial) -> float:
    """
    Calcula la distancia Euclideana entre dos puntos.

    :param coordenadas_inicial: Coordenadas del punto inicial.
    :return: Distancia Euclideana entre los dos puntos.
    """

    coordenadas_salida = self.GetSalida()
    return ((coordenadas_inicial[0] - coordenadas_salida[0]) ** 2 + (coordenadas_inicial[1] - coordenadas_salida[1]) ** 2) ** 0.5 * COSTE_HORIZONTAL_VERTICAL

  def CasillasAdyacentes(self, coordenadas) -> list:
    """
    Devuelve las casillas adyacentes a una casilla.

    :param coordenadas: Coordenadas de la casilla.
    :return: Casillas adyacentes a la casilla.
    """

    casillas_adyacentes = []
    fila = coordenadas[0]
    columna = coordenadas[1]
    movimientos = (-1, 0, 1)
    for desplazamiento_fila in movimientos:
      if fila + desplazamiento_fila < 1 or fila + desplazamiento_fila > self.filas: continue
      for desplazamiento_columna in movimientos:
        if desplazamiento_fila == 0 and desplazamiento_columna == 0: continue
        if columna + desplazamiento_columna < 1 or columna + desplazamiento_columna > self.columnas: continue
        candidato = (fila + desplazamiento_fila, columna + desplazamiento_columna)
        if self.GetCelda(candidato) != '1': casillas_adyacentes.append(candidato)
    return casillas_adyacentes
  
  def GetLaberintoSolucion(self) -> str:
    """
    Devuelve el laberinto con el camino hacia la salida.

    :return: Laberinto con el camino hacia la salida en forma 'bonita'.
    """

    resultado_lista = self.laberinto.copy()
    resultado = ""
    if self.arbol != None and self.solucionado:
      for celda_solucion in self.arbol.GetCamino():
        cadena_lista = list(resultado_lista[celda_solucion[0] - 1])
        cadena_lista[celda_solucion[1] - 1] = "◽"
        resultado_lista[celda_solucion[0] - 1] = ''.join(cadena_lista) 
      for fila in resultado_lista: resultado += fila + '\n'
      else: return resultado.replace('0', "⬜ ").replace('1', "⬛ ").replace('◽', "◽ ") + '\n'
    else: return '\n'
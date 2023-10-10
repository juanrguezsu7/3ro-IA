from arbol import Arbol

COSTE_HORIZONTAL_VERTICAL = 5
COSTE_DIAGONAL = 10

class Laberinto:
  def __init__(self) -> None:
    self.CargarLaberinto()
    self.id_camino = 0
    self.arbol = None
    self.solucionado = False
  
  def __str__(self) -> str:
    resultado = ""
    for fila in self.laberinto: resultado += fila.replace('0', '⬜').replace('1', '⬛').replace('3', "E ").replace('4', "S ") + '\n'
    else: return resultado[:-1]
  
  def GetEntrada(self) -> tuple:
    for i in range(self.filas):
      for j in range(self.columnas):
        if self.laberinto[i][j] == '3': return (i + 1, j + 1)
    return (0, 0)
  
  def GetSalida(self) -> tuple:
    for i in range(self.filas):
      for j in range(self.columnas):
        if self.laberinto[i][j] == '4': return (i + 1, j + 1)
    return (0, 0)

  def AEstrella(self) -> bool:
    # Reseteamos el estado del laberinto
    self.solucionado = False
    # Aumentar ID del camino.
    self.id_camino += 1
    # Creando el Arbol con el nodo inicial que se corresponde a la casilla de salida.
    self.arbol = Arbol(self.GetEntrada(), self.DistanciaManhattan(self.GetEntrada()))
    # Lo añadimos a la lista de nodos abiertos.
    nodos_abiertos = {self.GetEntrada(): self.arbol.head}
    nodos_cerrados = {}
    # Mientras haya nodos en la lista de nodos abiertos.
    while len(nodos_abiertos) > 0:
      # Encontramos el nodo con menor coste de la lista.
      nodo_actual = min(nodos_abiertos.values(), key = lambda nodo: nodo.CosteTotal())
      # Lo sacamos de la lista de nodos abiertos.
      nodos_abiertos.pop(nodo_actual.coordenadas)
      # Lo añadimos a la lista de nodos cerrados.
      nodos_cerrados.update({nodo_actual.coordenadas: nodo_actual})
      # Analizamos y si las coordenadas del nodo coinciden con la salida, hemos encontrado el camino.
      self.arbol.analizados.append(nodo_actual.coordenadas)
      if nodo_actual.coordenadas == self.GetSalida():
        self.arbol.final = nodo_actual
        self.solucionado = True
        return True
      # Recorremos los vecinos de la casilla actual.
      for casilla_adyacente in self.CasillasAdyacentes(nodo_actual.coordenadas):
        # Calculamos el coste del movimiento según sea recto o diagonal.
        coste_movimiento = COSTE_HORIZONTAL_VERTICAL
        if abs(casilla_adyacente[0] - nodo_actual.coordenadas[0]) == 1 and abs(casilla_adyacente[1] - nodo_actual.coordenadas[1]) == 1: coste_movimiento = COSTE_DIAGONAL
        # Si las coordenadas de la casilla vecina actual coinciden con algún nodo de nodos abiertos comprobar si hay que actualizarlo.
        if any(coordenadas == casilla_adyacente for coordenadas in nodos_abiertos.keys()):
          # Calculamos el nuevo coste que tendría el nodo desde el nodo actual.
          nuevo_coste = nodo_actual.coste_acumulado + coste_movimiento
          # Si el nuevo coste es menor que el coste actual, actualizar su coste acumulado y su padre.
          if nuevo_coste < nodos_abiertos[casilla_adyacente].coste_acumulado:
            nodos_abiertos[casilla_adyacente].coste_acumulado = nuevo_coste
            nodos_abiertos[casilla_adyacente].padre = nodo_actual
        # Comprobar que las coordenadas de la casilla vecina actual no están en la lista de nodos cerrados.
        elif any(coordenadas == casilla_adyacente for coordenadas in nodos_cerrados.keys()):
          pass
        # Si no está en ninguna de las listas, generar un nuevo nodo.
        else:
          nodos_abiertos.update({casilla_adyacente: self.arbol.CrearNodo(casilla_adyacente, nodo_actual.coste_acumulado + coste_movimiento, self.DistanciaManhattan(casilla_adyacente), nodo_actual)})
    return False

  def EscribirInstancia(self, fichero_salida) -> None:
    if self.solucionado:
      fichero_salida.write(f"ID {self.id_camino}    Filas: {self.filas}  Columnas: {self.columnas}  Entrada: {self.GetEntrada()}  Salida: {self.GetSalida()}  Camino: {self.arbol.GetCamino()}  Coste: {self.arbol.final.coste_acumulado}  Generados: {self.arbol.generados}  Analizados: {self.arbol.analizados}\n")
    else:
      fichero_salida.write(f"ID {self.id_camino}    Filas: {self.filas}  Columnas: {self.columnas}  Entrada: {self.GetEntrada()}  Salida: {self.GetSalida()}  Camino no encontrado  Generados: {self.arbol.generados}  Analizados: {self.arbol.analizados}\n")
    fichero_salida.write(self.GetLaberintoSolucion())
    fichero_salida.flush()

  def CargarLaberinto(self) -> None:
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
    nueva_fila = int(input("Introduzca la nueva fila de la entrada: "))
    nueva_columna = int(input("Introduzca la nueva columna de la entrada: "))
    self.SetCelda(self.GetEntrada(), '1')
    self.SetCelda((nueva_fila, nueva_columna), '3')
    nueva_fila = int(input("Introduzca la nueva fila de la salida: "))
    nueva_columna = int(input("Introduzca la nueva columna de la salida: "))
    self.SetCelda(self.GetSalida(), '1')
    self.SetCelda((nueva_fila, nueva_columna), '4')
  
  def SetCelda(self, coordenadas, valor) -> None:
    fila = self.laberinto[coordenadas[0] - 1]
    self.laberinto[coordenadas[0] - 1] = fila[:coordenadas[1] - 1] + valor + fila[coordenadas[1]:]
  
  def GetCelda(self, coordenadas) -> str:
    return self.laberinto[coordenadas[0] - 1][coordenadas[1] - 1]
  
  def DistanciaManhattan(self, coordenadas_inicial) -> int:
    coordenadas_salida = self.GetSalida()
    return (abs(coordenadas_inicial[0] - coordenadas_salida[0]) + abs(coordenadas_inicial[1] - coordenadas_salida[1])) * COSTE_HORIZONTAL_VERTICAL
  
  def CasillasAdyacentes(self, coordenadas) -> list:
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
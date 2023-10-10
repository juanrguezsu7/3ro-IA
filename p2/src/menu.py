from laberinto import Laberinto

class Menu:
  def __init__(self) -> None:
    self.CargarLaberinto()
    self.CargarArchivoSalida()
   
  def MostrarOpciones(self) -> None:
    while True:
      print("1) Calcular camino.\n2) Cambiar entrada y salida.\n3) Cargar laberinto.\n4) Imprimir laberinto.\n0) Salir.\n")
      opcion = input("Elegir opción: ")
      if opcion == '1':
        self.laberinto.AEstrella()
        self.laberinto.EscribirInstancia(self.fichero_salida)
      elif opcion == '2':
        self.laberinto.CambiarEntradaSalida()
      elif opcion == '3':
        self.CargarLaberinto()
      elif opcion == '4':
        print(self.laberinto)
      elif opcion == '0':
        break

  def CargarArchivoSalida(self) -> None:
    nombre_fichero_salida = input("Introduca un fichero de salida: ")
    while True:
      try:
        self.fichero_salida = open(nombre_fichero_salida, "w+", encoding="utf-8")
        break
      except OSError:
        nombre_fichero_salida = input("Introduca un fichero de salida válido: ")

  def CargarLaberinto(self) -> None:
    self.laberinto = Laberinto()
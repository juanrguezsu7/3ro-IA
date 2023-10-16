"""
Módulo que contiene la clase Menu.

:file: menu.py
:author: Juan Rodríguez Suárez
:date: 14/10/2023
"""

from laberinto import Laberinto
from time import time

class Menu:
  """
  Clase que muestra un menú con distintas opciones para interactuar con un laberinto.
  """

  def __init__(self) -> None:
    """
    Constructor de la clase Menu. Carga el laberinto y el archivo de salida.
    """

    self.CargarLaberinto()
    self.CargarArchivoSalida()

  def MostrarOpciones(self) -> None:
    """
    Muestra las opciones del menú y ejecuta la opción elegida por el usuario.
    """

    while True:
      print("1) Calcular camino.\n2) Cambiar entrada y salida.\n3) Cargar laberinto.\n4) Imprimir laberinto.\n5) Cambiar función heurística.\n0) Salir.\n")
      opcion = input("Elegir opción: ")
      if opcion == '1':
        start_time = time()
        self.laberinto.AEstrella()
        end_time = time()
        print(f"El método AEstrella tardó {end_time - start_time} segundos en ejecutarse usando como función heurística {self.laberinto.GetFuncionHeuristica()}.")
        self.laberinto.EscribirInstancia(self.fichero_salida)
      elif opcion == '2':
        self.laberinto.CambiarEntradaSalida()
      elif opcion == '3':
        self.CargarLaberinto()
      elif opcion == '4':
        print(self.laberinto)
      elif opcion == '5':
        self.laberinto.CambiarFuncionHeuristica()
      elif opcion == '0':
        break

  def CargarArchivoSalida(self) -> None:
    """
    Carga el archivo de salida.
    """

    nombre_fichero_salida = input("Introduca un fichero de salida: ")
    while True:
      try:
        self.fichero_salida = open(nombre_fichero_salida, "w+", encoding="utf-8")
        break
      except OSError:
        nombre_fichero_salida = input("Introduca un fichero de salida válido: ")

  def CargarLaberinto(self) -> None:
    """
    Carga el laberinto.
    """
    
    self.laberinto = Laberinto()
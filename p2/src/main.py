"""
Módulo principal del programa cliente. Instancia un objeto de la clase Menu y
muestra las opciones disponibles para encontrar el camino óptimo de un laberinto.

:file: main.py
:author: Juan Rodríguez Suárez
:date: 14/10/2023
"""

from sys import exit
from menu import Menu

def main():
  """
  Función principal. Instancia un Menu para el programa cliente.

  :return:
  """
  
  menu = Menu()
  menu.MostrarOpciones()
  exit(0)

if __name__ == "__main__":
  main()
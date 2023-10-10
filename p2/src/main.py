from sys import exit
from menu import Menu

def main():
  """
  Función principal. Instancia un Menu para el programa cliente.

  :return: None.
  """
  
  menu = Menu()
  menu.MostrarOpciones()
  exit(0)

if __name__ == "__main__":
  main()
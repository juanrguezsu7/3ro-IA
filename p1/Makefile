CC = g++
CXXFLAGS = -std=c++17 -o
OBJ = camino

all: ${OBJ}

${OBJ}:
	${CC} ${CXXFLAGS} $@ client.cpp menu.cpp grafo.cpp arbol.cpp nodo.cpp
clean:
	rm -f ${OBJ}
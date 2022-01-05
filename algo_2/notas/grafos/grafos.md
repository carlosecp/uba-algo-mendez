# Grafos

## DFS (Depth-First Search)

El recorrido en profundidad consiste en ir recorriendo el grafo empezando desde
un vertice cualquiera , y a cada paso se visita un vertice adyacente al ultimo
visitado. Para realizar este recorrido es de mucha ayuda utilizar una pila. Los
pasos para recorrer un grafo con DFS son:

1. Apila un nodo.
2. Desapilo un nodo de la pila. En este momento "visito" el nodo, es decir, le
aplico una operacion cualquiera. Tambien debo marcar el nodo como visitado de
alguna forma para no volver a pasar por este nodo.
3. Apilo los nodos adyacentes al nodo que acabo de desapilar. Aca tambien es
conveniente marcar un nodo como apilado, para saber que no se ha visitado, pero
ya ha sido agregado a la pila.
4. Repetir hasta que haya visitado todos los nodos.

Practicamente voy avanzando por los nodos adyacentes que puedo hasta que me
quedo sin nodos adyacentes que visitar (voy lo mas "profundo" que puedo). Luego
voy complementando los nodos que me faltaron en el camino.

## BFS (Breath-First Search)

El recorrido en anchura consiste en ir recorriendo el grafo empezando desde un
vertice cualquiera, y a cada paso se visita el vertice adyacente mas cercano.
Practicamente es el mismo DFS, pero se implementa con una cola en vez de pila.

Este algoritmo permite recorrer un ABB por niveles.

## Djiskstra



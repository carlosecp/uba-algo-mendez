#!/usr/bin/env -S python3 -i

import math

class Grafo():
    """
    Un grafo es un par ordenado G=(V,E), donde V es el conjunto de vertices o
    nodos, y E es el numero de aristas que conectan dichos nodos.

    ## Clasificacion

    * Grafos Dirigidos o No Dirigidos: En base a si sus aristas tienen sentido.
    * Grafos Pesados o Dispersos: Un grafo es considerado pesado si sus aristas
    tienen pesos asignados.
    * Grafo Nulo y Vacio: Un grafo es nulo cuando no se tiene absolumente
    ningun nodo, y por supuesto, ninguna arista. Un grafo es vacio cuando si
    tiene nodo pero no estan unidas entre si, es decir, no tiene aristas.
    * Grafo Simple: No tiene ni bucles ni aristas paralelas (dos aristas que
    conectan un mismo nodo).
    * Grafo Completo: Un grafo es completo cuando tiene todas las aristas
    posibles. En caso contrario simplemente es incompleto.

    ## Caminos

    Un camino es una secuencia de vertices (unidos por aristas) en las que no
    puede haber nodos repetidos, es decir que se puede visitar solamente una
    vez cada nodo (excepto el primer y ultimo nodo del camino).

    * Ciclo: Es un camino que inicia y termina en el mismo nodo. Tengo que
    pasar por nodos que no se repitan para llegar a un nodo, para que se siga
    considerando un camino. Es decir, no hay "callejones sin salida", porque
    tendria que volver a pasar por el ultimo nodo para encontrar una salida.

    * Grafo Conexo: Empezando desde cualquier nodo, hay al menos un camino
    hacia cualquier otro nodo del grafo. Es practicamente decir que todos los
    nodos del grafo estan conectados en al menos una forma.

    ## Random

    * Un grafo es un arbol si es conexo y aciclico.
    """


class Grafo_Matriz_Adyacencia(Grafo):
    """
    Los grafos se pueden representar utilizando una matriz conocida como matriz
    de adyacencia, en la que cada celda (interseccion de una columna y una
    fila) representa el peso de la arista que conecta al nodo que representa
    cada fila con el nodo que representa cada columna, o `Infty` en caso de que
    no haya arista que una a dicho nodos (puede ser cualquier valor absurdo
    para inidicar que no hay arista ahi).
    """

    def __init__(self, vertices: list[str]):
        n = len(vertices)
        self.matriz = [[math.inf for _ in range(n)] for _ in range(n)]

    def insertar_arista(self, origen: int, destino: int, peso: float, dirigida = False):
        self.matriz[origen][destino] = peso
        if dirigida:
            self.matriz[destino][origen] = peso

    def eliminar_arista(self, origen: int, destino: int):
        self.matriz[origen][destino] = math.inf

    def obtener_distancia(self, origen: int, destino: int):
        return self.matriz[origen][destino]

    def obtener_adyacencias(self, nodo: int):
        return sum([1 for adyacencia in self.matriz[nodo] if not adyacencia == math.inf])


class Grafo_Hash_De_Hashes(Grafo):
    """
    De manera practicamente igual a la matriz de adyacencia, podemos utilizar
    valores literales (strings) en vez de solo numeros para representar las
    filas y columnas.
    """

    def __init__(self, claves: list[str]):
        self.hash = {clave: {adyacencia: math.inf for adyacencia in claves} for clave in claves}

    def insertar_arista(self, origen: str, destino: str, peso: float, dirigida = False):
        self.hash[origen][destino] = peso
        if dirigida:
            self.hash[destino][origen] = peso

    def eliminar_arista(self, origen: str, destino: str):
        self.hash[origen][destino] = math.inf

    def obtener_distancia(self, origen: str, destino: str):
        if origen not in self.hash or destino not in self.hash[origen]:
            return math.inf
        return self.hash[origen][destino]

    def obtener_adyacencias(self, clave: str):
        if clave not in self.hash:
            return 0
        return sum([1 for adyacencia in self.hash[clave] if not adyacencia == math.inf])


vertices = ["FIUBA", "Carlos", "Caro", "Alguien"]
grafo_matriz = Grafo_Matriz_Adyacencia(vertices)
grafo_hash = Grafo_Hash_De_Hashes(vertices)

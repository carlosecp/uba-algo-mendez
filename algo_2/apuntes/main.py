class Nodo:
    def __init__(self, elemento) -> None:
        self.elemento = elemento
        self.siguiente = None


class Lista:
    def __init__(self) -> None:
        self.nodo_inicio = None
        self.tamanio = 0


def main() -> None:
    lista = Lista()
    print(lista)


if __name__ == "__main__":
    main()

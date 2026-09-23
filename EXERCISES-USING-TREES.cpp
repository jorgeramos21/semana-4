#include <iostream>
#include <algorithm>
using namespace std;

// Nodo del arbol binario
class Nodo {
public:
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(int valor) {
        dato = valor;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

// Arbol Binario de Busqueda
class ArbolPrimos {
private:
    Nodo* raiz;

    Nodo* insertar(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }

        if (valor < nodo->dato) {
            nodo->izquierdo = insertar(nodo->izquierdo, valor);
        } else {
            nodo->derecho = insertar(nodo->derecho, valor);
        }

        return nodo;
    }

    void inorden(Nodo* nodo) {
        if (nodo != nullptr) {
            inorden(nodo->izquierdo);
            cout << nodo->dato << " ";
            inorden(nodo->derecho);
        }
    }

    int contarHojas(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0;
        }

        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            return 1;
        }

        return contarHojas(nodo->izquierdo) +
               contarHojas(nodo->derecho);
    }

    int calcularAltura(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0;
        }

        return 1 + max(calcularAltura(nodo->izquierdo),
                       calcularAltura(nodo->derecho));
    }

public:
    ArbolPrimos() {
        raiz = nullptr;
    }

    void insertar(int valor) {
        raiz = insertar(raiz, valor);
    }

    void mostrarInorden() {
        inorden(raiz);
        cout << endl;
    }

    int obtenerCantidadHojas() {
        return contarHojas(raiz);
    }

    int obtenerAltura() {
        return calcularAltura(raiz);
    }
};

int main() {
    ArbolPrimos arbol;

    int primos[15] = {
        2, 3, 5, 7, 11,
        13, 17, 19, 23, 29,
        31, 37, 41, 43, 47
    };

    for (int i = 0; i < 15; i++) {
        arbol.insertar(primos[i]);
    }

    cout << "=== ARBOL DE NUMEROS PRIMOS ===" << endl;

    cout << "\nNumeros primos en inorden:" << endl;
    arbol.mostrarInorden();

    cout << "\nCantidad de nodos hoja: "
         << arbol.obtenerCantidadHojas() << endl;

    cout << "Altura del arbol: "
         << arbol.obtenerAltura() << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Clase que representa una red de computadoras mediante un grafo
class RedComputadoras {
private:
    int cantidadComputadoras;
    vector<vector<int>> conexiones;

public:
    // Constructor
    RedComputadoras(int cantidad) {
        cantidadComputadoras = cantidad;
        conexiones.resize(cantidad);
    }

    // Agregar una conexion entre dos computadoras
    void agregarConexion(int computadora1, int computadora2) {
        conexiones[computadora1].push_back(computadora2);
        conexiones[computadora2].push_back(computadora1);
    }

    // Mostrar las conexiones de la red
    void mostrarRed() {
        cout << "\n=== CONEXIONES DE LA RED ===" << endl;

        for (int i = 0; i < cantidadComputadoras; i++) {
            cout << "Computadora " << i << ": ";

            for (int vecino : conexiones[i]) {
                cout << vecino << " ";
            }

            cout << endl;
        }
    }

    // BFS para simular la propagacion de una actualizacion
    void propagarActualizacion(int inicio) {
        vector<bool> visitado(cantidadComputadoras, false);
        queue<int> cola;

        visitado[inicio] = true;
        cola.push(inicio);

        cout << "\nOrden de propagacion de la actualizacion:" << endl;

        while (!cola.empty()) {
            int actual = cola.front();
            cola.pop();

            cout << "Computadora " << actual << " ";

            for (int vecino : conexiones[actual]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    cola.push(vecino);
                }
            }
        }

        cout << endl;
    }

    // Calcular el numero minimo de saltos utilizando BFS
    int minimoSaltos(int origen, int destino) {
        vector<bool> visitado(cantidadComputadoras, false);
        vector<int> distancia(cantidadComputadoras, -1);
        queue<int> cola;

        visitado[origen] = true;
        distancia[origen] = 0;
        cola.push(origen);

        while (!cola.empty()) {
            int actual = cola.front();
            cola.pop();

            if (actual == destino) {
                return distancia[actual];
            }

            for (int vecino : conexiones[actual]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    distancia[vecino] = distancia[actual] + 1;
                    cola.push(vecino);
                }
            }
        }

        return -1;
    }
};

int main() {
    // Crear una red con 6 computadoras
    RedComputadoras red(6);

    // Crear conexiones entre las computadoras
    red.agregarConexion(0, 1);
    red.agregarConexion(0, 2);
    red.agregarConexion(1, 3);
    red.agregarConexion(2, 3);
    red.agregarConexion(2, 4);
    red.agregarConexion(3, 5);
    red.agregarConexion(4, 5);

    cout << "=== RED DE COMPUTADORAS ===" << endl;

    red.mostrarRed();

    // Simular propagacion desde la computadora 0
    red.propagarActualizacion(0);

    // Calcular distancia minima
    int origen = 0;
    int destino = 5;

    int saltos = red.minimoSaltos(origen, destino);

    cout << "\nNumero minimo de saltos entre la computadora "
         << origen << " y la computadora " << destino
         << ": " << saltos << endl;

    return 0;
}
#include "Grafo.h"
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>


// Constructor
Grafo::Grafo(unsigned int nodos) : numNodos(nodos), adjList(nodos) {}


const Vertex& Grafo::obtenerVertice(int indice) const {
    if (indice < 0 || static_cast<size_t>(indice) >= listaVertices.size()) {
        std::cerr << "Error: Índice fuera de rango. Índice solicitado: " << indice 
                  << ", Tamaño de listaVertices: " << listaVertices.size() << std::endl;
        throw std::out_of_range("Índice fuera de rango.");
    }

    auto it = listaVertices.begin();
    std::advance(it, indice);
    return *it;
}

void Grafo::agregarVertice(const Vertex& nuevoVertice) {
    listaVertices.push_back(nuevoVertice);
    adjList.emplace_back(); // Agrega una nueva lista de adyacencia para el nuevo vértice.
    numNodos++; // Incrementa el contador de nodos.
}

// Agregar una arista con peso entre dos vértices
void Grafo::agregarArista(const Vertex& origen, const Vertex& destino) {
    int peso = distanciaEuclidiana(origen, destino);

    // Agregar la conexión en ambas direcciones (si el grafo es no dirigido)
    auto itOrigen = std::next(adjList.begin(), origen.obtenerIndiceVer());
    auto itDestino = std::next(adjList.begin(), destino.obtenerIndiceVer());

    itOrigen->emplace_back(destino.obtenerIndiceVer(), peso);
    itDestino->emplace_back(origen.obtenerIndiceVer(), peso);
}

// Imprimir el grafo en formato de lista de adyacencia
void Grafo::imprimirGrafo() const {
    int nodo = 0;
    for (const auto& lista : adjList) {
        std::cout << "Nodo " << nodo++ << ": ";
        for (const auto& [destino, peso] : lista) {
            std::cout << " -> (Destino: " << destino << ", Peso: " << peso << ")";
        }
        std::cout << "\n";
    }
}

// Calcular la distancia euclidiana entre dos vértices
int Grafo::distanciaEuclidiana(const Vertex& a, const Vertex& b) {
    int dx = static_cast<int>(a.obtenerX() - b.obtenerX());
    int dy = static_cast<int>(a.obtenerY() - b.obtenerY());
    int dz = static_cast<int>(a.obtenerZ() - b.obtenerZ());
    return static_cast<int>(std::sqrt(dx * dx + dy * dy + dz * dz));
}

// Obtener el número de nodos
unsigned int Grafo::obtenerNumeroDeNodos() const {
    return numNodos;
}

// Algoritmo de Dijkstra para encontrar la ruta más corta desde un nodo
std::list<int> Grafo::dijkstra(int origen) const {
    std::vector<int> distancias(numNodos, std::numeric_limits<int>::max());
    distancias[origen] = 0;

    std::list<int> procesados;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> cola;
    cola.emplace(0, origen);

    while (!cola.empty()) {
        int distanciaActual = cola.top().first;
        int nodoActual = cola.top().second;
        cola.pop();

        if (distanciaActual > distancias[nodoActual]) continue;

        procesados.push_back(nodoActual);

        auto itLista = std::next(adjList.begin(), nodoActual);
        for (const auto& [destino, peso] : *itLista) {
            int nuevaDistancia = distanciaActual + peso;
            if (nuevaDistancia < distancias[destino]) {
                distancias[destino] = nuevaDistancia;
                cola.emplace(nuevaDistancia, destino);
            }
        }
    }

    return procesados;
}

Grafo crearGrafoDesdeObjeto(const Mesh& objeto) {
    // Obtener la lista de caras del objeto
    std::list<Face> caras = objeto.obtenerCaras();
    
    // Contar todos los vértices únicos del objeto
    unsigned int numVertices = objeto.obtenerCantidadVerticesObj();
    Grafo grafo(numVertices);

    // Iterar sobre las caras y sus aristas para agregar conexiones al grafo
    for (const auto& cara : caras) {
        std::list<Arista> aristas = cara.obtenerListaAristas();
        for (const auto& arista : aristas) {
            std::list<Vertex> vertices = arista.obtenerListaVertices();
           
            if (vertices.size() == 2) {
                auto it = vertices.begin();
                Vertex origen = *it++;
                Vertex destino = *it;
                grafo.agregarArista(origen, destino);
            }
        }
    }

    return grafo;
}

// Encontrar la ruta más corta entre dos vértices específicos
void Grafo::rutaCorta(int id1, int id2, const std::string& nombreObjeto) const {
    if (id1 == id2) {
        std::cout << "(Índices iguales) Los índices de los vértices dados son iguales." << std::endl;
        return;
    }

    if (id1 < 0 || id2 < 0 || id1 >= numNodos || id2 >= numNodos) {
        std::cout << "(Índices no existen) Algunos de los índices de vértices están fuera de rango para el objeto " << nombreObjeto << "." << std::endl;
        return;
    }

    std::vector<int> distancias(numNodos, std::numeric_limits<int>::max());
    distancias[id1] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> cola;
    cola.emplace(0, id1);

    std::vector<int> predecesores(numNodos, -1);

    while (!cola.empty()) {
        int distanciaActual = cola.top().first;
        int nodoActual = cola.top().second;
        cola.pop();

        if (distanciaActual > distancias[nodoActual]) continue;

        auto itLista = std::next(adjList.begin(), nodoActual);
        for (const auto& [destino, peso] : *itLista) {
            int nuevaDistancia = distanciaActual + peso;
            if (nuevaDistancia < distancias[destino]) {
                distancias[destino] = nuevaDistancia;
                cola.emplace(nuevaDistancia, destino);
                predecesores[destino] = nodoActual;
            }
        }
    }

    if (distancias[id2] == std::numeric_limits<int>::max()) {
        std::cout << "No hay una ruta entre los vértices " << id1 << " y " << id2 << " en el objeto " << nombreObjeto << "." << std::endl;
        return;
    }

    // Reconstruir la ruta
    std::list<int> ruta;
    for (int at = id2; at != -1; at = predecesores[at]) {
        ruta.push_front(at);
    }

    // Imprimir la ruta
    std::cout << "(Resultado exitoso) La ruta más corta que conecta los vértices " << id1 << " y " << id2 << " del objeto " << nombreObjeto << " pasa por: ";
    for (int nodo : ruta) {
        std::cout << nodo << " ";
    }
    std::cout << ", con una longitud de " << distancias[id2] << "." << std::endl;
}

void Grafo::rutaCortaCentro(int id, const std::string& nombreObjeto) {
    // Verificar que el índice está en el rango válido
    if (id < 0 || id >= numNodos) {
        std::cout << "(Índice no existe) El índice del vértice está fuera de rango para el objeto " << nombreObjeto << "." << std::endl;
        return;
    }

    // Calcular el centroide del objeto
    unsigned int sumaX = 0, sumaY = 0, sumaZ = 0;
    for (const auto& lista : adjList) {
        for (const auto& [destino, peso] : lista) {
            const Vertex& vertice = obtenerVertice(destino); // Suponemos que existe un método para obtener un vértice por índice
            sumaX += vertice.obtenerX();
            sumaY += vertice.obtenerY();
            sumaZ += vertice.obtenerZ();
        }
    }

    unsigned int numVertices = obtenerNumeroDeNodos();
    unsigned int centroX = sumaX / numVertices;
    unsigned int centroY = sumaY / numVertices;
    unsigned int centroZ = sumaZ / numVertices;

    Vertex centroide(centroX, centroY, centroZ);
    int idCentroide = numNodos; // Asignar un nuevo índice al centroide

    // Agregar el centroide como un nuevo vértice al grafo
    agregarVertice(centroide); // Este método debe ser implementado

    // Conectar el centroide al vértice más cercano
    int verticeMasCercano = -1;
    int distanciaMinima = std::numeric_limits<int>::max();

    for (int i = 0; i < numNodos; ++i) {
        int distancia = distanciaEuclidiana(obtenerVertice(i), centroide);
        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            verticeMasCercano = i;
        }
    }

    agregarArista(obtenerVertice(verticeMasCercano), centroide);

    // Encontrar la ruta más corta desde el vértice dado al centroide
    std::vector<int> distancias(numNodos + 1, std::numeric_limits<int>::max());
    distancias[id] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> cola;
    cola.emplace(0, id);

    std::vector<int> predecesores(numNodos + 1, -1);

    while (!cola.empty()) {
        int distanciaActual = cola.top().first;
        int nodoActual = cola.top().second;
        cola.pop();

        if (distanciaActual > distancias[nodoActual]) continue;

        auto itLista = std::next(adjList.begin(), nodoActual);
        for (const auto& [destino, peso] : *itLista) {
            int nuevaDistancia = distanciaActual + peso;
            if (nuevaDistancia < distancias[destino]) {
                distancias[destino] = nuevaDistancia;
                cola.emplace(nuevaDistancia, destino);
                predecesores[destino] = nodoActual;
            }
        }
    }

    if (distancias[idCentroide] == std::numeric_limits<int>::max()) {
        std::cout << "No hay una ruta entre el vértice " << id << " y el centroide del objeto " << nombreObjeto << "." << std::endl;
        return;
    }

    // Reconstruir la ruta
    std::list<int> ruta;
    for (int at = idCentroide; at != -1; at = predecesores[at]) {
        ruta.push_front(at);
    }

    // Imprimir la ruta
    std::cout << "(Resultado exitoso) La ruta más corta que conecta el vértice " << id << " con el centro del objeto " << nombreObjeto << " ubicado en (" << centroX << ", " << centroY << ", " << centroZ << ") pasa por: ";
    for (int nodo : ruta) {
        std::cout << nodo << " ";
    }
    std::cout << ", con una longitud de " << distancias[idCentroide] << "." << std::endl;
}


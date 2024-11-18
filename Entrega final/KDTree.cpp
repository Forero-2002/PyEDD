#include "KDTree.h"
#include <cmath>
#include <stdexcept>
#include <limits>

// Constructor de KDNode
KDNode::KDNode(Vertex v, int d) : vertice(v), profundidad(d), izquierda(nullptr), derecha(nullptr) {}

// Constructor del KDTree
KDTree::KDTree() : raiz(nullptr) {}

// Destructor del KDTree
KDTree::~KDTree() {
    destruir(raiz); // Llamar a la función que libera la memoria de todos los nodos
}

// Función para liberar memoria recursivamente
void KDTree::destruir(KDNode* nodo) {
    if (nodo != nullptr) {
        destruir(nodo->izquierda);
        destruir(nodo->derecha);
        delete nodo;
    }
}

// Función para construir el árbol recursivamente
KDNode* KDTree::construir(std::list<Vertex>& vertices, int profundidad) {
    if (vertices.empty()) {
        return nullptr;
    }

    // Determinar el eje de división (x=0, y=1, z=2)
    int eje = profundidad % 3;

    // Ordenar la lista de vértices según el eje actual
    vertices.sort([eje](const Vertex& a, const Vertex& b) {
        if (eje == 0) return a.obtenerX() < b.obtenerX();
        else if (eje == 1) return a.obtenerY() < b.obtenerY();
        else return a.obtenerZ() < b.obtenerZ();
    });

    // Dividir en el nodo mediano
    auto mediano = std::next(vertices.begin(), vertices.size() / 2);
    Vertex nodoVertice = *mediano;

    // Crear el nodo
    KDNode* nodo = new KDNode(nodoVertice, profundidad);

    // Crear las listas izquierda y derecha
    std::list<Vertex> izquierda(vertices.begin(), mediano);
    std::list<Vertex> derecha(std::next(mediano), vertices.end());

    // Recursivamente construir los hijos
    nodo->izquierda = construir(izquierda, profundidad + 1);
    nodo->derecha = construir(derecha, profundidad + 1);

    return nodo;
}

// Función pública para construir el árbol con una lista de vértices
void KDTree::construir(std::list<Vertex>& vertices) {
    raiz = construir(vertices, 0);
}

// Función para calcular la distancia euclidiana entre dos vértices
int distanciaEuclidiana(const Vertex& a, const Vertex& b) {
    int dx = static_cast<int>(a.obtenerX() - b.obtenerX());
    int dy = static_cast<int>(a.obtenerY() - b.obtenerY());
    int dz = static_cast<int>(a.obtenerZ() - b.obtenerZ());
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Función recursiva para encontrar el vecino más cercano
Vertex KDTree::vecinoMasCercano(KDNode* nodo, const Vertex& punto, int profundidad, Vertex mejor) {
    if (nodo == nullptr) {
        return mejor;
    }

    // Actualizar el mejor punto encontrado si es más cercano
    int mejorDistancia = distanciaEuclidiana(mejor, punto);
    int distanciaNodo = distanciaEuclidiana(nodo->vertice, punto);

    if (distanciaNodo < mejorDistancia) {
        mejor = nodo->vertice;
    }

    // Determinar el eje actual (x, y o z)
    int eje = profundidad % 3;
    bool irIzquierda = false;

    // Decidir si ir a la izquierda o a la derecha
    if (eje == 0) irIzquierda = punto.obtenerX() < nodo->vertice.obtenerX();
    else if (eje == 1) irIzquierda = punto.obtenerY() < nodo->vertice.obtenerY();
    else irIzquierda = punto.obtenerZ() < nodo->vertice.obtenerZ();

    // Buscar en la rama más prometedora primero
    KDNode* primeraRama = irIzquierda ? nodo->izquierda : nodo->derecha;
    KDNode* segundaRama = irIzquierda ? nodo->derecha : nodo->izquierda;

    mejor = vecinoMasCercano(primeraRama, punto, profundidad + 1, mejor);

    // Verificar si es necesario revisar la otra rama
    if (eje == 0 && std::abs(static_cast<int>(punto.obtenerX()) - static_cast<int>(nodo->vertice.obtenerX())) < mejorDistancia ||
        eje == 1 && std::abs(static_cast<int>(punto.obtenerY()) - static_cast<int>(nodo->vertice.obtenerY())) < mejorDistancia ||
        eje == 2 && std::abs(static_cast<int>(punto.obtenerZ()) - static_cast<int>(nodo->vertice.obtenerZ())) < mejorDistancia) {
        mejor = vecinoMasCercano(segundaRama, punto, profundidad + 1, mejor);
    }

    return mejor;
}

// Función pública para buscar el vecino más cercano
Vertex KDTree::buscarVecinoMasCercano(const Vertex& punto) {
    if (raiz == nullptr) {
        throw std::runtime_error("El árbol KD está vacío");
    }
    return vecinoMasCercano(raiz, punto, 0, raiz->vertice);
}

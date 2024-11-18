#ifndef KDTREE_H
#define KDTREE_H

#include "Vertex.h"
#include <list>

// Clase para representar un nodo en el k-d tree
class KDNode {
public:
    Vertex vertice;        // Vértice que almacena este nodo
    KDNode* izquierda;     // Hijo izquierdo
    KDNode* derecha;       // Hijo derecho
    int profundidad;       // Profundidad actual para saber en qué eje dividir

    KDNode(Vertex v, int d); // Constructor
};

// Clase para el k-d tree en sí
class KDTree {
private:
    KDNode* raiz;          // Raíz del k-d tree
    KDNode* construir(std::list<Vertex>& vertices, int profundidad); // Construir el árbol
    void destruir(KDNode* nodo); // Para liberar la memoria del árbol
    Vertex vecinoMasCercano(KDNode* nodo, const Vertex& punto, int profundidad, Vertex mejor); // Búsqueda del vecino más cercano

public:
    KDTree();              // Constructor
    ~KDTree();             // Destructor
    void construir(std::list<Vertex>& vertices); // Construir el árbol con una lista de vértices
    Vertex buscarVecinoMasCercano(const Vertex& punto); // Función para buscar el vecino más cercano
    int distanciaEuclidiana(const Vertex& a, const Vertex& b);
};

#endif

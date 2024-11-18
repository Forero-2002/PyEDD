#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include <utility> // Para std::pair
#include <iostream>
#include <limits>  // Para std::numeric_limits
#include <algorithm>
#include <vector>
#include "Vertex.h"
//#include "Arista.h"
#include "Mesh.h"

class Grafo{
    private:
    std::vector<Vertex> listaVertices;
    unsigned int numNodos; // Número total de nodos en el grafo
    std::list<std::list<std::pair<int, int>>> adjList; // Lista de adyacencia: nodo -> [(nodo_destino, peso)]

    public:
    // Constructor
    Grafo(unsigned int nodos);

    // Métodos para construir y manipular el grafo
    void agregarArista(const Vertex& origen, const Vertex& destino); // Agregar una arista con peso
    void imprimirGrafo() const;                                      // Imprimir el grafo en formato de lista de adyacencia

    // Algoritmos de rutas más cortas
    std::list<int> dijkstra(int origen) const; // Ruta más corta desde un nodo usando Dijkstra

    const Vertex& obtenerVertice(int indice) const;
    void agregarVertice(const Vertex& nuevoVertice);

    // Funciones auxiliares
    static int distanciaEuclidiana(const Vertex& a, const Vertex& b); // Cálculo del peso de una arista
    void rutaCorta(int id1, int id2, const std::string& nombreObjeto) const;
    // Getters
    unsigned int obtenerNumeroDeNodos() const;
    void rutaCortaCentro(int id, const std::string& nombreObjeto);
    void agregarVerticeUnico(const Vertex& vertice);
};

    Grafo crearGrafoDesdeObjeto(const Mesh& objeto); 
    

#endif


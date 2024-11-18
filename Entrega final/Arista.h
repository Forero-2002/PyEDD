#ifndef ARISTA_H
#define ARISTA_H

#include <list>
#include "Vertex.h"
  
class Arista{
    private: 
    unsigned int idAris;
    std::list<Vertex> listaVertices;
  
    public:
    //Getters
    unsigned int obtenerIndiceAr();
    std::list<Vertex> obtenerListaVertices() const;
    //setters
    void fijarIndiceAr(unsigned int index);
    void fijarListaVertices(std::list<Vertex> lista);
    void fijarVertices(unsigned int x, unsigned int y, unsigned int z);
    //manipulacion de vertices y aristas.
    void imprimirArista();
    void agregarVertice(Vertex vertex);
    void eliminarVertice(int vertexIndex);
    unsigned int contarVertices(std::list<Vertex> lista);
    Arista();
    
};

#endif
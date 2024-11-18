#ifndef FACE_H
#define FACE_H

#include "Arista.h"
#include <list>

class Face{
    private:
    unsigned int idFace;
    unsigned int cantiVerCar;//Cantidad de vertices
    std::list<Arista> listaAristas;

    public:
    unsigned int obtenerIndiceCar();
    unsigned int obtenerCantidadVerticesCar();
    std::list<Arista> obtenerListaAristas() const;

    void fijarIndiceCar(unsigned int indice);
    void fijarCantidadVerticesCar(unsigned int cantVertices);
    void fijarListaAristas(std::list<Arista> lista);

    void imprimirCara();
    void agregarArista(Arista edge);
    void eliminarArista(int edgeIndex);
    unsigned int contarAristas(std::list<Arista> lista);
    Face();
};

#endif
#ifndef VERTICE_H
#define VERTICE_H

#include <vector>
#include <ostream>
#include <iostream>

class Vertice {
private:
    unsigned int indiceVer;
    unsigned int x;
    unsigned int y;
    unsigned int z;

public:
    // Constructor
    Vertice();
    Vertice(unsigned int x, unsigned int y, unsigned int z);

    // Getters
    unsigned int obtenerX();
    unsigned int obtenerY();
    unsigned int obtenerZ();
    unsigned int obtenerIndiceVer();
    
    // Setters
    void fijarX(unsigned int x);
    void fijarY(unsigned int y);
    void fijarZ(unsigned int z);
    void fijarIndiceVer(unsigned int index);

    // Método para imprimir el vértice
    void imprimirVertice();

    /*Sobrecarga para operador de igualdad*/
    friend bool operator==(const Vertice& v1, const Vertice& v2);

    /*Sobrecarga para operador de salida*/
    friend std::ostream& operator<<(std::ostream& os, const Vertice& vertice);

    // Método para calcular las esquinas de la caja envolvente
    std::vector<Vertice> calcularEsquinasCaja(unsigned int xmin, unsigned int xmax, unsigned int ymin, unsigned int ymax, unsigned int zmin, unsigned int zmax);
};

#endif // VERTICE_H

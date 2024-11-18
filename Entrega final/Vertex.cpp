#include "Vertex.h"
#include <iostream> 

//Constructor vacío
Vertex::Vertex(){}

Vertex::Vertex(unsigned int x, unsigned int y, unsigned int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

//Getters
unsigned int Vertex::obtenerX() const {
    return x;
}

unsigned int Vertex::obtenerY() const {
    return y;
}

unsigned int Vertex::obtenerZ()const {
    return z;
}

unsigned int Vertex::obtenerIndiceVer() const {
    return idVer;
}

//Setters
void Vertex::fijarX(unsigned int x) {
    this->x = x;
}

void Vertex::fijarY(unsigned int y) {
    this->y = y;
}

void Vertex::fijarZ(unsigned int z) {
    this->z = z;
}

void Vertex::fijarIndiceVer(unsigned int index) {
    idVer = index;
}

void Vertex::imprimirVertice() {
    std::cout<<"Vértice [índice: " << idVer << ", x: " << x << ", y: " << y << ", z: " << z << "]"<<std::endl;
} 


#include "Arista.h"
#include <iostream>

//Constructor vacío
Arista::Arista() {}

//Getters
unsigned int Arista::obtenerIndiceAr() {
    return idAris;
}

std::list<Vertex> Arista::obtenerListaVertices() const{
    return listaVertices;
}

//Setters
void Arista::fijarIndiceAr(unsigned int index) {
    this->idAris = index;
}

void Arista::fijarListaVertices(std::list<Vertex> lista) {
    this->listaVertices = lista;
}

void Arista::fijarVertices(unsigned int x, unsigned int y, unsigned int z) {
    Vertex vertex;
    vertex.fijarX(x);
    vertex.fijarY(y);
    vertex.fijarZ(z);
    listaVertices.push_back(vertex);
}

//Método para imprimir la arista
void Arista::imprimirArista() {
    std::cout << "Arista [índice: " << idAris << "]\n";
    std::cout << "Vértices:\n";

    for (Vertex& vertice : listaVertices) {
        vertice.imprimirVertice();
    }
}

//Método para agregar un vértice a la lista
void Arista::agregarVertice(Vertex vertex) {
    listaVertices.push_back(vertex);
}

//Método para eliminar un vértice de la lista
void Arista::eliminarVertice(int vertexIndex) {
    std::list<Vertex>::iterator itVer;
    std::list<Vertex>::iterator aux;
    
    for(itVer = listaVertices.begin();itVer!=listaVertices.end();itVer++){
        if(itVer->obtenerIndiceVer()==vertexIndex){
            aux = itVer;
            listaVertices.erase(aux);
        }
    }
}

//Método para contar el número de vértices en la lista
unsigned int Arista::contarVertices(std::list<Vertex> lista) {
    return lista.size();
}

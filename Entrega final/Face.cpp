#include "Face.h"
#include <iostream>

//Constructor vacío
Face::Face() {
    // Inicialización si es necesario
}

//Getters
unsigned int Face::obtenerIndiceCar() {
    return idFace;
}

unsigned int Face::obtenerCantidadVerticesCar() {
    return cantiVerCar;
}

std::list<Arista> Face::obtenerListaAristas() const {
    return listaAristas;
}

//Setters
void Face::fijarIndiceCar(unsigned int indice) {
    this->idFace = indice;
}

void Face::fijarCantidadVerticesCar(unsigned int cantVertices) {
    this->cantiVerCar = cantVertices;
}

void Face::fijarListaAristas(std::list<Arista> lista) {
    this->listaAristas = lista;
}

//Método para imprimir la cara
void Face::imprimirCara(){
    std::cout << "Face [índice: " << idFace << ", cantidad de vértices: " << cantiVerCar << "]\n";
    for (Arista& arista : listaAristas) {
        arista.imprimirArista();
    }
}

//Método para agregar una arista a la lista
void Face::agregarArista(Arista edge) {
    listaAristas.push_back(edge);
}

//Método para eliminar una arista de la lista
void Face::eliminarArista(int edgeIndex) {

    std::list<Arista>::iterator itAris;
    std::list<Arista>::iterator aux;
    itAris = listaAristas.begin();

    for(;itAris!=listaAristas.end();itAris++){
        if(itAris->obtenerIndiceAr()==edgeIndex){
            aux = itAris;
            listaAristas.erase(aux);
        }
    }
}

//Método para contar el número de aristas en la lista
unsigned int Face::contarAristas(std::list<Arista> lista) {
    return lista.size();
}

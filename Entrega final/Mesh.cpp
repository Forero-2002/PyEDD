#include "Mesh.h"
#include <iostream>

//Constructor vacío
Mesh::Mesh(){}

//Getters°
std::string Mesh::obtenerNombreObjeto() {
    return this->nombreObjeto;
}

std::list<Face> Mesh::obtenerCaras() const{
    return this->listaCaras;
}

int Mesh::obtenerCantidadVerticesObj() const{
    return this->cantidadVerticesObj;
}

//Setters
void Mesh::fijarNombreObjeto(std::string objectName) {
    this->nombreObjeto = objectName;
}

void Mesh::fijarListaCaras(std::list<Face> listaCaras) {
    this->listaCaras = listaCaras;
}

void Mesh::fijarCantidadVerticesObj(int cantVertices){
    this->cantidadVerticesObj=cantVertices;
}

// Método para agregar una cara a la lista
void Mesh::agregarCara(Face face) {
    listaCaras.push_back(face);
}

// Método para eliminar una cara de la lista
void Mesh::eliminarCara(int faceIndex) {
    std::list<Face>::iterator itCar;
    std::list<Face>::iterator aux;
    itCar = listaCaras.begin();
    for(;itCar!=listaCaras.end();itCar++){
        if(itCar->obtenerIndiceCar()==faceIndex){
            aux = itCar;
            listaCaras.erase(aux);
        }
    }
}


// Método para contar el número de caras en la lista
unsigned int Mesh::contarCaras() {
    return listaCaras.size();
}

//Método para imprimir el objeto
void Mesh::imprimirObjeto() {
    std::cout << "Mesh: " << nombreObjeto << "\n";
    for (Face& cara : listaCaras) {
        cara.imprimirCara();
    }
}

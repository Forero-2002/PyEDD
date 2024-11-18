#ifndef MESH_H
#define MESH_H

#include <string>
#include <list>
#include "Face.h"

class Mesh {
    private:
        std::string nombreObjeto;
        std::list<Face> listaCaras;
        unsigned int cantidadVerticesObj;

    public:
        std::string obtenerNombreObjeto(); 
        std::list<Face> obtenerCaras() const;
        int obtenerCantidadVerticesObj() const;

        void fijarNombreObjeto(std::string objectName);  
        void fijarListaCaras(std::list<Face> listaCaras);
        void fijarCantidadVerticesObj(int cantVertices);

        void agregarCara(Face face);
        void eliminarCara(int faceIndex);  
        unsigned int contarCaras();

        void imprimirObjeto();
        Mesh();
};

#endif
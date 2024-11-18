
#ifndef VERTEX_H
#define VERTEX_H

class Vertex{
    private:
        unsigned int idVer;
        unsigned int x;
        unsigned int y;
        unsigned int z;
    
    public:
        //Getters
        unsigned int obtenerX() const;
        unsigned int obtenerY() const;
        unsigned int obtenerZ() const;
        unsigned int obtenerIndiceVer() const ;
        //Setters
        void fijarX(unsigned int x);
        void fijarY(unsigned int y);
        void fijarZ(unsigned int z);
        void fijarIndiceVer(unsigned int index);
        //Constructor y toString
        void imprimirVertice();
        Vertex();
        Vertex(unsigned int x, unsigned int y, unsigned int z);
};

#endif
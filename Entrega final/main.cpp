#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <fstream>
#include <sstream> 
#include <string>
#include <limits>
#include <vector>
#include "Mesh.h"
#include "KDTree.h"
#include "Grafo.h"

void lecturaArchivos(std::string nombreArchivo, std::list<Mesh>& objetosPrograma);
void listado(std::list<Mesh>& listadoObjetos);
void imprimirListado(std::list<Mesh>& listadoObjetos);
void envolvente(std::string nombreObjeto,std::list<Mesh>& listadoObjetos);
void envolvente(std::list<Mesh>& objetosPrograma);
void descargar(std::string nombreObjeto, std::list<Mesh>& listadoObjetos);
void guardar(std::string nombreObjeto, std::string nombreArchivo, std::list<Mesh>& listadoObjetos);
Mesh encontrarObjeto(std::string nombreObjeto, std::list<Mesh>& listadoObjetos);
void salir();
bool verificacionObjetos(std::string nombreArchivo, std::list<Mesh>& listadoObjetos);
void ayuda(std::string comando);

///////////////////////////////////////////////COMPONENTE 2//////////////////////////////////////////
void v_cercano_nombre_objeto(int px, int py, int pz, std::string nombreObjeto,std::list<Mesh>& objetosPrograma);
void v_cercano(int px, int py, int pz,std::list<Mesh>& objetosPrograma);
void v_cercanos_caja(std::string nombre_objeto,std::list<Mesh>& objetosPrograma);
int distanciaEuclidiana(const Vertex& a, const Vertex& b);
////////////////////////////////////////////COMPONENTE 3///////////////////////////////////////////////////
void ruta_corta_centro(int id, std::string nombreObjeto, std::list<Mesh>& objetosPrograma );

void comandosDisponibles(); 

std::list<Mesh> objetosPrograma;


int main() {
   

    std::list<Mesh> objetosPrograma;

    ///////////////////////////////////////////////COMPONENTE 1////////////////////////////////////////// 

    try{
        std::string comandoUsuario;

        std::vector<std::string> argumentosUsuario; 
        std::string argumento;

        while (true) {
            std::cout << "-----------------------------------------------------------------------------------------------\n";
            std::cout << "Ingrese el comando. \n";
            comandosDisponibles();
            std::cout << "-----------------------------------------------------------------------------------------------\n";

            std::cout << "$";
            std::getline(std::cin, comandoUsuario);
               
            //Se toma la primera entrada por el usuario como el comando 
            std::istringstream stream(comandoUsuario);
            stream >> comandoUsuario;

            /*Se toma el resto de la línea ingresada como argumentos por
            //medio del .pushback() que va metiendo lo leído dentro de
            //argumentosUsuario*/
            argumentosUsuario.clear();
            while (stream >> argumento) {
                    argumentosUsuario.push_back(argumento);
            }
            
            //Comando componente 1 (7/7)
            if (comandoUsuario == "salir") {
                    salir();
                    break;
                //Componente parte interaccion con el usuario 
            }else if(comandoUsuario == "ayuda"){
                        if (!argumentosUsuario.empty()) {
                            ayuda(argumentosUsuario[0]);
                        } else {
                            comandosDisponibles();
                        }
                    //Comando componente 1 (1/7)
                    } else if (comandoUsuario == "cargar") {
                        if (argumentosUsuario.size() == 1) {
                            lecturaArchivos(argumentosUsuario[0], objetosPrograma);
                        } else {
                            std::cout<<"Error"<<std::endl;
                            std::cout << "Uso incorrecto, use 'ayuda cargar' para más información.\n";
                        }
                        //Comando componente 1 (2/7)
                    } else if (comandoUsuario == "listado") {
                        //Salidas en pantalla error 
                        if(objetosPrograma.empty()){
                            std::cout << "(Memoria vacía) Ningún objeto ha sido cargado en memoria." << std::endl;
                        }else {
                            //Salida en pantalla resultadon exitoso
                            
                            std::cout << "\n(Resultado exitoso) Hay " <<objetosPrograma.size() << " objetos en memoria:" <<std::endl;
                            // ACA TENER DISPONIBLE LA LISTA DE OBJETOS y se imprimira lo siguiente:
                            // nombre_objeto_1 contiene n_1 vertexs, a_1 aristas y c_1 caras.
                            listado(objetosPrograma);
                        }
                    //Comando componente (5/7)
                    } else if (comandoUsuario == "descargar") {
                        if (argumentosUsuario.size() == 1) {  
                        // TODO TIENE Q ESTAR CARGADO EN MEMORIA
                            descargar(argumentosUsuario[0], objetosPrograma);
                        } else {
                            std::cout<<"Error"<<std::endl;
                            std::cout<<"Uso incorrecto, use 'ayuda descargar' para más información.\n";
                        }
                    } else if (comandoUsuario == "guardar") {
                        if (argumentosUsuario.size() == 2) {
                        //TODO TIENE QUE ESTAR CARGADO EN MEMORIA
                            guardar(argumentosUsuario[0], argumentosUsuario[1], objetosPrograma);
                        } else {
                            std::cout<<"Error"<<std::endl;
                            std::cout << "Uso incorrecto, use 'ayuda guardar' para más información.\n";
                        }
                    } else if (comandoUsuario == "envolvente") {
                        //TODO DEBE ESTAR CARGADO EN MEMORIA
                        if (argumentosUsuario.size() == 1) {
                            envolvente(argumentosUsuario[0],objetosPrograma);
                        } else if (argumentosUsuario.empty()) {
                            envolvente(objetosPrograma);
                        } else {
                            std::cout<<"Error"<<std::endl;
                            std::cout << "Uso incorrecto, use 'ayuda envolvente' para más información.\n";
                        }
                    }else if (comandoUsuario == "v_cercano") {
                        if (argumentosUsuario.size() == 3) {
                            int px;
                            int py;
                            int pz;
                            std::cout<<" Ingreselas posiciones x, y, z" << std::endl;
                            std::cin>>px>>py>>pz;
                            v_cercano(px, py, pz,objetosPrograma);
                        } else if (argumentosUsuario.empty()) {
                            int px;
                            int py;
                            int pz;
                            std::string nombreObjeto;
                            std::cout<<" Ingreselas posiciones x, y, z y el nombre del objeto: "<<std::endl;
                            std::cin>>px>>py>>pz>>nombreObjeto;
                            v_cercano_nombre_objeto(px, py, pz, nombreObjeto,objetosPrograma);
                        } else {
                            std::cout << "Error: Uso incorrecto. Use 'ayuda v_cercano' para más información." << std::endl;
                        }

                    } else if (comandoUsuario == "ruta_corta") {
                        if (argumentosUsuario.size() == 3) {
                            int id1 = std::stoi(argumentosUsuario[0]);
                            int id2 = std::stoi(argumentosUsuario[1]);
                            std::string nombreObjeto = argumentosUsuario[2];

                            // Buscar el objeto en memoria
                            Mesh objeto = encontrarObjeto(nombreObjeto, objetosPrograma);

                            if (objeto.obtenerNombreObjeto().empty()) {
                                std::cout << "(Objeto no existe) El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
                            } else {
                                // Crear el grafo desde el objeto
                                Grafo grafo = crearGrafoDesdeObjeto(objeto);

                                // Llamar a la función para calcular la ruta más corta
                                grafo.rutaCorta(id1, id2, nombreObjeto);
                            }
                        } else {
                            std::cout << "Error: Uso incorrecto. Use 'ayuda ruta_corta' para más información." << std::endl;
                        }

                    } else if (comandoUsuario == "ruta_corta_centro") {
                        if (argumentosUsuario.size() == 2) {
                            int id = std::stoi(argumentosUsuario[0]);
                            std::string nombreObjeto = argumentosUsuario[1];
                            ruta_corta_centro(id, nombreObjeto, objetosPrograma );
                        } else if (argumentosUsuario.empty()) {
                            int id;
                            std::string nombreObjeto;
                            std::cout<<"Ingresa el indice y el nombre:"<<std::endl;
                            std::cin>>id>>nombreObjeto;
                            ruta_corta_centro(id, nombreObjeto, objetosPrograma );
                        } else {
                            std::cout << "Error: Uso incorrecto. Use 'ayuda ruta_corta_centro' para más información." << std::endl;
                        }

                    } else if (comandoUsuario == "v_cercanos_caja") {
                        if (argumentosUsuario.size() == 1) {
                            std::string nombreObjeto = argumentosUsuario[0];
                            v_cercanos_caja(nombreObjeto,objetosPrograma);
                        } else {
                            std::cout << "Error: Uso incorrecto. Use 'ayuda v_cercanos_caja' para más información." << std::endl;
                        }

                    } else {
                        std::cout<<"    ________________________________________________________________________________\n";
                        std::cout<<"    |                            Comando no reconocido.                            |\n";
                        std::cout<<"    |            Use 'ayuda' para ver la lista de comandos disponibles.            |\n";
                        std::cout<<"    |______________________________________________________________________________|\n";
                    }
        }
        
    }catch(const std::runtime_error& e){
        std::cout << "Error: " << e.what() << '\n';
    }

    return 0;

}

void comandosDisponibles() {
     std::cout << "     _______________________________________________________________________________\n";
     std::cout << "    |                             COMANDOS DISPONIBLES                             |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  cargar nombreArchivo -> Carga un archivo en memoria.                        |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  listado -> Muestra todos los objetos cargados en memoria.                   |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  descargar nombreObjeto -> Descarga un objeto de la memoria.                 |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  guardar nombreObjeto nombreArchivo -> Guarda un objeto en un archivo.       |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  envolvente nombreObjeto -> Crea una envolvente para un objeto.              |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  envolvente -> Calcula y agrega una caja envolvente global que incluye       |\n";
     std::cout << "    |  todos los objetos cargados en memoria.                                      |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  v_cercano nombreObjeto -> Identifica el vértice más cercano al punto.       |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  ayuda comando -> Muestra información de ayuda sobre un comando específico.  |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  salir -> Termina la ejecución de la aplicación.                             |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  v_cercano px py pz nombreObjeto -> Identifica el vértice más                |\n";
     std::cout << "    |  cercano al punto (px, py, pz) en el objeto <nombreObjeto>                   |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  v_cercano px py pz -> Identifica el vértice más cercano al punto            |\n";
     std::cout << "    |  (px, py, pz) entre todos los objetos cargados en memoria.                   |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  v_cercanos_caja nombreObjeto -> Identifica los vértices más cercanos a      |\n";
     std::cout << "    |  las esquinas de la caja envolvente del objeto <nombreObjeto>.               |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  ruta_corta i1 i2 nombreObjeto -> Encuentra la ruta más corta entre          |\n";
     std::cout << "    |  dos vértices de un objeto.                                                  |\n";
     std::cout << "    |                                                                              |\n";
     std::cout << "    |  ruta_corta_centro i1 nombreObjeto -> Encuentra la ruta más corta entre      |\n";
     std::cout << "    |  un vértice y el centro del objeto.                                          |\n";
     std::cout << "    |______________________________________________________________________________|\n";
}


void listado(std::list<Mesh>& listadoObjetos) {
    std::cout<<std::endl;

    std::list<Mesh>::iterator itListado;
    itListado = listadoObjetos.begin();

    for(;itListado!=listadoObjetos.end(); itListado++){
        std::cout<<"______________________________________"<<std::endl;
        itListado->imprimirObjeto();
        std::cout<<std::endl;
    }
}

void envolvente(std::string nombreObjeto,std::list<Mesh>& objetosPrograma) {  
    // Buscar el objeto en la lista
    Mesh objetoEnMemoria;
    bool objetoEncontrado = false;
    // Recorrer la lista de objetos
    if (objetosPrograma.empty()) {
        std::cout << "(Memoria vacía) Ningun objeto ha sido cargado en memoria." << std::endl;
    } else{
        for (std::list<Mesh>::iterator it = objetosPrograma.begin(); it != objetosPrograma.end(); ++it) {
            std::cout << " "<< it->obtenerNombreObjeto()<< std::endl; 
            if (it->obtenerNombreObjeto() == nombreObjeto) {
                std::cout << " Dentro del loop"<< std::endl;
                objetoEnMemoria = *it;
                objetoEncontrado = true;
                break;
            }
        }
    }
    
    //No encontro el objeto en la lista
    if (!objetoEncontrado) {
        std::cout << "(Mesh no existe) El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    //Se inicializa en un valor muy grande para que se pueda comparar con los demás
    float xmin = std::numeric_limits<float>::max();
    float xmax = -std::numeric_limits<float>::max();
    float ymin = std::numeric_limits<float>::max();
    float ymax = -std::numeric_limits<float>::max();
    float zmin = std::numeric_limits<float>::max();
    float zmax = -std::numeric_limits<float>::max();

    std::list<Face> caras = objetoEnMemoria.obtenerCaras();//obtener las caras del objeto

    for (std::list<Face>::iterator itCara = caras.begin(); itCara != caras.end(); itCara++) {//recorrer las caras del objeto

        std::list<Arista> aristas = itCara->obtenerListaAristas();//obtener las aristas de la cara

        for (std::list<Arista>::iterator itArista = aristas.begin(); itArista != aristas.end(); itArista++) {//recorrer las aristas de la cara

            std::list<Vertex> vertexs = itArista->obtenerListaVertices();//obtener los vertexs de la arista

            for (std::list<Vertex>::iterator itVertex = vertexs.begin(); itVertex != vertexs.end(); itVertex++) {//recorrer los vertexs de la arista
                float x = static_cast<float>(itVertex->obtenerX());//obtener el valor de x del vertex
                float y = static_cast<float>(itVertex->obtenerY());//obtener el valor de y del vertex
                float z = static_cast<float>(itVertex->obtenerZ());//obtener el valor de z del vertex

                if (x < xmin){//se compara el valor de x con el valor minimo actual
                    xmin = x;
                } 
                if (x > xmax){//se compara el valor de x con el valor maximo actual
                    xmax = x;
                } 
                if (y < ymin){//se compara el valor de y con el valor minimo actual
                    ymin = y;
                } 
                if (y > ymax){//se compara el valor de y con el valor maximo actual
                    ymax = y;
                } 
                if (z < zmin){//se compara el valor de z con el valor minimo actual
                    zmin = z;
                } 
                if (z > zmax){//se compara el valor de z con el valor maximo actual
                    zmax = z;
                } 
            }
        }
    }

    // Crear un nuevo objeto para la caja envolvente
    Mesh cajaEnvolvente;
    std::string nuevoNombre = "env_" + nombreObjeto;

    cajaEnvolvente.fijarNombreObjeto(nuevoNombre);//Esto es para que el nombre del objeto sea el nombre del objeto mas el prefijo "env_"    

    // Definir los 8 vértices de la caja envolvente
    //En este punto todo estava bien
    std::vector<Vertex> vertexsAux;
    vertexsAux.reserve(8);
    Vertex v1, v2, v3, v4, v5, v6, v7, v8;
    //Primer vertex
    v1.fijarX(static_cast<unsigned int>(xmin));
    std::cout<<"__________________________________________";
    std::cout << "\n| Vertex 1:[ x = " << v1.obtenerX() << ", y = "; 
    v1.fijarY(static_cast<unsigned int>(ymin));
    std::cout<< v1.obtenerY() << ", " << "z = ";; 
    v1.fijarZ(static_cast<unsigned int>(zmin));
    std::cout << v1.obtenerZ() << "] " << "v1 |"<<std::endl; 
    v1.fijarIndiceVer(0);//v1
    vertexsAux.push_back(v1);
    //--------------------------------------------
    //Segundo vertex
    v2.fijarX(static_cast<unsigned int>(xmax));
    std::cout << "| Vertex 2:[ x = " << v2.obtenerX() << ", " << "y = "; 
    v2.fijarY(static_cast<unsigned int>(ymin));
    std::cout << v2.obtenerY() << ", " << "z = "; 
    v2.fijarZ(static_cast<unsigned int>(zmin));
    std::cout  << v2.obtenerZ() << "] " << "v2 |"<<std::endl; 
    v2.fijarIndiceVer(1);//v2
    vertexsAux.push_back(v2);
    //--------------------------------------------
    //Tercer vertex
    v3.fijarX(static_cast<unsigned int>(xmax));
    std::cout << "| Vertex 3:[ x = " << v3.obtenerX() << ", " <<"y= ";
    v3.fijarY(static_cast<unsigned int>(ymax));
    std::cout << v3.obtenerY() << ", " << "z= ";
    v3.fijarZ(static_cast<unsigned int>(zmin));
    std::cout << v3.obtenerZ() << "] " << " v3 |"<<std::endl;
    v3.fijarIndiceVer(2);//v3
    vertexsAux.push_back(v3);
    //--------------------------------------------
    //Cuarto vertex
    v4.fijarX(static_cast<unsigned int>(xmin));
    std::cout << "| Vertex 4:[ x = " << v4.obtenerX() << ", " <<"y = ";
    v4.fijarY(static_cast<unsigned int>(ymax));
    std::cout << v4.obtenerY() << ", " << "z= ";
    v4.fijarZ(static_cast<unsigned int>(zmin)); 
    std::cout << v4.obtenerZ() << "] " << " v4 |"<<std::endl;
    v4.fijarIndiceVer(3);//v4
    vertexsAux.push_back(v4);
    //--------------------------------------------
    //Quinto vertex
    v5.fijarX(static_cast<unsigned int>(xmin));
    std::cout << "| Vertex 5:[ x = " << v5.obtenerX() << ", " <<"y = ";
    v5.fijarY(static_cast<unsigned int>(ymin));
    std::cout << v5.obtenerY() << ", " << "z = ";
    v5.fijarZ(static_cast<unsigned int>(zmax));
    std::cout << v5.obtenerZ() << "] " << " v5 |"<<std::endl;
    v5.fijarIndiceVer(4);//v5
    vertexsAux.push_back(v5);
    //--------------------------------------------
    //Sexto vertex
    v6.fijarX(static_cast<unsigned int>(xmax));
    std::cout << "| Vertex 6:[ x = " << v6.obtenerX() << ", " <<"y = ";
    v6.fijarY(static_cast<unsigned int>(ymin));
    std::cout << v6.obtenerY() << ", " << " z = ";
    v6.fijarZ(static_cast<unsigned int>(zmax));
    std::cout << v6.obtenerZ() << "] " << " v6 |"<<std::endl;
    v6.fijarIndiceVer(5);//v6
    vertexsAux.push_back(v6);
    //--------------------------------------------
    //Septimo vertex
    v7.fijarX(static_cast<unsigned int>(xmax));
    std::cout << "| Vertex 7:[ x = " << v7.obtenerX() << ", " <<"y = ";
    v7.fijarY(static_cast<unsigned int>(ymax)); 
    std::cout << v7.obtenerY() << ", " << "z = ";
    v7.fijarZ(static_cast<unsigned int>(zmax));
    std::cout << v7.obtenerZ() << "] " << " v7 |"<<std::endl;
    v7.fijarIndiceVer(6);//v7
    vertexsAux.push_back(v7);
    //--------------------------------------------
    //Octavo vertex
    v8.fijarX(static_cast<unsigned int>(xmin));
    std::cout << "| Vertex 8:[ x = " << v8.obtenerX() << ", " <<" y = ";
    v8.fijarY(static_cast<unsigned int>(ymax));
    std::cout << v8.obtenerY() << ", " << "z = ";
    v8.fijarZ(static_cast<unsigned int>(zmax));
    std::cout << v8.obtenerZ() << "] " << " v8 |"<<std::endl;
    std::cout<<"_________________________________________"<<std::endl;
    v8.fijarIndiceVer(7);//v8
    vertexsAux.push_back(v8);
    //--------------------------------------------
    std::vector<unsigned int> indices;
        indices.reserve(6); // Reservar espacio para evitar realineaciones innecesarias

        std::cout << std::endl;

        // Recorre los primeros 6 elementos o el tamaño de vertexsAux si es menor
        for (size_t i = 0; i < std::min<size_t>(6, vertexsAux.size()); ++i) {
            unsigned int indice = vertexsAux[i].obtenerIndiceVer();

            if (indice < vertexsAux.size()) {
                indices.push_back(indice);
                std::cout << "Se ha ingresado el índice " << indice << " a la cara" << std::endl;
            } else {
                std::cerr << "Índice de vértice fuera de rango: " << indice << std::endl;
                std::cout << "No se ha agregado ninguna cara tras este mensaje" << std::endl;
                return; // Salir de la función en caso de error
            }

            // Se encuentra el -1 o la lista está vacía, se acaba el ciclo
            if (indices.empty() || indices[0] == static_cast<unsigned int>(-1)) {
                return;
            }
        }

        // Se crea una cara temporal para ir asignándole los vértices
        Face cara;
        cara.fijarCantidadVerticesCar(indices.size() / 2);

        std::list<Arista> aristas;
        std::cout << std::endl;

        // Se crean aristas tomando las posiciones de dos en dos
        for (size_t i = 0; i + 1 < indices.size(); i += 2) {
            unsigned int indiceInicio = indices[i];
            unsigned int indiceFin = indices[i + 1];

            // No se crean aristas si se encuentran con el mismo vértice según el índice
            if (indiceInicio != indiceFin) {
                Arista arista;
                arista.fijarIndiceAr(i / 2);
                arista.agregarVertice(vertexsAux[indiceInicio]);
                arista.agregarVertice(vertexsAux[indiceFin]);

                aristas.push_back(arista);

                std::cout << "\nSe ha ingresado: " << std::endl;
                arista.imprimirArista();
            }
        }

        // Se terminan de asignar los datos a la cara del objeto
        static int indiceCara = 0; // Variable estática para mantener el índice entre llamadas
        cara.fijarIndiceCar(indiceCara++);
        cara.fijarListaAristas(aristas);
        cajaEnvolvente.agregarCara(cara);
    


    // Agregar la caja envolvente a la lista de objetos en memoria
    objetosPrograma.push_back(cajaEnvolvente);
    std::cout<<"_____________________________________________________________________________"<<std::endl;
    std::cout << "\n(Resultado exitoso) La caja envolvente del objeto " << nombreObjeto << " se ha generado con el nombre " << nuevoNombre << " y se ha agregado a los objetos en memoria." << std::endl;

    }

void envolvente(std::list<Mesh>& objetosPrograma) {   
    
    if (objetosPrograma.empty()) {
        std::cout << "(Memoria vacía) Ningún objeto ha sido cargado en memoria." << std::endl;
        return;
    }

    // Inicializar los límites de la caja envolvente
    float xmin = std::numeric_limits<float>::max();
    float xmax = -std::numeric_limits<float>::max();
    float ymin = std::numeric_limits<float>::max();
    float ymax = -std::numeric_limits<float>::max();
    float zmin = std::numeric_limits<float>::max();
    float zmax = -std::numeric_limits<float>::max();

    // Recorrer todos los objetos en memoria     
        for (std::list<Mesh>::iterator itObj = objetosPrograma.begin(); itObj != objetosPrograma.end(); itObj++) {

            std::list<Face> caras = itObj->obtenerCaras();

            for (std::list<Face>::iterator itCara = caras.begin(); itCara != caras.end(); itCara++) {//se recorre cada cara del objeto

                std::list<Arista> aristas = itCara->obtenerListaAristas();

                for (std::list<Arista>::iterator itArista = aristas.begin(); itArista != aristas.end(); itArista++) {//se recorre cada arista de la cara

                    std::list<Vertex> vertexs = itArista->obtenerListaVertices();

                    for (std::list<Vertex>::iterator itVertex = vertexs.begin(); itVertex != vertexs.end(); itVertex++) {//se recorre cada vertex de la arista
                        float x = static_cast<float>(itVertex->obtenerX());//se obtiene el valor de x del vertex
                        float y = static_cast<float>(itVertex->obtenerY());//se obtiene el valor de y del vertex
                        float z = static_cast<float>(itVertex->obtenerZ());//se obtiene el valor de z del vertex

                        if (x < xmin){//se compara el valor de x con el valor minimo actual
                            xmin = x;
                        } 
                        if (x > xmax){//se compara el valor de x con el valor maximo actual
                            xmax = x;
                        } 
                        if (y < ymin){//se compara el valor de y con el valor minimo actual
                            ymin = y;
                        } 
                        if (y > ymax){//se compara el valor de y con el valor maximo actual
                            ymax = y;
                        } 
                        if (z < zmin){//se compara el valor de z con el valor minimo actual
                            zmin = z;
                        } 
                        if (z > zmax){//se compara el valor de z con el valor maximo actual
                            zmax = z;
                        } 
                    }
                }
            }
        }


    // Crear un nuevo objeto para la caja envolvente global
    Mesh cajaEnvolvente;
    std::string nuevoNombre = "env_global";
    cajaEnvolvente.fijarNombreObjeto(nuevoNombre);

    std::vector<Vertex> vertexsAux;
    vertexsAux.reserve(8);
    Vertex v1, v2, v3, v4, v5, v6, v7, v8;
    //Primer vertex
    v1.fijarX(static_cast<unsigned int>(xmin));
    std::cout<<"________________________________________";
    std::cout << "\n| Vertex 1:[ x = " << v1.obtenerX() << ", y = "; 
    v1.fijarY(static_cast<unsigned int>(ymin));
    std::cout<< v1.obtenerY() << ", " << "z = ";; 
    v1.fijarZ(static_cast<unsigned int>(zmin));
    std::cout << v1.obtenerZ() << "] " << "v1 |"<<std::endl; 
    v1.fijarIndiceVer(0);//v1
    vertexsAux.push_back(v1);
    //--------------------------------------------
    //Segundo vertex
    v2.fijarX(static_cast<unsigned int>(xmax));
    std::cout << "| Vertex 2:[ x = " << v2.obtenerX() << ", " << "y = "; 
    v2.fijarY(static_cast<unsigned int>(ymin));
    std::cout << v2.obtenerY() << ", " << "z = "; 
    v2.fijarZ(static_cast<unsigned int>(zmin));
    std::cout  << v2.obtenerZ() << "] " << "v2 |"<<std::endl; 
    v2.fijarIndiceVer(1);//v2
    vertexsAux.push_back(v2);
    //--------------------------------------------
    //Tercer vertex
    v3.fijarX(static_cast<unsigned int>(xmax));
    std::cout << "| Vertex 3:[ x = " << v3.obtenerX() << ", " <<"y= ";
    v3.fijarY(static_cast<unsigned int>(ymax));
    std::cout << v3.obtenerY() << ", " << "z= ";
    v3.fijarZ(static_cast<unsigned int>(zmin));
    std::cout << v3.obtenerZ() << "] " << " v3 |"<<std::endl;
    v3.fijarIndiceVer(2);//v3
    vertexsAux.push_back(v3);
    //--------------------------------------------
    //Cuarto vertex
    v4.fijarX(static_cast<unsigned int>(xmin));
    std::cout << "| Vertex 4:[ x = " << v4.obtenerX() << ", " <<"y = ";
    v4.fijarY(static_cast<unsigned int>(ymax));
    std::cout << v4.obtenerY() << ", " << "z= ";
    v4.fijarZ(static_cast<unsigned int>(zmin)); 
    std::cout << v4.obtenerZ() << "] " << " v4 |"<<std::endl;
    v4.fijarIndiceVer(3);//v4
    vertexsAux.push_back(v4);
    //--------------------------------------------
    //Quinto vertex
    v5.fijarX(static_cast<unsigned int>(xmin));
    std::cout << "| Vertex 5:[ x = " << v5.obtenerX() << ", " <<"y = ";
    v5.fijarY(static_cast<unsigned int>(ymin));
    std::cout << v5.obtenerY() << ", " << "z = ";
    v5.fijarZ(static_cast<unsigned int>(zmax));
    std::cout << v5.obtenerZ() << "] " << " v5 |"<<std::endl;
    v5.fijarIndiceVer(4);//v5
    vertexsAux.push_back(v5);
    //--------------------------------------------
    //Sexto vertex
    v6.fijarX(static_cast<unsigned int>(xmax));
    std::cout << "| Vertex 6:[ x = " << v6.obtenerX() << ", " <<"y = ";
    v6.fijarY(static_cast<unsigned int>(ymin));
    std::cout << v6.obtenerY() << ", " << " z = ";
    v6.fijarZ(static_cast<unsigned int>(zmax));
    std::cout << v6.obtenerZ() << "] " << " v6 |"<<std::endl;
    v6.fijarIndiceVer(5);//v6
    vertexsAux.push_back(v6);
    //--------------------------------------------
    //Septimo vertex
    v7.fijarX(static_cast<unsigned int>(xmax));
    std::cout << "| Vertex 7:[ x = " << v7.obtenerX() << ", " <<"y = ";
    v7.fijarY(static_cast<unsigned int>(ymax)); 
    std::cout << v7.obtenerY() << ", " << "z = ";
    v7.fijarZ(static_cast<unsigned int>(zmax));
    std::cout << v7.obtenerZ() << "] " << " v7 |"<<std::endl;
    v7.fijarIndiceVer(6);//v7
    vertexsAux.push_back(v7);
    //--------------------------------------------
    //Octavo vertex
    v8.fijarX(static_cast<unsigned int>(xmin));
    std::cout << "| Vertex 8:[ x = " << v8.obtenerX() << ", " <<" y = ";
    v8.fijarY(static_cast<unsigned int>(ymax));
    std::cout << v8.obtenerY() << ", " << "z = ";
    v8.fijarZ(static_cast<unsigned int>(zmax));
    std::cout << v8.obtenerZ() << "] " << " v8 |"<<std::endl;
    std::cout<<"________________________________________"<<std::endl;
    v8.fijarIndiceVer(7);//v8
    vertexsAux.push_back(v8);
    //--------------------------------------------
    std::vector<unsigned int> indices;
        indices.reserve(6); // Reservar espacio para evitar realineaciones innecesarias

        std::cout << std::endl;

        // Recorre los primeros 6 elementos o el tamaño de vertexsAux si es menor
        for (size_t i = 0; i < std::min<size_t>(6, vertexsAux.size()); ++i) {
            unsigned int indice = vertexsAux[i].obtenerIndiceVer();

            if (indice < vertexsAux.size()) {
                indices.push_back(indice);
                std::cout << "Se ha ingresado el índice " << indice << " a la cara" << std::endl;
            } else {
                std::cerr << "Índice de vértice fuera de rango: " << indice << std::endl;
                std::cout << "No se ha agregado ninguna cara tras este mensaje" << std::endl;
                return; // Salir de la función en caso de error
            }

            // Se encuentra el -1 o la lista está vacía, se acaba el ciclo
            if (indices.empty() || indices[0] == static_cast<unsigned int>(-1)) {
                return;
            }
        }

        // Se crea una cara temporal para ir asignándole los vértices
        Face cara;
        cara.fijarCantidadVerticesCar(indices.size() / 2);

        std::list<Arista> aristas;
        std::cout << std::endl;

        // Se crean aristas tomando las posiciones de dos en dos
        for (size_t i = 0; i + 1 < indices.size(); i += 2) {
            unsigned int indiceInicio = indices[i];
            unsigned int indiceFin = indices[i + 1];

            // No se crean aristas si se encuentran con el mismo vértice según el índice
            if (indiceInicio != indiceFin) {
                Arista arista;
                arista.fijarIndiceAr(i / 2);
                arista.agregarVertice(vertexsAux[indiceInicio]);
                arista.agregarVertice(vertexsAux[indiceFin]);

                aristas.push_back(arista);

                std::cout << "\nSe ha ingresado: " << std::endl;
                arista.imprimirArista();
            }
        }

        // Se terminan de asignar los datos a la cara del objeto
        static int indiceCara = 0; // Variable estática para mantener el índice entre llamadas
        cara.fijarIndiceCar(indiceCara++);
        cara.fijarListaAristas(aristas);
        cajaEnvolvente.agregarCara(cara);
    
    // Agregar la caja envolvente a la lista de objetos en memoria
    objetosPrograma.push_back(cajaEnvolvente);

    std::cout << "\n(Resultado exitoso) La caja envolvente de los objetos en memoria se ha generado con el nombre " << nuevoNombre << " y se ha agregado a los objetos en memoria." << std::endl;
 
}

void descargar(std::string nombreObjeto, std::list<Mesh>& listadoObjetos) {
    std::list<Mesh>::iterator iteradorBorrar;
    std::list<Mesh>::iterator iteradorBorrar2;
    iteradorBorrar = listadoObjetos.begin();
        
    bool confirmacion=false;

    for (; iteradorBorrar != listadoObjetos.end();) {
            
        if (iteradorBorrar->obtenerNombreObjeto() == nombreObjeto) {
                
            iteradorBorrar = listadoObjetos.erase(iteradorBorrar);
            std::cout<<"El objeto "<<nombreObjeto<<" ha sido eliminado de la memoria de trabajo"<<std::endl;
            confirmacion = true; 
            break; 
        } else {
            iteradorBorrar++;
        }
    }

    if (confirmacion==false) {
        std::cout<<"El objeto "<<nombreObjeto<<" no ha sido cargado en memoria"<<std::endl;
    }

}

void salir(){
    std::cout<<"\t\t\t\t\t\t\t¡Gracias por usar nuestro programa!";
    exit(0);                                 
}

void imprimirListado(std::list<Mesh>& listadoObjetos){
}

Mesh encontrarObjeto(std::string nombreObjeto, std::list<Mesh>& listadoObjetos) {
     // Recorrer la lista usando un iterador
    for (auto it = listadoObjetos.begin(); it != listadoObjetos.end(); ++it) {
        if (it->obtenerNombreObjeto() == nombreObjeto) {
            return *it;
        }
    }
    // Retornar un objeto vacío si no se encuentra el objeto buscado
    return Mesh();
}

void guardar(std::string nombreObjeto, std::string nombreArchivo, std::list<Mesh>& listadoObjetos){
    std::ofstream archivo(nombreArchivo.c_str());

    if(!archivo.is_open()){
      std::cout<<"El archivo no se pudo abrir";
        
    }else{
        std::list<Mesh>::iterator itGuardar;
        itGuardar = listadoObjetos.begin();
        bool confirmacion=false;
        Mesh objetoAux;

        for(;itGuardar!=listadoObjetos.end(); itGuardar++){
            if(nombreObjeto == itGuardar->obtenerNombreObjeto()){
                objetoAux = *(itGuardar);
                confirmacion=true;
                break;
            }

        }

        if(confirmacion==true){

            //Se escribe el nombre del objeto
            archivo<<objetoAux.obtenerNombreObjeto()<<std::endl;

            //Se escribe el número de vertexs dentro del archivo
            archivo<<objetoAux.obtenerCantidadVerticesObj()<<std::endl;

            std::list<Face> listaCarasObjetos = objetoAux.obtenerCaras();
            std::list<Face>::iterator itCara = listaCarasObjetos.begin();
            std::vector<Vertex> listaVertexsAux;
            
            //Iterar sobre cada cara
            for (; itCara != listaCarasObjetos.end(); itCara++) {

                //Obtener las aristas de la cara
                std::list<Arista> listaAristasCaras = itCara->obtenerListaAristas();
                std::list<Arista>::iterator itAris = listaAristasCaras.begin();

                //Iterar sobre cada arista
                for (; itAris!=listaAristasCaras.end(); itAris++){

                    //Obtener los vértices de la arista
                    std::list<Vertex> listaVertexsAristas = itAris->obtenerListaVertices();
                    std::list<Vertex>::iterator itVer = listaVertexsAristas.begin();

                    //Iterar sobre cada vértice
                    for (; itVer != listaVertexsAristas.end(); itVer++) {

                        //Verificar si el vértice ya está en la lista auxiliar
                        bool vertexYaGuardado = false;
                        for (Vertex& vertex : listaVertexsAux) {
                            if (vertex.obtenerIndiceVer() == itVer->obtenerIndiceVer()) {
                                vertexYaGuardado = true;
                                break;
                            }
                        }

                        //Si el vértice no ha sido guardado, se agrega a la lista y se guarda en el archivo
                        if (!vertexYaGuardado) {
                            listaVertexsAux.push_back(*itVer);
                            archivo<<itVer->obtenerX()<<" "<<itVer->obtenerY()<<" "<<itVer->obtenerZ()<<std::endl;
                        }
                    }
                }
            }

            //Escribir las caras con los índices de los vértices correspondientes
            itCara = listaCarasObjetos.begin();
            for (; itCara != listaCarasObjetos.end(); itCara++) {

                std::list<Arista> listaAristasCaras = itCara->obtenerListaAristas();
                std::list<Arista>::iterator itAris = listaAristasCaras.begin();

                std::vector<unsigned int> indicesCaras;

                //Iterar sobre las aristas de la cara
                for (; itAris != listaAristasCaras.end(); itAris++) {
                    std::list<Vertex> listaVertexsAristas = itAris->obtenerListaVertices();
                    std::list<Vertex>::iterator itVer = listaVertexsAristas.begin();

                    //Escribir los índices de los vértices de la cara
                    for (; itVer != listaVertexsAristas.end(); itVer++) {
                        indicesCaras.push_back(itVer->obtenerIndiceVer());
                    }
                }

                std::vector<unsigned int>::iterator itIndex;
                itIndex = indicesCaras.begin();
                
                for (; itIndex != indicesCaras.end(); itIndex++) {
                    archivo<<*(itIndex)<<" ";
                }
                archivo<<std::endl;
            }

            //Se pone el -1 al final del objeto
            archivo << -1 << std::endl;
            std::cout<<"La informacion del objeto "<<nombreObjeto<<" ha sido guardada exitosamente en el archivo "<<nombreArchivo;
            archivo.close();
        }else{
            std::cout<<"El objeto "<<nombreObjeto<<" se encuentra en memoria";
        }
            
    }
      archivo.close();
}

void lecturaArchivos(std::string nombreArchivo, std::list<Mesh>& listadoObjetos){
    std::ifstream archivo("puntos.txt");
    bool confirmacionObjeto = verificacionObjetos(nombreArchivo,listadoObjetos);
    bool existenciaObjeto=false;

    if(!archivo.is_open()){
      std::cout<<"El archivo "<<nombreArchivo<< " no existe o es ilegible"<<std::endl;
      archivo.close();
    }else{
        std::string linea;
        while (std::getline(archivo, linea)) {
            Mesh objetoAux;
            bool existenciaObjeto = false;

            // SE OBTIENE EL NOMBRE DEL OBJETO
            objetoAux.fijarNombreObjeto(linea);
            std::cout << "Se ha obtenido el nombre del objeto: " << objetoAux.obtenerNombreObjeto() << std::endl;

            // Verificar si el objeto ya existe en memoria
            for (auto& obj : listadoObjetos) {
                if (objetoAux.obtenerNombreObjeto() == obj.obtenerNombreObjeto()) {
                    existenciaObjeto = true;
                    break;
                }
            }

            if (existenciaObjeto) {
                std::cout << "El objeto ya existe en memoria" << std::endl;
                continue; // Saltar al siguiente objeto si ya existe
            }

            // Leer la cantidad de vértices
            int n = 0;
            if (std::getline(archivo, linea)) {
                std::istringstream texto(linea);
                texto >> n;
                objetoAux.fijarCantidadVerticesObj(n);
                std::cout << "Se ha obtenido el número de vértices del objeto: " << n << std::endl;
            }

            // Leer los vértices
            std::vector<Vertex> vertexAux;
            vertexAux.reserve(n);
            for (int i = 0; i < n; ++i) {
                if (std::getline(archivo, linea)) {
                    std::istringstream texto(linea);
                    unsigned int x, y, z;
                    texto >> x >> y >> z;

                    Vertex vertex;
                    vertex.fijarX(x);
                    vertex.fijarY(y);
                    vertex.fijarZ(z);
                    vertex.fijarIndiceVer(i);

                    vertexAux.push_back(vertex);
                }
            }

            // IMPRESIÓN DE PRUEBA SI SE ESTÁN GUARDANDO CORRECTAMENTE LOS VÉRTICES
            for (auto& vertice : vertexAux) {
                std::cout << "Index vertex: " << vertice.obtenerIndiceVer() << std::endl;
                std::cout << "X:" << vertice.obtenerX() << " Y:" << vertice.obtenerY() << " Z:" << vertice.obtenerZ() << std::endl;
            }

            // Leer las caras
            int indiceCara = 0;
            while (std::getline(archivo, linea)) {
                std::istringstream iss(linea);
                std::vector<unsigned int> indices;
                int indice;

                while (iss >> indice) {
                    if (indice == -1) {
                        break;  // Detener si se encuentra el -1, fin de la figura actual
                    }

                    if (indice < vertexAux.size()) {
                        indices.push_back(indice);
                        std::cout << "Se ha ingresado el índice " << indice << " a la cara" << std::endl;
                    } else {
                        std::cerr << "Índice de vértice fuera de rango: " << indice << std::endl;
                    }
                }

                if (indices.empty() || indices[0] == -1) {
                    break;  // Final de la lista de caras, pasar a la siguiente figura
                }

                Face cara;
                cara.fijarCantidadVerticesCar(indices.size() / 2);

                std::list<Arista> aristas;
                for (size_t i = 0; i + 1 < indices.size(); i += 2) {
                    unsigned int indiceInicio = indices[i];
                    unsigned int indiceFin = indices[i + 1];

                    if (indiceInicio != indiceFin) {
                        Arista arista;
                        arista.fijarIndiceAr(i);
                        arista.agregarVertice(vertexAux[indiceInicio]);
                        arista.agregarVertice(vertexAux[indiceFin]);

                        aristas.push_back(arista);

                        std::cout << "Se ha ingresado la arista" << std::endl;
                        arista.imprimirArista();
                    }
                }

                cara.fijarIndiceCar(indiceCara);
                cara.fijarListaAristas(aristas);
                objetoAux.agregarCara(cara);

                indiceCara++;
            }

            // Agregar el objeto a la lista de objetos en memoria
            listadoObjetos.push_back(objetoAux);
            std::cout << "El objeto " << objetoAux.obtenerNombreObjeto() << " ha sido cargado exitosamente desde el archivo " 
                    << nombreArchivo << std::endl;

            // Continuar con la siguiente figura si encuentra -1
            if (linea == "-1") {
                continue;  // Se pasa al siguiente objeto en el archivo
            }
        }
    }

    archivo.close();
}

bool verificacionObjetos(std::string nombreArchivo, std::list<Mesh>& listadoObjetos){

    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cout<< "El archivo "<<nombreArchivo <<"no se pudo abrir (Desde verificación objeto)."<<std::endl;
        return false;
    }

    std::string linea;

    if (!std::getline(archivo, linea)) {
        std::cout<<"El archivo está vacio."<<std::endl;
        return false;
    }
      
    if (linea.find(' ') != std::string::npos) {
        std::cout<<"El nombre del objeto tiene espacio, hacer cambios necesarios: Eliminar espacios. "<<std::endl;
        return false;
    }

      //Revisar que está el número de vertexs
    if (!std::getline(archivo, linea)) {
        std::cout<<"No existe el número de vertexs, hacer cambios necesarios: Agregar vertexs. "<<std::endl;
        return false;
    }

    //Se revisa que realmente se esté ingrensando un número de vertexs
    //que sea un entero positivo y que sea un número 
    int numVertexs;
    std::istringstream entrada(linea);
    if (!(entrada>>numVertexs) || numVertexs<=0) {
        std::cout<<"El número de vertexs no es un número o no es una entrada válida"<<std::endl;
        return false;
    }

    //Se valida que existan siempre las 3 coordenadas insertadas en los vertexs
    for (int i=0; i<numVertexs; i++) {
        if (!std::getline(archivo, linea)){
            //Se revisa primero que en la siguiente línea hayan vertexs
            std::cout<<"No hay vertexs en el archivo"<<std::endl;
            return false;
        }

        //Se va tomando cada línea y verificando que se encuentren todas las coordenadas
        std::istringstream lineaVertexs(linea);
        int x, y, z;
        if (!(lineaVertexs>>x>>y>>z)) {
            std::cout<<"Error: El renglón "<<i+3<<" no se tienen las coordenadas necesarias"<<std::endl;
            return false;
        }
    }

      //Se activa un booleando que nos indica si el
      //archivo termina en menos -1
        bool hayMenos1 = false;
        while(std::getline(archivo, linea)){
            //Nos vamos a la línea final en donde se toma el valor
            std::istringstream lineaFinal(linea);
            int valor;
            //En caso de que la línea sea de menos 1, se activa el booleano
            if(lineaFinal>>valor && valor==-1) {
               hayMenos1 = true;
               break;
            }
        }

    if (hayMenos1==false) {
        std::cout<<"El archivo no termina en -1"<<std::endl;
        return false;
    }

    std::cout<<"Los datos del objeto son válidos"<<std::endl;
    return true;

}

void v_cercano_nombre_objeto(int px, int py, int pz, std::string nombreObjeto, std::list<Mesh>& objetosPrograma) {
    // Buscar el objeto en memoria
    Mesh objetoEnMemoria;
    bool objetoEncontrado = false;
    for (auto it = objetosPrograma.begin(); it != objetosPrograma.end(); ++it) {
        if (it->obtenerNombreObjeto() == nombreObjeto) {
            objetoEnMemoria = *it;
            objetoEncontrado = true;
            break;
        }
    }

    // Verificar si el objeto fue encontrado
    if (!objetoEncontrado) {
        std::cout << "(Objeto no existe) El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    // Obtener los vértices del objeto para construir el KDTree
    std::list<Face> caras = objetoEnMemoria.obtenerCaras();
    std::list<Vertex> vertices;

    for (auto itCara = caras.begin(); itCara != caras.end(); ++itCara) {
        std::list<Arista> aristas = itCara->obtenerListaAristas();
        for (auto itArista = aristas.begin(); itArista != aristas.end(); ++itArista) {
            std::list<Vertex> verticesArista = itArista->obtenerListaVertices();
            vertices.insert(vertices.end(), verticesArista.begin(), verticesArista.end());
        }
    }

    // Construir el KDTree con los vértices del objeto
    KDTree kdtree;
    kdtree.construir(vertices);

    // Crear un vértice con las coordenadas dadas por el usuario
    Vertex punto(px, py, pz);

    // Buscar el vértice más cercano en el KDTree
    Vertex verticeMasCercano = kdtree.buscarVecinoMasCercano(punto);

    // Calcular la distancia entre el vértice más cercano y el punto dado
    float dx = static_cast<float>(verticeMasCercano.obtenerX() - px);
    float dy = static_cast<float>(verticeMasCercano.obtenerY() - py);
    float dz = static_cast<float>(verticeMasCercano.obtenerZ() - pz);
    float distancia = std::sqrt(dx * dx + dy * dy + dz * dz);

    // Imprimir el resultado
    std::cout << "(Resultado exitoso) El vértice " << verticeMasCercano.obtenerIndiceVer() << " (" 
              << verticeMasCercano.obtenerX() << ", " << verticeMasCercano.obtenerY() << ", " 
              << verticeMasCercano.obtenerZ() << ") del objeto " << nombreObjeto
              << " es el más cercano al punto (" << px << ", " << py << ", " << pz << "), a una distancia de " 
              << distancia << "." << std::endl;
}

void v_cercano(int px, int py, int pz,std::list<Mesh>& objetosPrograma) {
    // Verificar si hay objetos en memoria
    if (objetosPrograma.empty()) {
        std::cout << "(Memoria vacía) Ningún objeto ha sido cargado en memoria." << std::endl;
        return;
    }

    // Construir el KDTree con todos los vértices de todos los objetos
    std::list<Vertex> todosVertices;

    for (auto itObj = objetosPrograma.begin(); itObj != objetosPrograma.end(); ++itObj) {
        std::list<Face> caras = itObj->obtenerCaras();
        for (auto itCara = caras.begin(); itCara != caras.end(); ++itCara) {
            std::list<Arista> aristas = itCara->obtenerListaAristas();
            for (auto itArista = aristas.begin(); itArista != aristas.end(); ++itArista) {
                std::list<Vertex> vertices = itArista->obtenerListaVertices();
                todosVertices.insert(todosVertices.end(), vertices.begin(), vertices.end());
            }
        }
    }

    // Verificar que haya vértices cargados
    if (todosVertices.empty()) {
        std::cout << "(Memoria vacía) Ningún vértice ha sido cargado en memoria." << std::endl;
        return;
    }

    // Construir el KDTree
    KDTree kdtree;
    kdtree.construir(todosVertices);

    // Crear el punto de búsqueda (px, py, pz)
    Vertex punto(px, py, pz);

    // Buscar el vértice más cercano usando el KDTree
    Vertex verticeMasCercano = kdtree.buscarVecinoMasCercano(punto);

    // Calcular la distancia entre el vértice más cercano y el punto (px, py, pz)
    int dx = static_cast<int>(verticeMasCercano.obtenerX() - px);
    int dy = static_cast<int>(verticeMasCercano.obtenerY() - py);
    int dz = static_cast<int>(verticeMasCercano.obtenerZ() - pz);
    int distancia = std::sqrt(dx * dx + dy * dy + dz * dz);

    // Mostrar el resultado
    std::cout << "(Resultado exitoso) El vértice " << verticeMasCercano.obtenerIndiceVer() 
              << " (" << verticeMasCercano.obtenerX() << ", " << verticeMasCercano.obtenerY() 
              << ", " << verticeMasCercano.obtenerZ() << ") es el más cercano al punto ("
              << px << ", " << py << ", " << pz << "), a una distancia de " 
              << distancia << std::endl;
}

void v_cercanos_caja(std::string nombre_objeto,std::list<Mesh>& objetosPrograma) {
    // Buscar el objeto en la lista
    Mesh objetoEnMemoria;
    bool objetoEncontrado = false;

    for (auto it = objetosPrograma.begin(); it != objetosPrograma.end(); ++it) {
        if (it->obtenerNombreObjeto() == nombre_objeto) {
            objetoEnMemoria = *it;
            objetoEncontrado = true;
            break;
        }
    }

    // Verificar si el objeto fue encontrado
    if (!objetoEncontrado) {
        std::cout << "(Objeto no existe) El objeto " << nombre_objeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    // Obtener la caja envolvente del objeto
    float xmin = std::numeric_limits<float>::max();
    float xmax = -std::numeric_limits<float>::max();
    float ymin = std::numeric_limits<float>::max();
    float ymax = -std::numeric_limits<float>::max();
    float zmin = std::numeric_limits<float>::max();
    float zmax = -std::numeric_limits<float>::max();

    std::list<Face> caras = objetoEnMemoria.obtenerCaras();
    for (auto itCara = caras.begin(); itCara != caras.end(); ++itCara) {
        std::list<Arista> aristas = itCara->obtenerListaAristas();
        for (auto itArista = aristas.begin(); itArista != aristas.end(); ++itArista) {
            std::list<Vertex> vertices = itArista->obtenerListaVertices();
            for (auto itVertex = vertices.begin(); itVertex != vertices.end(); ++itVertex) {
                float x = static_cast<float>(itVertex->obtenerX());
                float y = static_cast<float>(itVertex->obtenerY());
                float z = static_cast<float>(itVertex->obtenerZ());

                xmin = std::min(xmin, x);
                xmax = std::max(xmax, x);
                ymin = std::min(ymin, y);
                ymax = std::max(ymax, y);
                zmin = std::min(zmin, z);
                zmax = std::max(zmax, z);
            }
        }
    }

    // Definir las 8 esquinas de la caja envolvente
    std::vector<Vertex> esquinas(8);
    esquinas[0] = Vertex(xmin, ymin, zmin);
    esquinas[1] = Vertex(xmax, ymin, zmin);
    esquinas[2] = Vertex(xmax, ymax, zmin);
    esquinas[3] = Vertex(xmin, ymax, zmin);
    esquinas[4] = Vertex(xmin, ymin, zmax);
    esquinas[5] = Vertex(xmax, ymin, zmax);
    esquinas[6] = Vertex(xmax, ymax, zmax);
    esquinas[7] = Vertex(xmin, ymax, zmax);

    // Construir el KDTree con los vértices del objeto
    std::list<Vertex> todosVertices;
    for (auto itCara = caras.begin(); itCara != caras.end(); ++itCara) {
        std::list<Arista> aristas = itCara->obtenerListaAristas();
        for (auto itArista = aristas.begin(); itArista != aristas.end(); ++itArista) {
            std::list<Vertex> vertices = itArista->obtenerListaVertices();
            todosVertices.insert(todosVertices.end(), vertices.begin(), vertices.end());
        }
    }

    // Construir el KDTree
    KDTree kdtree;
    kdtree.construir(todosVertices);

    // Buscar los vértices más cercanos a las esquinas de la caja envolvente
    std::vector<Vertex> verticesCercanos(8);
    std::vector<float> distancias(8);
    
    for (int i = 0; i < 8; ++i) {
        verticesCercanos[i] = kdtree.buscarVecinoMasCercano(esquinas[i]);
        distancias[i] = distanciaEuclidiana(esquinas[i], verticesCercanos[i]);
    }

    // Mostrar el resultado en formato de tabla
    std::cout << "(Resultado exitoso) Los vértices del objeto " << nombre_objeto 
              << " más cercanos a las esquinas de su caja envolvente son:\n";
    std::cout << "Esquina \t | Vértice \t\t\t\t | Distancia\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << i+1 << " (" << esquinas[i].obtenerX() << ", " 
                  << esquinas[i].obtenerY() << ", " << esquinas[i].obtenerZ() << ")"
                  << "\t | " << verticesCercanos[i].obtenerIndiceVer() 
                  << " (" << verticesCercanos[i].obtenerX() << ", " 
                  << verticesCercanos[i].obtenerY() << ", " 
                  << verticesCercanos[i].obtenerZ() << ")\t | " 
                  << distancias[i] << std::endl;
    }
}

//Ayuda:
void ayuda(std::string comando) {
    if (comando == "cargar") {
        std::cout << "El comando cargar permite cargar un archivo en memoria.\n";
    }
    // Agregar más comandos y sus descripciones aquí.
}

void ruta_corta_centro(int id, std::string nombreObjeto, std::list<Mesh>& objetosPrograma ){
    // Buscar el objeto en memoria
    Mesh objeto = encontrarObjeto(nombreObjeto, objetosPrograma);
    if (objeto.obtenerNombreObjeto().empty()) {
        std::cout << "(Objeto no existe) El objeto " << nombreObjeto << " no ha sido cargado en memoria." << std::endl;
    } else {
        // Crear el grafo desde el objeto
        Grafo grafo = crearGrafoDesdeObjeto(objeto);
        grafo.rutaCortaCentro(id, nombreObjeto);
    }    
}

// campos: IdTratamiento;Nombre;Descripcion;Costo

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_tratamientos.h"

//constructor
ArbolTratamiento::ArbolTratamiento()
{
    raiz = nullptr;
}

//destructor
ArbolTratamiento::~ArbolTratamiento()
{
    LiberarMemoria(raiz);
}

//metodos privados

void ArbolTratamiento::InsertarRN(pTrata nuevo)
{
    //insercion normal de arbol binario de busqueda -sin balancear todavia
    // entes de llamar esto ya se reviso q el id no exista, entonces aca no hay iguales
    pTrata actual = raiz;
    pTrata papa = nullptr;

    while (actual != nullptr) {
        papa = actual;
        if (nuevo->idTratamiento < actual->idTratamiento)
            actual = actual->Hizq;
        else
            actual = actual->Hder;
    }

    nuevo->padre = papa;

    if (papa == nullptr) {
        raiz = nuevo;
    }
    else if (nuevo->idTratamiento < papa->idTratamiento) {
        papa->Hizq = nuevo;
    }
    else {
        papa->Hder = nuevo;
    }
}

void ArbolTratamiento::ArreglaInsercion(pTrata nodo)
{
    //mientras el padre sea rojo hay 2 rojos seguidos, o sea q se rompe una regla

    while (nodo != raiz and nodo->padre != nullptr and nodo->padre->color == true) {
        pTrata papa = nodo->padre;
        pTrata abuelo = papa->padre;

        if (abuelo == nullptr) break; //el padre es la raiz (y la raiz es negra, no deberia pasar)

        pTrata tio;
        bool papaEsIzquierdo;

        if (abuelo->Hizq == papa) {
            papaEsIzquierdo = true;
            tio = abuelo->Hder;
        }
        else {
            papaEsIzquierdo = false;
            tio = abuelo->Hizq;
        }

        if (tio != nullptr and tio->color == true) {
            //Caso 1: tio rojo -> solo se recolorea y se sigue subiendo con el abuelo
            papa->color = false;
            tio->color = false;
            abuelo->color = true;
            nodo = abuelo;
        }
        else {
            // tio negro (o null) -> hay que rotar
            if (papaEsIzquierdo) {
                if (nodo == papa->Hder) {
                    //Caso 2:nodo es hijo derecho -> rotar izq en el padre para volverlo caso 3
                    nodo = papa;
                    RotIzquierda(nodo);
                    papa = nodo->padre;
                    abuelo = papa->padre;
                }
                //Caso 3: rotar derecha en el abuelo
                papa->color = false;
                abuelo->color = true;
                RotDerecha(abuelo);
            }
            else {
                if (nodo == papa->Hizq) {
                    //Caso 2 espejo
                    nodo = papa;
                    RotDerecha(nodo);
                    papa = nodo->padre;
                    abuelo = papa->padre;
                }
                // Caso 3 espejo: rotar izquierda en el abuelo
                papa->color = false;
                abuelo->color = true;
                RotIzquierda(abuelo);
            }
            break;
        }
    }

    raiz->color = false; //la raiz siempre negra
}

void ArbolTratamiento::RotIzquierda(pTrata nodo)
{
    pTrata hijoDer = nodo->Hder;
    nodo->Hder = hijoDer->Hizq;

    if (hijoDer->Hizq != nullptr)
        hijoDer->Hizq->padre = nodo;

    hijoDer->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoDer;
    else if (nodo == nodo->padre->Hizq)
        nodo->padre->Hizq = hijoDer;
    else
        nodo->padre->Hder = hijoDer;

    hijoDer->Hizq = nodo;
    nodo->padre = hijoDer;
}

void ArbolTratamiento::RotDerecha(pTrata nodo)
{
    pTrata hijoIzq = nodo->Hizq;
    nodo->Hizq = hijoIzq->Hder;

    if (hijoIzq->Hder != nullptr)
        hijoIzq->Hder->padre = nodo;

    hijoIzq->padre = nodo->padre;

    if (nodo->padre == nullptr)
        raiz = hijoIzq;
    else if (nodo == nodo->padre->Hder)
        nodo->padre->Hder = hijoIzq;
    else
        nodo->padre->Hizq = hijoIzq;

    hijoIzq->Hder = nodo;
    nodo->padre = hijoIzq;
}

pTrata ArbolTratamiento::Buscarvalor(pTrata r, int id)
{
    if (r == nullptr) {
        return nullptr;
    }

    if (id == r->idTratamiento) {
        return r;
    }
    else if (id < r->idTratamiento) {
        return Buscarvalor(r->Hizq, id);
    }
    else {
        return Buscarvalor(r->Hder, id);
    }
}

void ArbolTratamiento::LiberarMemoria(pTrata r)
{
    if (r == nullptr) return;
    LiberarMemoria(r->Hizq);
    LiberarMemoria(r->Hder);
    delete r;
}

// Metodos publicos

bool ArbolTratamiento::InsertaNodo(int id, string nom, string desc, double cost)
{
    if (Buscarvalor(raiz, id) != nullptr) {
        return false; //ya existe, no se crea el nodo
    }

    pTrata nuevo = new NodoTrata(id, nom, desc, cost);
    InsertarRN(nuevo);
    ArreglaInsercion(nuevo);
    return true;
}

pTrata ArbolTratamiento::Buscarvalor(int id)
{
    return Buscarvalor(raiz, id);
}

void ArbolTratamiento::InsertarTratamiento(int id, string nom, string desc, double cost)
{
    if (InsertaNodo(id, nom, desc, cost)) {
        cout << "Tratamiento de nombre: " << nom << " con codigo: " << id << " insertado correctamente" << endl;
    }
    else {
        cout << "No se pudo insertar el tratamiento ya que ya existe un tratamiento de codigo: " << id << endl;
    }
}

void ArbolTratamiento::leerArchivo(const char* nombreArchivo)
{
    cout << "------------------ chunches tratamientos" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string idtrata, nombre, descripcion, costo;
    string filaencabezado;

    getline(archivo, filaencabezado); //el encabezado no se borra del archivo

    while (getline(archivo, idtrata, ';')) {
        getline(archivo, nombre, ';');
        getline(archivo, descripcion, ';');
        getline(archivo, costo); //el ultimo campo de la fila no lleva delimitnte
        int idtrataint = stoi(idtrata);
        double costodouble = stod(costo);
        InsertarTratamiento(idtrataint, nombre, descripcion, costodouble);
    }
    archivo.close();
}

void ArbolTratamiento::BuscarMostrar(int id)
{
    pTrata nodoesta = Buscarvalor(id);

    if (nodoesta != nullptr) {
        cout << "Tratamiento encontrado" << endl;
        cout << "Id de tratamiento: " << nodoesta->idTratamiento << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
        cout << "Descripcion: " << nodoesta->descripcion << endl;
        cout << "Costo: " << nodoesta->costo << endl;
    }
    else {
        cout << "No existe ningun tratamiento de codigo: " << id << endl;
    }
}

void ArbolTratamiento::ModificarTratamiento(int id, string nuevoNombre, string nuevaDesc, double nuevoCosto) {
    pTrata nodoesta = Buscarvalor(id);
    if (nodoesta == nullptr) {
        cout << "No existe ningun tratamiento de codigo: " << id << endl;
    }
    else {
        nodoesta->nombre = nuevoNombre;
        nodoesta->descripcion = nuevaDesc;
        nodoesta->costo = nuevoCosto;
        cout << "Tratamiento de codigo " << id << " modificado, ahora es: " << nodoesta->nombre << " | " << nodoesta->descripcion << " | costo " << nodoesta->costo << endl;
        // le puse esas | en el cout pq sino se hacia un desmadre

    }
}

void ArbolTratamiento::InordenReportesTrata(pTrata r, reportes& rep, int anchos[]) {
    if (r == nullptr) {
        return;
    }
    InordenReportesTrata(r->Hizq, rep, anchos);
    string textos[] = { to_string(r->idTratamiento), r->nombre, r->descripcion, to_string(r->costo) };
    rep.escribirFilaDinamica(4, textos, anchos);
    InordenReportesTrata(r->Hder, rep, anchos);
}
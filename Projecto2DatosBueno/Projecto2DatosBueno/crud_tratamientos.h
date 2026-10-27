#ifndef CRUD_TRATAMIENTOS_H
#define CRUD_TRATAMIENTOS_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "reportes.h"

//arbol Rojo-Negro  arbol binario de busqueda balanceado donde cada nodo tiene un color

class NodoTrata {
    int idTratamiento;
    string nombre;
    string descripcion;
    double costo;
    bool color; //true = rojo, false = negro
    NodoTrata* padre;
    NodoTrata* Hizq;
    NodoTrata* Hder;

public:
    NodoTrata(int id, string nom, string desc, double cost) {
        idTratamiento = id;
        nombre = nom;
        descripcion = desc;
        costo = cost;
        color = true; //nodo nuevo es rojo
        padre = nullptr;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolTratamiento;
};
typedef NodoTrata* pTrata;

class ArbolTratamiento {
    friend class reportes;
private:
    pTrata raiz;

    void InsertarRN(pTrata nuevo);
    void ArreglaInsercion(pTrata nodo);
    void RotIzquierda(pTrata x);
    void RotDerecha(pTrata x);
    pTrata Buscarvalor(pTrata r, int id);
    void LiberarMemoria(pTrata r);

public:
    ArbolTratamiento();
    ~ArbolTratamiento();

    bool InsertaNodo(int id, string nom, string desc, double cost);
    pTrata Buscarvalor(int id);

    void InsertarTratamiento(int id, string nom, string desc, double cost);
    void leerArchivo(const char* nombreArchivo);
    void BuscarMostrar(int id);
    void ModificarTratamiento(int id, string nuevoNombre, string nuevaDesc, double nuevoCosto);
    void InordenReportesTrata(pTrata r, reportes& rep, int anchos[]);
};

#endif
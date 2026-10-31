#ifndef CRUD_ESPECIALIDADES_H
#define CRUD_ESPECIALIDADES_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "reportes.h"
//Arbol AA, arbol binario de busqueda balanceado.
//cambiamos factor de balance del AVL, cada nodo tiene un "nivel"
//nodo nuevo nace con nivel 1, y el balanceo se hace con operaciones Skew y Split

class NodoEsp {
    int idEspecialidad;
    string nombre;
    string descripcion;
    int nivel;
    NodoEsp* Hizq;
    NodoEsp* Hder;

public:
    NodoEsp(int id, string nom, string desc) {
        idEspecialidad = id;
        nombre = nom;
        descripcion = desc;
        nivel = 1;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolEspecialidad;
};
typedef NodoEsp* pEsp;

class ArbolEspecialidad {
    friend class reportes;
private:
    pEsp raiz;

    void Skew(pEsp& r);
    void Split(pEsp& r);
    void InsertaAA(pEsp& r, int id, string nom, string desc, bool& insertado);
    pEsp Buscarvalor(pEsp r, int id);
    void destruirArbol(pEsp r);

public:
    ArbolEspecialidad();
    ~ArbolEspecialidad();

    bool InsertaNodo(int id, string nom, string desc);
    pEsp Buscarvalor(int id); // lo usa Medicos para validar que la especialidad exista

    void InsertarEspecialidad(int id, string nom, string desc);
    void leerArchivo(const char* nombreArchivo);
    void BuscarMostrar(int id);
    void ModificarEspecialidad(int id, string nuevaDesc);
    void InordenReportesEsp(pEsp r, reportes& rep, int anchos[]);
};

#endif
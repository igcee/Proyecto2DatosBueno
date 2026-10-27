#ifndef CRUD_DIAGNOSTICO_H
#define CRUD_DIAGNOSTICO_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "reportes.h"

//arbol AA, arbol binario de busqueda balanceado

class NodoDiag {
    string idDiagnostico;
    string nombre;
    string descripcion;
    int nivel;
    NodoDiag* Hizq;
    NodoDiag* Hder;

public:
    NodoDiag(string id, string nom, string desc) {
        idDiagnostico = id;
        nombre = nom;
        descripcion = desc;
        nivel = 1;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolDiagnostico;
};
typedef NodoDiag* pDiag;

class ArbolDiagnostico {
    friend class reportes;
private:
    pDiag raiz;

    void Skew(pDiag& r);
    void Split(pDiag& r);
    void InsertaAA(pDiag& r, string id, string nom, string desc, bool& insertado);
    pDiag Buscarvalor(pDiag r, string id);
    void destruirArbol(pDiag r);

public:
    ArbolDiagnostico();
    ~ArbolDiagnostico();

    bool InsertaNodo(string id, string nom, string desc);
    pDiag Buscarvalor(string id); //para validar que el diagnostico exista (lo van a ocupar otros modulos)

    void InsertarDiagnostico(string id, string nom, string desc);
    void leerArchivo(const char* nombreArchivo);
    void BuscarMostrar(string id);
    void ModificarDiag(string id, string nuevaDesc);
    void InordenReportesDiag(pDiag r, reportes& rep, int anchos[]);
};

#endif
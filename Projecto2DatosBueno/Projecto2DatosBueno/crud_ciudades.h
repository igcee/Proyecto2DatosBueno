#ifndef CRUD_CIUDADES_H
#define CRUD_CIUDADES_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_paises.h" // para validar q pais exista

class NodoCiudad {
    int codCiudad;
    int codPais;
    string nombre;
    NodoCiudad* Hizq;
    NodoCiudad* Hder;


public:
    NodoCiudad(int codp, int codc,string nom) {
        codPais = codp;
        codCiudad = codc;
        nombre = nom;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolCiudad;
};
typedef NodoCiudad* pCiudad;

class ArbolCiudad { 
    friend class reportes;

private:
    pCiudad raiz;
    void destruirArbol(pCiudad raiz);

    pCiudad InsertaBinario(pCiudad raiz, int codp, int codc, string nom, bool& insertado);
    pCiudad Buscarvalor(pCiudad raiz, int codp, int codc);

public:
    ArbolCiudad();
    ~ArbolCiudad();

    bool InsertaNodo(int codp, int codc, string nom);
    pCiudad Buscarvalor(int codp, int codc);

    int Comp(int codp1, int codc1, int codp2, int codc2);
    void InsertarCiudad(int codp, int codc, string nom, ArbolPais& paises); 
    void leerArchivo(const char* nombreArchivo, ArbolPais& paises);
    void BuscarMostrar(int codp, int codc, ArbolPais& paises);
    // Ciudades necesita validar q codigo de pais exista antes de insertar o buscar, se pasa como parametro x referencia
    void ModificarCiudad(int codp, int codc, string nom, ArbolPais& paises);
    void InordenReportesCiudad(pCiudad r, reportes& rep, int anchos[], int codPaisFiltro);
};
#endif

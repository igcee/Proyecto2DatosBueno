#ifndef CRUD_HABITACIONES_H
#define CRUD_HABITACIONES_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "reportes.h"

class NodoHab{
	int idHabitacion;
	int numero;
	string piso;
	int tipo;
	int estado;
    int FB;
	NodoHab* Hizq;
    NodoHab* Hder;

public:
    NodoHab(int idhab, int num, string p, int t, int est) {
        idHabitacion = idhab;
        numero = num;
        piso = p;
        tipo = t;
        estado = est;
        FB = 0;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolHabitaciones;
};

typedef NodoHab* pHab;

class ArbolHabitaciones {
    friend class reportes;
private:
    pHab raiz;


    void InsertarBalanceado(pHab& r, bool& Hh, int id, int num, string pis, int tip, int est);
    void RotacionSimpleIzquierda(pHab& n, pHab& n1);
    void RotacionSimpleDerecha(pHab& n, pHab& n1);
    void RotacionDobleIzquierda(pHab& n, pHab& n1);
    void RotacionDobleDerecha(pHab& n, pHab& n1);
    pHab Buscarvalor(pHab r, int id);
    void InordenR(pHab r);
    void MostrarNodo(pHab n);
    void LiberarMemoria(pHab r);

public:

    ArbolHabitaciones();
    ~ArbolHabitaciones();

    bool InsertaNodo(int id, int num, string pis, int tip, int est);
    pHab Buscarvalor(int id);

    void InordenR();
    void InsertarHabitacion(int id, int num, string pis, int tip, int est);
    void leerArchivo(const char* nombreArchivo);
    void BuscarMostrar(int id);
    void ModificarHab(int id, int estado);
    void InordenReportesHab(pHab r, reportes& rep, int anchos[], int est);


};


#endif
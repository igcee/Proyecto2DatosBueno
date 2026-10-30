#ifndef CRUD_CITAS_H
#define CRUD_CITAS_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_medicos.h"
#include "crud_pacientes.h"
#include "reportes.h"


class NodoCita {
    int idCita;
    int idPaciente;
    int idMedico;
    int idEspecialidad;
    string fecha;
    string hora;
    string motivo;
    int estado;
    int FB;
    NodoCita* Hizq;
    NodoCita* Hder;

public:
    NodoCita(int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est) {
        idCita = idc;
        idPaciente = idp;
        idMedico = idm;
        idEspecialidad = idesp;
        fecha = fch;
        hora = hra;
        motivo = mtivo;
        estado = est;
        FB = 0;
        Hizq = nullptr;
        Hder = nullptr;
    }
    friend class ArbolCitas;
    friend class reportes;
};

typedef NodoCita* pCita;

class ArbolCitas {
    friend class reportes;
private:
    pCita raiz;


    void InsertarBalanceado(pCita& r, bool& Hh, int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est);
    void RotacionSimpleIzquierda(pCita& n, pCita& n1);
    void RotacionSimpleDerecha(pCita& n, pCita& n1);
    void RotacionDobleIzquierda(pCita& n, pCita& n1);
    void RotacionDobleDerecha(pCita& n, pCita& n1);
    pCita Buscarvalor(pCita r, int id);
    void LiberarMemoria(pCita r);

public:

    ArbolCitas();
    ~ArbolCitas();

    bool InsertaNodo(int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est);
    pCita Buscarvalor(int id);

    void InsertarCita(int idc, int idp, int idm, int idesp, string fch, string hra, string mtivo, int est, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    void leerArchivo(const char* nombreArchivo, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    void BuscarMostrar(int idp, int idm, int id, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    void ModificarCita(int idp, int idm, int idc, string motivo, int estado, ArbolPacientes& pacientes, ArbolMedicos& medicos);
    void InordenReportesCitasPorPaciente(pCita r, reportes& rep, int anchos[], int IdPacFiltro);
    void InordenReportesCitasPorMedico(pCita r, reportes& rep, int anchos[], int idMedFiltro);

};


#endif

#ifndef CRUD_PACIENTES_H
#define CRUD_PACIENTES_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_ciudades.h" //para validar q la ciudad exista
#include "reportes.h"
#include "crud_paises.h"
//Arbol B

const int MAXPAC = 4;
const int MINPAC = 2;

class NodoPaciente { //es el dato (la clave) q se guarda dentro de las paginas
    int idPaciente;
    string nombre;
    string fechaNacimiento;
    string telefono;
    int codPais;
    int codCiudad;
    string correo;

public:
    NodoPaciente() {
        idPaciente = 0;
        codPais = 0;
        codCiudad = 0;
    }
    NodoPaciente(int id, string nom, string fecha, string tel, int codp, int codc, string cor) {
        idPaciente = id;
        nombre = nom;
        fechaNacimiento = fecha;
        telefono = tel;
        codPais = codp;
        codCiudad = codc;
        correo = cor;
    }
    friend class ArbolPacientes;
};
typedef NodoPaciente* pPaciente;

class PaginaPaciente { //es el nodo del arbol B
    int cuenta;
    NodoPaciente claves[MAXPAC + 1];
    PaginaPaciente* ramas[MAXPAC + 1];

public:
    PaginaPaciente() {
        cuenta = 0;
        for (int i = 0; i <= MAXPAC; i++) {
            ramas[i] = nullptr;
        }
    }
    friend class ArbolPacientes;
};
typedef PaginaPaciente* pPagPac;

class ArbolPacientes {
    friend class reportes;
private:
    pPagPac raiz;

    void Insertar(NodoPaciente cl);
    void Empujar(pPagPac actual, NodoPaciente cl, bool& subeArriba, NodoPaciente& mediana, pPagPac& nuevo);
    bool BuscarNodo(pPagPac actual, int id, int& k);
    void MeterHoja(pPagPac actual, NodoPaciente cl, pPagPac rd, int k);
    void DividirNodo(pPagPac actual, NodoPaciente cl, pPagPac rd, int k, NodoPaciente& mediana, pPagPac& nuevo);
    pPaciente Buscarvalor(pPagPac r, int id);
    void destruirArbol(pPagPac r);

public:
    ArbolPacientes();
    ~ArbolPacientes();

    bool InsertaNodo(int id, string nom, string fecha, string tel, int codp, int codc, string cor);
    pPaciente Buscarvalor(int id); //lo usa Hospitalizaciones (y Citas) para validar que el paciente exista

    void InsertarPaciente(int id, string nombre, string fecha, string telefono, string correo, int codpais, int codciudad, ArbolCiudad& ciudades);
    void leerArchivo(const char* nombreArchivo, ArbolCiudad& ciudades);
    void BuscarMostrar(int codpais, int codciudad, int id, ArbolCiudad& ciudades);
    void ModificarPaciente(int codpais, int codciudad, int id, string telefono, string correo, ArbolCiudad& ciudades);
    //Pacientes necesita validar q la ciudad exista, se pasa como parametro x referencia
    void InordenReportesPacientes(pPagPac r, reportes& rep, int anchos[]);
    void InordenReportesPacientesPorPais(pPagPac r, reportes& rep, int anchos[], int codPais);

};
#endif
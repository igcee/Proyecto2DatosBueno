//archivo de especialidades.
//arbol AA y el archivo es especialidades.csv
//campo IdEspecialidad;Nombre;Descripcion

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_especialidades.h"
#include "reportes.h"

// Constructor
ArbolEspecialidad::ArbolEspecialidad()
{
    raiz = nullptr;
}

//destructor
ArbolEspecialidad::~ArbolEspecialidad()
{
    destruirArbol(raiz);
}

//metodos privados

void ArbolEspecialidad::Skew(pEsp& r)
{
    //skew =rotacion simple a la derecha, pero solo cuando hay un "enlace horizontal izquierdo"
    //osea cuando el hijo izquierdo tien mismo nivel que su padre
    if (r == nullptr || r->Hizq == nullptr) return;

    if (r->Hizq->nivel == r->nivel) {
        pEsp izq = r->Hizq;
        r->Hizq = izq->Hder;
        izq->Hder = r;
        r = izq; //el hijo izq sube y pasa a ser la nueva raiz de este subarbol
    }
}

void ArbolEspecialidad::Split(pEsp& r)
{
    //split= rotacion simple a la izquierda, pero solo cuando hay 2 enlaces horizontales derechos seguidos
    //  cuando el nieto derecho tiene el MISMO nivel que el abuelo
    if (r == nullptr || r->Hder == nullptr || r->Hder->Hder == nullptr) return;

    if (r->nivel == r->Hder->Hder->nivel) {
        pEsp der = r->Hder;
        r->Hder = der->Hizq;
        der->Hizq = r;
        r = der;     //el hijo der sube
        r->nivel++;  //nivel aumenta en 1
    }
}

void ArbolEspecialidad::InsertaAA(pEsp& r, int id, string nom, string desc, bool& insertado)
{
    if (r == nullptr) {
        r = new NodoEsp(id, nom, desc);
        insertado = true;
        return;
    }

    if (id < r->idEspecialidad) {
        InsertaAA(r->Hizq, id, nom, desc, insertado);
    }
    else if (id > r->idEspecialidad) {
        InsertaAA(r->Hder, id, nom, desc, insertado);
    }
    else {
        return; // ya existe, insertado se queda en false y no hay nada q rebalancear
    }

    //de regreso de la recursion se arregla el balance, siempre en este orden   primero Skew y luego Split
    Skew(r);
    Split(r);
}

pEsp ArbolEspecialidad::Buscarvalor(pEsp r, int id)
{
    if (r == nullptr) {
        return nullptr;
    }

    if (id == r->idEspecialidad) {
        return r;
    }
    else if (id < r->idEspecialidad) {
        return Buscarvalor(r->Hizq, id);
    }
    else {
        return Buscarvalor(r->Hder, id);
    }
}

void ArbolEspecialidad::destruirArbol(pEsp r)
{
    if (r == nullptr) return;
    destruirArbol(r->Hizq);
    destruirArbol(r->Hder);
    delete r;
}

//metodos publicos

bool ArbolEspecialidad::InsertaNodo(int id, string nom, string desc)
{
    bool insertado = false;
    InsertaAA(raiz, id, nom, desc, insertado);
    return insertado;
}

pEsp ArbolEspecialidad::Buscarvalor(int id)
{
    return Buscarvalor(raiz, id);
}

void ArbolEspecialidad::InsertarEspecialidad(int id, string nom, string desc)
{
    if (InsertaNodo(id, nom, desc)) {
        cout << "Especialidad de nombre: " << nom << " con codigo: " << id << " insertada correctamente" << endl;
    }
    else {
        cout << "No se pudo insertar la especialidad ya que ya existe una especialidad de codigo: " << id << endl;
    }
}

void ArbolEspecialidad::leerArchivo(const char* nombreArchivo)
{
    cout << "------------------ chunches especialidades" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string idesp, nombre, descripcion;
    string filaencabezado;

    getline(archivo, filaencabezado); //el encabezado no se borra del archivo, solo se salta al leer

    while (getline(archivo, idesp, ';')) {
        getline(archivo, nombre, ';');
        getline(archivo, descripcion); //el ultimo campo de la fila no lleva delimitnte
        int idespint = stoi(idesp);
        InsertarEspecialidad(idespint, nombre, descripcion);
    }
    archivo.close();
}

void ArbolEspecialidad::BuscarMostrar(int id)
{
    pEsp nodoesta = Buscarvalor(id);

    if (nodoesta != nullptr) {
        cout << "Especialidad encontrada" << endl;
        cout << "Id de especialidad: " << nodoesta->idEspecialidad << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
        cout << "Descripcion: " << nodoesta->descripcion << endl;
    }
    else {
        cout << "No existe ninguna especialidad de codigo: " << id << endl;
    }
}

void ArbolEspecialidad::ModificarEspecialidad(int id, string nuevaDesc) {
    pEsp nodoesta = Buscarvalor(id);
    if (nodoesta == nullptr) {
        cout << "No existe ninguna especialidad de codigo: " << id << endl;
    }
    else {
        nodoesta->descripcion = nuevaDesc;
        cout << "Especialidad de codigo " << id << " modificada, nueva descripcion: " << nuevaDesc << endl;
    }
}

void ArbolEspecialidad::InordenReportesEsp(pEsp r, reportes& rep, int anchos[]) {
    if (r == nullptr) {
        return;
    }
    InordenReportesEsp(r->Hizq, rep, anchos);
    string textos[] = { to_string(r->idEspecialidad), r->nombre, r->descripcion };
    rep.escribirFilaDinamica(3, textos, anchos);
    InordenReportesEsp(r->Hder, rep, anchos);
}
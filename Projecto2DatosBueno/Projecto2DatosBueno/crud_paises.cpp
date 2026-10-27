// chunches del archivo de paises.
// es arbol binario de busqueda, y el archivo es Paises.csv

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_paises.h"
// Constructor
ArbolPais::ArbolPais()
{
    raiz = nullptr;
}

// Destructor
ArbolPais::~ArbolPais()
{
    destruirArbol(raiz);
}

// Metodos publicos

bool ArbolPais::InsertaNodo(int cod, string nom)
{   
    bool insertado = false;
    raiz = InsertaBinario(raiz, cod, nom, insertado);
    return insertado;
}

pPais ArbolPais::Buscarvalor(int cod)
{
    return Buscarvalor(raiz, cod);
}

// Metodos privados

pPais ArbolPais::InsertaBinario(pPais raiz, int cod, string nom, bool &insertado)
{
    if (raiz == nullptr)
    {   
        insertado = true;
        return new NodoPais(cod, nom);
    }

    if (cod < raiz->codPais)
    {
        raiz->Hizq = InsertaBinario(raiz->Hizq, cod, nom, insertado);
    }
    else
        if (cod > raiz->codPais)
        {
            raiz->Hder = InsertaBinario(raiz->Hder, cod, nom, insertado);
        }
    // si igual no pasa nada, insertado se queda en false
    return raiz;
}

pPais ArbolPais::Buscarvalor(pPais raiz, int cod)
{
    if (raiz == nullptr) return nullptr;
    else if (cod == raiz->codPais) return raiz;
    else if (cod < raiz->codPais)
        return Buscarvalor(raiz->Hizq, cod);
    else
        return Buscarvalor(raiz->Hder, cod);
}


void ArbolPais::destruirArbol(pPais raiz)
{
    if (raiz == nullptr) return;
    destruirArbol(raiz->Hizq);
    destruirArbol(raiz->Hder);
    delete raiz;
}

void ArbolPais::InsertarPais(int cod, string nom) {
    if (InsertaNodo(cod, nom))
        cout << "Pais de nombre: " << nom << " con codigo: " << cod <<" insertado correctamente" << endl;
    else {
        cout << "No se pudo insertar el pais o este ya existe " << endl;
    }
}

void ArbolPais::leerArchivo(const char* nombreArchivo) {
    cout << "------------------ chunches paises" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pude abrir el archivo " << nombreArchivo << endl;
        return;
    }
    string codigo; // aunque en los nodos el codigo es un int, el getline lee strings, por lo q hay que convertir string codigo a un int dsps
    int codigoint;
    string nombre;
    string filaencabezado;

    getline(archivo, filaencabezado);

    while (getline(archivo, codigo, ';')) { // el delimitante tenia q usar '', no "" pq este espera un char, no un string
        getline(archivo, nombre);
        codigoint = stoi(codigo);
        InsertarPais(codigoint, nombre);
    }
    archivo.close();
}

void ArbolPais::BuscarMostrar(int cod) {
    pPais nodoesta = Buscarvalor(cod);
    if (nodoesta != nullptr) {
        cout << "Pais encontrado" << endl;
        cout << "Codigo: " << nodoesta->codPais << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
    }
    else {
        cout << "No se pudo encontrar ese pais" << endl;
    }
}

void ArbolPais::ModificarPais(int cod, string nuevoNom) {
    pPais nodoesta = Buscarvalor(cod);
    if (nodoesta == nullptr) {
        cout << "No se pudo realizar esa modificacion ya que el pais de codigo " << cod << " no existe" << endl;
    }

    else {
        cout << "Pais de codigo " << cod << " modificado, antes se llamaba " << nodoesta->nombre << ", ahora se llama " << nuevoNom << endl;
        nodoesta->nombre = nuevoNom;
        
    }
}

void ArbolPais::InordenReportesPais(pPais raiz, reportes& rep, int anchos[]) {
    if (raiz == nullptr) {
        return;
    }
    else {
        InordenReportesPais(raiz->Hizq, rep, anchos);
        string textos[] = { to_string(raiz->codPais), raiz->nombre }; // el to_string es lo mismo que stoi, pero al reves. Se ocupa hacer ya que el arreglos de textos es string, por lo q no deja meterle un int
        rep.escribirFilaDinamica(2, textos, anchos);
        InordenReportesPais(raiz->Hder, rep, anchos);
    }

}
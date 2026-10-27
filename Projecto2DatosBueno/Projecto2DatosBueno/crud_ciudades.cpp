// chunches del archivo de ciudades.
// es arbol binario de busqueda, y el archivo es Ciudades.csv
// mucho se recicla del archivo de paises, pq es mismo arbol

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_ciudades.h"
#include "crud_paises.h" // validar codigo pais existe
// Constructor

int ArbolCiudad::Comp(int codp1, int codc1, int codp2, int codc2){
    // para decidir si ir por Hizq o Hder en el arbol.
    // primero revisa codigos de paises, codp1 es el nodo actual y codp2 es del nodo q se quiere insertar
    // si codp2 > codp1, se va para Hder, si < se va para Hizq
    // si codp2 = codp1, se hace la misma comparacion pero con codc2 y codc1
    // 1 es der y -1 es izq
    if (codp2 > codp1) {
        return 1;
    }
    else if (codp2 < codp1) {
        return -1;
    }
    else {
        if (codc2 > codc1) {
            return 1;
        }
        else if (codc2 < codc1) {
            return -1;
        }
        else {
            return 0; // x codp2 == codp1 y codc2 == codc1. osea q ya existe

        }

    }
}



ArbolCiudad::ArbolCiudad()
{
    raiz = nullptr;
}

// Destructor
ArbolCiudad::~ArbolCiudad()
{
    destruirArbol(raiz);
}

// Metodos publicos

bool ArbolCiudad::InsertaNodo(int codp, int codc, string nom)
{
    bool insertado = false;
    raiz = InsertaBinario(raiz, codp, codc, nom, insertado);
    return insertado;
}

pCiudad ArbolCiudad::Buscarvalor(int codp, int codc)
{
    return Buscarvalor(raiz, codp, codc);
}


// Metodos privados

pCiudad ArbolCiudad::InsertaBinario(pCiudad raiz, int codp, int codc, string nom, bool& insertado)
{
    

    if (raiz == nullptr)
    {
        insertado = true;
        return new NodoCiudad(codp, codc, nom);
    }

    int direccion = Comp(raiz->codPais, raiz->codCiudad, codp, codc); // -1 izq, 1 der

    if (direccion < 0) // si -1, izq
    {
        raiz->Hizq = InsertaBinario(raiz->Hizq, codp, codc, nom, insertado);
    }
    else
        if (direccion > 0)
        {
            raiz->Hder = InsertaBinario(raiz->Hder, codp, codc, nom, insertado);
        }
    // si igual no pasa nada, insertado se queda en false
    return raiz;
}

pCiudad ArbolCiudad::Buscarvalor(pCiudad raiz, int codp, int codc)
{
    
    if (raiz == nullptr) {
        return nullptr;
    }
    
    int direccion = Comp(raiz->codPais, raiz->codCiudad, codp, codc); // esto aca y no arriba, para no pase de q se busca cuando raiz == nullptr

    if (direccion == 0){
        return raiz;
    }
    else if (direccion < 0){
        return Buscarvalor(raiz->Hizq, codp, codc);
    }
    else { // osea dir > 0
        return Buscarvalor(raiz->Hder, codp, codc);
    }

}


void ArbolCiudad::destruirArbol(pCiudad raiz)
{
    if (raiz == nullptr) return;
    destruirArbol(raiz->Hizq);
    destruirArbol(raiz->Hder);
    delete raiz;
}



void ArbolCiudad::InsertarCiudad(int codp, int codc, string nom, ArbolPais& paises){

    if (paises.Buscarvalor(codp) == nullptr){ // antes q nada hay q ver si el codigo de pais existe USANDO METODO DE crud_paises
        cout << " No existe ningun pais de codigo: " << codp << endl;
    }


    else if (InsertaNodo(codp, codc, nom)){
        cout << "Ciudad de nombre: " << nom << " con codigo: " << codc << " con codigo de pais: " << codp << " insertado correctamente" << endl;
    }
    else{
        cout << "No se pudo insertar la ciudad ya que ya existe una ciudad de codigo: " << codc << " en el pais de codigo : "<< codp  << endl;
    }
}

void ArbolCiudad::leerArchivo(const char* nombreArchivo, ArbolPais& paises){
    cout << "------------------ chunches ciudades" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false){
        cout << "No se pude abrir el archivo " << nombreArchivo << endl;
        return;
    }
    string codpais, codciudad;
    int codigopaisint, codigociudadint;
    string nombre;
    string filaencabezado;

    getline(archivo, filaencabezado);

    while (getline(archivo, codpais, ';')) { // el delimitante tenia q usar '', no "" pq este espera un char, no un string
        getline(archivo, codciudad, ';'); // aca tambien poner delimitante
        getline(archivo, nombre); // el unico q no ocupa q se le ponga el delimitante es al ultimo de la fila, que para al toparse CRLF
        codigopaisint = stoi(codpais);
        codigociudadint = stoi(codciudad);
        InsertarCiudad(codigopaisint, codigociudadint,nombre, paises);
    }
    archivo.close();
}

void ArbolCiudad::BuscarMostrar(int codp, int codc, ArbolPais& paises){
    pCiudad nodoesta = Buscarvalor(codp, codc);

    if (paises.Buscarvalor(codp) == nullptr) { // primero se valida q el pais exista
        cout << "No existe ningun pais de codigo: " << codp << endl;
        return;
    }
    else if (nodoesta != nullptr){
        cout << "Ciudad encontrada" << endl;
        cout << "Codigo de pais: " << nodoesta->codPais << endl;
        cout << "Codigo de ciudad: " << nodoesta->codCiudad << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
    }
    else{
        cout << "No se pudo encontrar esa ciudad" << endl;
    }
}

void ArbolCiudad::ModificarCiudad(int codp, int codc, string nuevoNom, ArbolPais& paises){
    if (paises.Buscarvalor(codp) == nullptr) { // si codigo pais no existe mandar error
        cout << "No se pudo realizar esa modificacion ya que el pais de codigo " << codp << " no existe" << endl;
        return;
    }

    pCiudad nodoesta = Buscarvalor(codp, codc);

    if (nodoesta == nullptr){
        cout << "No se pudo realizar esa modificacion ya que la ciudad de codigo " << codc << " no existe en el pais de codigo "<< codp << endl;
    }

    else{
        cout << "Ciudad de codigo " << codc << " en pais de codigo "<< codp << " modificada, antes se llamaba " << nodoesta->nombre << ", ahora se llama " << nuevoNom << endl;
        nodoesta->nombre = nuevoNom;
    }

}

void ArbolCiudad::InordenReportesCiudad(pCiudad r, reportes& rep, int anchos[], int codPaisFiltro){
    // para recorrer todo el arbol de ciudades, inorden (r -> izq -> der)
    // ocupa recibir la raiz (q se convierte en Hizq/Hder), referencia al chunche de reportes, el arreglo conteniendo los anchos de cada columna (recordar q debian de sumar 520 para q quede bien)
    // y para este caso, recibe codPaisFiltro, que seria para solo poner en los reportes las ciudades que tengan codPais coincidiendo con este
    if (r == nullptr){
        return;
    }
    InordenReportesCiudad(r->Hizq, rep, anchos, codPaisFiltro);
    if (r->codPais == codPaisFiltro) { // añade en el reporte solo si se cumple que codPais de la ciudad == codPaisFiltro.
        string textos[] = {to_string(r->codCiudad), r->nombre}; // el to_string es lo mismo q stoi pero al reves, convierte de int a string. Se ocupa pq el arreglo de textos es de tipo string, x lo q no aceptaria codPais tal cual x ser int
        rep.escribirFilaDinamica(2, textos, anchos); // escribe en el reporte 2 columnas, conteniendo lo que esta en textos para su respectivo indice, y de tamaño dependiendo de lo que esta en anchos, tambien a su respectivo indice
    }
    InordenReportesCiudad(r->Hder, rep, anchos, codPaisFiltro);
}
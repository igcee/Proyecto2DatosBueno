//archivo de pacientes.
//es arbol B, y el archivo es Pacientes.csv
//campos: Idpaciente;Nombre;Fechanacimiento;Telefono;CodPais;CodCiudad;Correo

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "crud_pacientes.h"
#include "crud_ciudades.h" //validar q la ciudad existe
#include "reportes.h"

//Constructor
ArbolPacientes::ArbolPacientes()
{
    raiz = nullptr;
}

//Destructor
ArbolPacientes::~ArbolPacientes()
{
    destruirArbol(raiz);
}

//Metodos privados

bool ArbolPacientes::BuscarNodo(pPagPac actual, int id, int& k)
{
    //busca el id dentro de UNA pagina. devuelve true si esta, y en k queda la posicion
    //si no esta, k es la rama por la q hay q bajar (0 si es menor q todas las claves)
    if (id < actual->claves[1].idPaciente) {
        k = 0;
        return false;
    }
    k = actual->cuenta;
    while (id < actual->claves[k].idPaciente && k > 1) {
        k--;
    }
    return id == actual->claves[k].idPaciente;
}

void ArbolPacientes::MeterHoja(pPagPac actual, NodoPaciente cl, pPagPac rd, int k)
{
    //mete la clave cl (y su rama derecha rd) en la posicion k+1 de la pagina, corriendo las demas a la derecha
    //se llama solo cuando la pagina tiene espacio
    for (int i = actual->cuenta; i >= k + 1; i--) {
        actual->claves[i + 1] = actual->claves[i];
        actual->ramas[i + 1] = actual->ramas[i];
    }
    actual->claves[k + 1] = cl;
    actual->ramas[k + 1] = rd;
    actual->cuenta++;
}

void ArbolPacientes::DividirNodo(pPagPac actual, NodoPaciente cl, pPagPac rd, int k, NodoPaciente& mediana, pPagPac& nuevo)
{
    //la pagina esta llena (4 claves) y hay q meter una mas: se parte en 2 y la clave del medio sube
    //posMdna es la posicion de la clave q va a subir, depende de donde cae la clave nueva
    int posMdna;
    if (k <= MINPAC) {
        posMdna = MINPAC;
    }
    else {
        posMdna = MINPAC + 1;
    }

    nuevo = new PaginaPaciente();

    //lo q esta a la derecha de la mediana se pasa a la pagina nueva
    for (int i = posMdna + 1; i <= MAXPAC; i++) {
        nuevo->claves[i - posMdna] = actual->claves[i];
        nuevo->ramas[i - posMdna] = actual->ramas[i];
    }
    nuevo->cuenta = MAXPAC - posMdna;
    actual->cuenta = posMdna;

    //se mete la clave nueva en la pagina q le toca
    if (k <= MINPAC) {
        MeterHoja(actual, cl, rd, k);
    }
    else {
        MeterHoja(nuevo, cl, rd, k - posMdna);
    }

    //la clave del final de la pagina izquierda es la mediana, esa sube
    mediana = actual->claves[actual->cuenta];
    nuevo->ramas[0] = actual->ramas[actual->cuenta];
    actual->cuenta--;
}

void ArbolPacientes::Empujar(pPagPac actual, NodoPaciente cl, bool& subeArriba, NodoPaciente& mediana, pPagPac& nuevo)
{
    if (actual == nullptr) {
        //se llego a un lugar vacio: la clave "sube" para q la meta el nivel de arriba
        subeArriba = true;
        mediana = cl;
        nuevo = nullptr;
    }
    else {
        int k;
        bool esta = BuscarNodo(actual, cl.idPaciente, k);

        if (esta) {
            //repetido aca no deberia llegar porq antes se revisa con Buscarvalor
            subeArriba = false;
            return;
        }

        Empujar(actual->ramas[k], cl, subeArriba, mediana, nuevo);

        if (subeArriba) {
            if (actual->cuenta < MAXPAC) {
                //hay espacio en la pagina, se mete y listo
                subeArriba = false;
                MeterHoja(actual, mediana, nuevo, k);
            }
            else {
                //pagina llena, se divide y sigue subiendo la mediana
                subeArriba = true;
                DividirNodo(actual, mediana, nuevo, k, mediana, nuevo);
            }
        }
    }
}

void ArbolPacientes::Insertar(NodoPaciente cl)
{
    bool subeArriba;
    NodoPaciente mediana;
    pPagPac nuevo;

    Empujar(raiz, cl, subeArriba, mediana, nuevo);

    if (subeArriba) {
        //se dividio hasta la raiz: se crea una raiz nueva y el arbol crece un nivel
        pPagPac p = new PaginaPaciente();
        p->cuenta = 1;
        p->claves[1] = mediana;
        p->ramas[0] = raiz;
        p->ramas[1] = nuevo;
        raiz = p;
    }
}

pPaciente ArbolPacientes::Buscarvalor(pPagPac r, int id)
{
    if (r == nullptr) {
        return nullptr;
    }

    int k;
    if (BuscarNodo(r, id, k)) {
        return &(r->claves[k]);
    }
    return Buscarvalor(r->ramas[k], id);
}

void ArbolPacientes::destruirArbol(pPagPac r)
{
    if (r == nullptr) return;
    for (int i = 0; i <= r->cuenta; i++) {
        destruirArbol(r->ramas[i]);
    }
    delete r;
}

//Metodos publicos

bool ArbolPacientes::InsertaNodo(int id, string nom, string fecha, string tel, int codp, int codc, string cor)
{
    if (Buscarvalor(raiz, id) != nullptr) {
        return false; // ya existe
    }
    Insertar(NodoPaciente(id, nom, fecha, tel, codp, codc, cor));
    return true;
}

pPaciente ArbolPacientes::Buscarvalor(int id)
{
    return Buscarvalor(raiz, id);
}

void ArbolPacientes::InsertarPaciente(int id, string nombre, string fecha, string telefono, string correo, int codpais, int codciudad, ArbolCiudad& ciudades)
{
    if (ciudades.Buscarvalor(codpais, codciudad) == nullptr) { //antes q nada hay q ver q la ciudad exista USANDO METODO DE crud_ciudades
        cout << "No existe ninguna ciudad de codigo: " << codciudad << " en el pais de codigo: " << codpais << endl;
    }
    else if (InsertaNodo(id, nombre, fecha, telefono, codpais, codciudad, correo)) {
        cout << "Paciente de nombre: " << nombre << " con id: " << id << " insertado correctamente" << endl;
    }
    else {
        cout << "No se pudo insertar el paciente ya que ya existe un paciente de id: " << id << endl;
    }
}

void ArbolPacientes::leerArchivo(const char* nombreArchivo, ArbolCiudad& ciudades)
{
    cout << "------------------ chunches pacientes" << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open() == false) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string idpaciente, nombre, fecha, telefono, codpais, codciudad, correo;
    string filaencabezado;

    getline(archivo, filaencabezado); //el encabezado no se borra del archivo, solo se salta al leer

    while (getline(archivo, idpaciente, ';')) {
        getline(archivo, nombre, ';');
        getline(archivo, fecha, ';');
        getline(archivo, telefono, ';');
        getline(archivo, codpais, ';');
        getline(archivo, codciudad, ';');
        getline(archivo, correo); //el ultimo campo de la fila no lleva delimitante
        int idint = stoi(idpaciente);
        int codpaisint = stoi(codpais);
        int codciudadint = stoi(codciudad);
        //en el archivo el correo va al final, pero InsertarPaciente lo recibe antes del pais y la ciudad
        InsertarPaciente(idint, nombre, fecha, telefono, correo, codpaisint, codciudadint, ciudades);
    }
    archivo.close();
}

void ArbolPacientes::BuscarMostrar(int codpais, int codciudad, int id, ArbolCiudad& ciudades)
{
    if (ciudades.Buscarvalor(codpais, codciudad) == nullptr) { //primero se valida q la ciudad exista
        cout << "No existe ninguna ciudad de codigo: " << codciudad << " en el pais de codigo: " << codpais << endl;
        return;
    }

    pPaciente nodoesta = Buscarvalor(id);

    if (nodoesta == nullptr) {
        cout << "No existe ningun paciente de id: " << id << endl;
    }
    else if (nodoesta->codPais != codpais || nodoesta->codCiudad != codciudad) { //el paciente tiene q ser de ESA ciudad
        cout << "El paciente de id: " << id << " existe, pero no pertenece a esa ciudad" << endl;
    }
    else {
        cout << "Paciente encontrado" << endl;
        cout << "Id de paciente: " << nodoesta->idPaciente << endl;
        cout << "Nombre: " << nodoesta->nombre << endl;
        cout << "Fecha de nacimiento: " << nodoesta->fechaNacimiento << endl;
        cout << "Telefono: " << nodoesta->telefono << endl;
        cout << "Codigo de pais: " << nodoesta->codPais << endl;
        cout << "Codigo de ciudad: " << nodoesta->codCiudad << endl;
        cout << "Correo: " << nodoesta->correo << endl;
    }
}

void ArbolPacientes::ModificarPaciente(int codpais, int codciudad, int id, string telefono, string correo, ArbolCiudad& ciudades)
{
    if (ciudades.Buscarvalor(codpais, codciudad) == nullptr) {
        cout << "No existe ninguna ciudad de codigo: " << codciudad << " en el pais de codigo: " << codpais << endl;
        return;
    }

    pPaciente nodoesta = Buscarvalor(id);

    if (nodoesta == nullptr) {
        cout << "No existe ningun paciente de id: " << id << endl;
    }
    else if (nodoesta->codPais != codpais || nodoesta->codCiudad != codciudad) {
        cout << "El paciente de id: " << id << " existe, pero no pertenece a esa ciudad" << endl;
    }
    else {
        nodoesta->telefono = telefono;
        nodoesta->correo = correo;
        cout << "Paciente de id: " << id << " modificado correctamente" << endl;
    }
}

void ArbolPacientes::InordenReportesPacientes(pPagPac r, reportes& rep, int anchos[]) {
    if (r == nullptr) {
        return;
    }
    InordenReportesPacientes(r->ramas[0], rep, anchos);
    for (int i = 1; i <= r->cuenta;i++) {
        string textos[] = { to_string(r->claves[i].idPaciente), r->claves[i].nombre, r->claves[i].fechaNacimiento,  r->claves[i].telefono, to_string(r->claves[i].codPais), to_string(r->claves[i].codCiudad),r->claves[i].correo};
        rep.escribirFilaDinamica(7, textos, anchos);
        InordenReportesPacientes(r->ramas[i], rep, anchos);
    }
}

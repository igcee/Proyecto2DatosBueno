#define _CRT_SECURE_NO_WARNINGS
// ^ este chunche es para q deje usar ctime, sin este el codigo manda:
// "This function or variable may be unsafe. Consider using ctime_s instead. To disable dprecation, use _CRT_SECURE_NO_WARNINGS"
// y me daba paja ponerme a buscar como haberlo "bien", pq ctime_s pedia parametros de buffer parayoquese

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "hpdf.h"
#include "reportes.h"
#include "crud_paises.h"
#include "crud_ciudades.h"
#include "crud_habitaciones.h"
#include "crud_especialidades.h"
#include "crud_diagnostico.h"
#include "crud_tratamientos.h"
#include "crud_medicos.h"
#include "crud_citas.h"
#include "crud_hospitalizaciones.h"
#include "crud_pacientes.h"
#include <ctime>





void reportes::revisarEspacio() {
    // esto lo q hace es revisar si queda espacio en la hoja actual para una nueva fila con la info
    // basicamente, si la posicion del cursor esta muy baja, en lugar de meter primero la siguiente fila crea una nueva hoja en el doc
    if (posY < 50) {
        paginaActual = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(paginaActual, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        posY = 750; // reiniciar altura del cursor a la parte de arriba, ahora en la pag nueva
        numPagina++;
        numPag();
    }
}



void reportes::generarEncabezado(string tituloReporte) {

    HPDF_Page_BeginText(paginaActual); // BeginText deja editar texto en la pag

    // titulo general
    HPDF_Page_SetFontAndSize(paginaActual, fuenteNegrita, 22); // dice q tipo de fuente y q tmñ va a usar la pag, osea aca seria fuente helvetica y tmñ 22
    HPDF_Page_TextOut(paginaActual, 137, 810, "Sistema de Gestion Hospitalaria"); // TextOut escribe en la pag dada, en X y X, el texto q se da en 4to parametro

    // titulo especifico (el q depende de opcion)
    HPDF_Page_SetFontAndSize(paginaActual, fuenteNegrita, 16); // letra mas pequeñita para el titulo "secundario"
    HPDF_Page_TextOut(paginaActual, 47, 781, tituloReporte.c_str()); //c_str da ptr a arreglo de caracteres, en este caso el arreglo seria el titulo de reporte dado

    // fecha
    time_t ahorita = time(0); // time consulta relog de compu
    string fechahora = ctime(&ahorita); //ctime agarra ptr a variable time_t (variable "ahorita") y lo pasa a cadena txt
    string txtfecha = "Fecha de emision del reporte: " + fechahora;
    HPDF_Page_SetFontAndSize(paginaActual, fuente, 10);
    HPDF_Page_TextOut(paginaActual, 47, 758, txtfecha.c_str());

    //nombres
    HPDF_Page_TextOut(paginaActual, 337, 761, "Empleados del mes:");
    HPDF_Page_TextOut(paginaActual, 337, 747, "Ian Gabriel Castro Esquivel");
    HPDF_Page_TextOut(paginaActual, 337, 733, "Maria Paula Monge Naranjo");
    //nombres v2
    HPDF_Page_TextOut(paginaActual, 47, 710, "Jefe del hospital: Ivannia Cerdas Quesada");
    HPDF_Page_TextOut(paginaActual, 47, 696, "Jefe asistente: Isaac Van der Bom");

    //recordatorio de q los totales se escriben al puro final, al puro principio de guardarYTerminar()


    HPDF_Page_EndText(paginaActual); // EndText al reves de BeginText, cierra modo de editar de la pag



    // linea caja
    HPDF_Page_Rectangle(paginaActual, 40, 685, 520, 150); // rectangulo exterior q tiene titulos, fecha, totales y nombres dentro
    // linea debajo de titulo principal
    HPDF_Page_MoveTo(paginaActual, 40, 800);  
    HPDF_Page_LineTo(paginaActual, 560, 800);
    // linea debajo de titulo especifico
    HPDF_Page_MoveTo(paginaActual, 40, 775);  
    HPDF_Page_LineTo(paginaActual, 560, 775);
    // entre fecha y totales (solo lado izq, la linea para masomenos por la mitad, cuando choca con la parte de nombres)
    HPDF_Page_MoveTo(paginaActual, 40, 750);  
    HPDF_Page_LineTo(paginaActual, 330, 750);
    // vertical que separa fecha/totales de nombres
    HPDF_Page_MoveTo(paginaActual, 330, 725); 
    HPDF_Page_LineTo(paginaActual, 330, 775);
    //fila nombres v2
    HPDF_Page_MoveTo(paginaActual, 40, 725);
    HPDF_Page_LineTo(paginaActual, 560, 725);
    HPDF_Page_Stroke(paginaActual);

    posY = 650; // pone el cursor abajito del las varas de titulo y eso, para q las filas no lo majen
}

void reportes::escribirFilaDinamica(int cantColumnas, string textos[], int anchos[]) {
    // recibe cantidad de columnas, un arreglo con textos (por ejemplo {"ID", "Nombre", "Telefono", "Especialidad"}) y un arreglo con anchos
    // la cantidad de elementos en los 2 arreglos tiene que ser igual al valor de columnas para que quede todo bien
    // el valor de la SUMA en el arreglo de ancho TIENE QUE ser 520, para evitar que aveces quede chueco
    revisarEspacio();
    contador++; // cantidad de filas totales del reporte, se inc cuando ya se va a escribir. No hay problema con q la de encabezados cuente entre los totales, pq antes de llamar se hace contador-1

    int anchoTotal = 520;
    
    // imprimir txt
    HPDF_Page_BeginText(paginaActual);
    HPDF_Page_SetFontAndSize(paginaActual, fuente, 10);

    int xActual = inicioX + 5; // el +5 es margen con la raya de la columna, para q no quede encima (osea FEO). inicio dejaba margen izq de 40
    for (int i = 0; i < cantColumnas; i++) {
        // este bucle va metiendo en la pag actual el texto a escribir, y mueve el cursor a la derecha dependiendo del ancho de su columna
        HPDF_Page_TextOut(paginaActual, xActual, posY, textos[i].c_str());
        xActual += anchos[i];
    }
    HPDF_Page_EndText(paginaActual);

    // rectangulo de fila actual
    HPDF_Page_Rectangle(paginaActual, inicioX, posY - 5, anchoTotal, altoFila); // Rectangle define dimensiones de rectangulo, toma X/Y de esquina inferior izq, ancho y alto. hace el -5 para dejar campo con texto escrito

    // lineas verticales de fila actual
    xActual = inicioX;
    for (int i = 0; i < cantColumnas - 1; i++) { // cantColumnas -1 pq no se necesita dibujar la ultima columna q ya se dibujo al hacer el rectangulo de la fila
        // este bucle es para ir dibujando las rayas verticales dentro del rectangulo de la fila actual, tomando en cuenta los anchos de cada columna
        xActual += anchos[i];
        HPDF_Page_MoveTo(paginaActual, xActual, posY - 5); // MoveTo mueve cursor a X/Y
        HPDF_Page_LineTo(paginaActual, xActual, posY - 5 + altoFila); // LineTo dibuja linea desde pos de curso actual hasta X/Y
    }

    // el Rectangle, MoveTo y LineTo no dibujan las figuras en si, solo "definen" el trayecto por asi decirlo
    // el Page_Stroke es el q ahora si dibuja todos los Rectangle/MoveTO/LineTo q se habian llamado hasta el momento, por eso va de ultimo (no se ocupa poner despues de cada rectangle, move o line)
    HPDF_Page_Stroke(paginaActual);

    posY -= altoFila; // bajar para siguiente fila
}

void reportes::guardarYTerminar(string nombreArchivo){
    escribirTotal(); // no tiene sentido hacer lo de totales en otro momento, se ocupa despues de saber cuantas filas con datos tuve el reporte al final, por eso se llama aca
    HPDF_SaveToFile(pdf, nombreArchivo.c_str()); //guarda el doc
    HPDF_Free(pdf); // chunche para liberar mem del doc
    cout << "Reporte guardado en un archivo de nombre: " << nombreArchivo << endl;
}

void reportes::numPag() {
    HPDF_Page_BeginText(paginaActual);
    HPDF_Page_SetFontAndSize(paginaActual, fuente, 12);
    string Pag = "Numero de pagina: " + to_string(numPagina);
    HPDF_Page_TextOut(paginaActual, 480, 20, Pag.c_str());
    HPDF_Page_EndText(paginaActual);
}

void reportes::escribirTotal() {
    //revisarEspacio();
    HPDF_Page_BeginText(primeraPag);
    HPDF_Page_SetFontAndSize(primeraPag, fuente, 10);
    string txttotales = "Total de registros: " + to_string(contador - 1); // -1 para no contar el del encabezado
    HPDF_Page_TextOut(primeraPag, 47, 733, txttotales.c_str());
    HPDF_Page_EndText(primeraPag);
}







//------ los reportes ------------------------------------------------------------------


void reportes::ReporteTodosPaises(ArbolPais& paises){
    reportes reportepais;
    reportepais.generarEncabezado("Listado De Todos Los Paises");
    int anchos[] = { 150, 370 };
    string textos[] = { "Codigo", "Nombre del pais" };
    reportepais.escribirFilaDinamica(2, textos, anchos);
    paises.InordenReportesPais(paises.raiz, reportepais, anchos);

    reportepais.guardarYTerminar("reporte_paises.pdf");

}

void reportes::ReporteTodasCiudadesDePais(ArbolCiudad& ciudades, ArbolPais& paises, int codPaisFiltro) {

    
    pPais pais = paises.Buscarvalor(codPaisFiltro);
    if (pais == nullptr) {
        cout << "ERROR: no existe un pais de codigo: " << codPaisFiltro << endl;
        return;
    }
    reportes reporteciudad;
    string temp = "Ciudades guardadas del pais" + pais->nombre;
    reporteciudad.generarEncabezado(temp);
    int anchos[] = {150,370};
    string textos[] = { "Codigo de ciudad", "Nombre de la ciudad" };
    reporteciudad.escribirFilaDinamica(2, textos, anchos);
    ciudades.InordenReportesCiudad(ciudades.raiz, reporteciudad, anchos, codPaisFiltro);
    reporteciudad.guardarYTerminar("reporte_ciudades_de_pais.pdf");

}

void reportes::ReporteTodosPacientes(ArbolPacientes& pacientes) {
    reportes r;
    string titulo = "Listado De Todos Los Pacientes";
    string archivo = "reporte_pacientes.pdf";
    r.generarEncabezado(titulo);
    int anchos[] = { 35, 130, 67, 75, 35, 40, 138 };
    string textos[] = { "Id", "Nombre", "Nacimiento", "Telefono","Pais", "Ciudad","Correo"};
    r.escribirFilaDinamica(7, textos, anchos);
    pacientes.InordenReportesPacientes(pacientes.raiz, r, anchos);
    r.guardarYTerminar(archivo);
}

void reportes::ReportePacientesPorPais(ArbolPacientes& pacientes, ArbolPais& paises, int codPaisFiltro) {
    if (paises.Buscarvalor(codPaisFiltro) == nullptr) {
        cout << "ERROR: no existe un pais de codigo: " << codPaisFiltro << endl;
        return;
    }
    reportes r;
    string titulo = "Listado De Pacientes De Pais Id " + to_string(codPaisFiltro);
    string archivo = "reporte_pacientes_de_pais.pdf";
    r.generarEncabezado(titulo);
    int anchos[] = { 35, 130, 67, 75, 35, 40, 138 };
    string textos[] = { "Id", "Nombre", "Nacimiento", "Telefono","Pais", "Ciudad","Correo" };
    r.escribirFilaDinamica(7, textos, anchos);
    pacientes.InordenReportesPacientesPorPais(pacientes.raiz, r, anchos, codPaisFiltro);
    r.guardarYTerminar(archivo);
}

void reportes::ReportePacientesPorCiudad(ArbolPacientes& pacientes, ArbolCiudad& ciudades, ArbolPais& paises,  int codPais,int codCiudad) {
    if (paises.Buscarvalor(codPais) == nullptr) {
        cout << "ERROR: no existe un pais de codigo: " << codPais << endl;
        return;
    }
    if (ciudades.Buscarvalor(codPais, codCiudad) == nullptr) {
        cout << "ERROR: no existe una ciudad de codigo: " << codCiudad << endl << " en el pais de codigo " << codPais << endl;
        return;
    }
    reportes r;
    string titulo = "Listado De Pacientes De Ciudad Id " + to_string(codCiudad) + " Y Pais De Id "+ to_string(codPais);
    string archivo = "reporte_pacientes_de_ciudad_de_pais.pdf";
    r.generarEncabezado(titulo);
    int anchos[] = { 35, 130, 67, 75, 35, 40, 138 };
    string textos[] = { "Id", "Nombre", "Nacimiento", "Telefono","Pais", "Ciudad","Correo" };
    r.escribirFilaDinamica(7, textos, anchos);
    pacientes.InordenReportesPacientesPorCiudad(pacientes.raiz, r, anchos, codPais, codCiudad);
    r.guardarYTerminar(archivo);
}

void reportes::ReporteTodasEspecialidades(ArbolEspecialidad& especialidades) {
    reportes r;
    r.generarEncabezado("Listado De Todas Las Especialidades");
    int anchos[] = { 50, 140, 330 };
    string textos[] = { "Id", "Nombre", "Descripcion" };
    r.escribirFilaDinamica(3, textos, anchos);
    especialidades.InordenReportesEsp(especialidades.raiz, r, anchos);
    r.guardarYTerminar("reporte_especialidades.pdf");
}

void reportes::ReporteHabitaciones(ArbolHabitaciones& habitaciones, int estado) {
    reportes r;
    string titulo = "Listado De Habitaciones Disponibles";
    string archivo = "reporte_habitaciones_disponibles.pdf";
    if (estado == 1) {
        // cambiar nombre de titulo y archivo por si se piden las habitaciones ocupadadas, no las dispo
        titulo = "Listado De Habitaciones Ocupadas";
        archivo = "reporte_habitaciones_ocupadas.pdf";
    }
    r.generarEncabezado(titulo);
    int anchos[] = { 70, 70, 100, 140, 140 };
    string textos[] = { "Id", "Numero", "Piso", "Tipo", "Estado" };
    r.escribirFilaDinamica(5, textos, anchos);
    habitaciones.InordenReportesHab(habitaciones.raiz, r, anchos, estado);
    r.guardarYTerminar(archivo);
}

void reportes::ReporteTodasHospitalizaciones(ArbolHospitalizaciones& hospitalizaciones) {
    reportes r;
    string titulo = "Listado De Todas Las Hospitalizaciones";
    string archivo = "reporte_hospitalizaciones.pdf";
    r.generarEncabezado(titulo);
    int anchos[] = { 50, 50, 50, 50, 80, 80, 180 };
    string textos[] = { "Id hosp", "Id pac", "Id hab", "Id med","Ingreso", "Salida", "Motivo"};
    r.escribirFilaDinamica(7, textos, anchos);
    hospitalizaciones.InordenReportesHosp(hospitalizaciones.raiz, r, anchos);
    r.guardarYTerminar(archivo);
}


void reportes::ReporteHospitalizacionesPorMedico(ArbolHospitalizaciones& hospitalizaciones, ArbolMedicos& medicos, int idMedico) {
    reportes r;
    string titulo = "Listado De Hospitalizaciones De Medico Id " + to_string(idMedico);
    string archivo = "reporte_hospitalizaciones_de_medico.pdf";
    r.generarEncabezado(titulo);
    int anchos[] = { 50, 50, 50, 50, 80, 80, 180 };
    string textos[] = { "Id med", "Id pac", "Id hab", "Id hops", "Ingreso", "Salida", "Motivo"};
    r.escribirFilaDinamica(7, textos, anchos);
    hospitalizaciones.InordenReportesHospDeMedico(hospitalizaciones.raiz, r, anchos, idMedico);
    r.guardarYTerminar(archivo);
}

void reportes::ReporteTodosMedicos(ArbolMedicos& medicos) {
    reportes r;
    string titulo = "Listado De Todos Los Medicos";
    string archivo = "reporte_medicos.pdf";
    r.generarEncabezado(titulo);
    int anchos[] = { 60, 140, 90, 150, 80 };
    string textos[] = { "Id", "Nombre", "Telefono", "Correo", "Id Especialidad"};
    r.escribirFilaDinamica(5, textos, anchos);
    medicos.InordenReportesMedicos(medicos.raiz, r, anchos);
    r.guardarYTerminar(archivo);
}


void reportes::ReporteMedicosPorEspecialidad(ArbolMedicos& medicos, ArbolEspecialidad& especialidades, int idEsp) {
    reportes r;
    string titulo = "Listado De Medicos De Especialidad Id " + to_string(idEsp);
    string archivo = "reporte_medicos_de_especialidad.pdf";
    r.generarEncabezado(titulo);
    int anchos[] = { 60, 140, 90, 150, 80 };
    string textos[] = { "Id", "Nombre", "Telefono", "Correo", "Id Especialidad"};
    r.escribirFilaDinamica(5, textos, anchos);
    medicos.InordenReportesMedicosPorEspecialidad(medicos.raiz, r, anchos, idEsp);
    r.guardarYTerminar(archivo);
}
/*
void reportes::ReporteCitasPorFecha(ArbolCitas& citas, string fecha) {

}

void reportes::ReporteCitasPorEspecialidad(ArbolCitas& citas, ArbolEspecialidad& especialidades, int idEsp) {

}

void reportes::ReporteCitasPorMedico(ArbolCitas& citas, ArbolMedicos& medicos, int idMedico) {

}
*/
void reportes::ReporteCitasPorPaciente(ArbolCitas& citas, ArbolPacientes& pacientes, int idPacienteFiltro) {
    if (pacientes.Buscarvalor(idPacienteFiltro) == nullptr) {
        cout << "ERROR: no existe un paciente de codigo: " << idPacienteFiltro << endl;
        return;
    }
    reportes r;
    string titulo = "Listado De Citas De Paciente Id " + to_string(idPacienteFiltro);
    r.generarEncabezado(titulo);
    int anchos[] = { 30,55,55,55,80,70,115,60 };
    string textos[] = { "Id", "IdPaciente","IdMedico","IdEspec","Fecha","Hora","Motivo","Estado" };
    r.escribirFilaDinamica(8, textos, anchos);
    citas.InordenReportesCitasPorPaciente(citas.raiz, r,  anchos, idPacienteFiltro);
    r.guardarYTerminar("reporte_citas_de_paciente.pdf");
}

void reportes::ReporteTodosDiagnosticos(ArbolDiagnostico& diag) {
    reportes r;
    r.generarEncabezado("Listado De Todos Los Diagnosticos");
    int anchos[] = { 60, 180, 280 };
    string textos[] = { "Id", "Nombre", "Descripcion" };
    r.escribirFilaDinamica(3, textos, anchos);
    diag.InordenReportesDiag(diag.raiz, r, anchos);
    r.guardarYTerminar("reporte_diagnosticos.pdf");
}

void reportes::ReporteTodosTratamientos(ArbolTratamiento& trata) {
    reportes r;
    r.generarEncabezado("Listado De Todos Los Tratamientos");
    int anchos[] = { 40, 120, 290, 70 };
    string textos[] = { "Id", "Nombre", "Descripcion", "Costo" };
    r.escribirFilaDinamica(4, textos, anchos);
    trata.InordenReportesTrata(trata.raiz, r, anchos);
    r.guardarYTerminar("reporte_tratamientos.pdf");
}



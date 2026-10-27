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





void reportes::revisarEspacio() {
    // esto lo q hace es revisar si queda espacio en la hoja actual para una nueva fila con la info
    // basicamente, si la posicion del cursor esta muy baja, en lugar de meter primero la siguiente fila crea una nueva hoja en el doc
    if (posY < 50) {
        paginaActual = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(paginaActual, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        posY = 750; // reiniciar altura del cursor a la parte de arriba, ahora en la pag nueva
        numPagina++; // para dsps
    }
}

void reportes::generarEncabezado(string tituloReporte) {
    HPDF_Page_BeginText(paginaActual); // BeginText deja editar texto en la pag

    // titulo general
    HPDF_Page_SetFontAndSize(paginaActual, fuente, 22); // dice q tipo de fuente y q tmñ va a usar la pag, osea aca seria fuente helvetica y tmñ 22
    HPDF_Page_TextOut(paginaActual, 180, 800, "Sistema de Gestion Hospitalaria"); // TextOut escribe en la pag dada, en X y X, el texto q se da en 4to parametro

    // titulo especifico (el q depende de opcion)
    HPDF_Page_SetFontAndSize(paginaActual, fuente, 16); // letra mas pequeñita para el titulo "secundario"
    HPDF_Page_TextOut(paginaActual, 180, 760, tituloReporte.c_str()); //c_str da ptr a arreglo de caracteres, en este caso el arreglo seria el titulo de reporte dado

    HPDF_Page_EndText(paginaActual); // EndText al reves de BeginText, cierra modo de editar de la pag
    posY = 700; // pone el cursor abajito del titulo especifico, para q las filas no lo majen
}

void reportes::escribirFilaDinamica(int cantColumnas, string textos[], int anchos[]) {
    // recibe cantidad de columnas, un arreglo con textos (por ejemplo {"ID", "Nombre", "Telefono", "Especialidad"}) y un arreglo con anchos
    // la cantidad de elementos en los 2 arreglos tiene que ser igual al valor de columnas para que quede todo bien
    // el valor de la SUMA en el arreglo de ancho TIENE QUE ser 520, para evitar que aveces quede chueco
    revisarEspacio();

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
    HPDF_SaveToFile(pdf, nombreArchivo.c_str()); //guarda el doc
    HPDF_Free(pdf); // chunche para liberar mem del doc
    cout << "Reporte guardado en un archivo de nombre: " << nombreArchivo << endl;
}

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
/*
void reportes::ReporteTodosPacientes(ArbolPacientes& pacientes) {

}

void reportes::ReportePacientesPorPais(ArbolPacientes& pacientes, ArbolPais& paises, int codPais) {

}

void reportes::ReportePacientesPorCiudad(ArbolPacientes& pacientes, ArbolCiudad& ciudades, ArbolPais& paises, int codPais, int codCiudad) {

}
*/
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
    archivo = "reporte_hospitalizaciones.pdf";
    r.generarEncabezado(titulo);
    int anchos[] = { 70, 70, 100, 120, 120, 20, 20 };
    string textos[] = { "Id hospitalizacion", "Id paciente", "Id habitacion", "Id medico","Ingreso", "Salida", "Motivo"};
    r.escribirFilaDinamica(7, textos, anchos);
    hospitalizaciones.InordenReportesHosp(hospitalizaciones.raiz, r, anchos);
    r.guardarYTerminar(archivo);
}

/*
void reportes::ReporteHospitalizacionesPorMedico(ArbolHospitalizaciones& hospitalizaciones, ArbolMedicos& medicos, int idMedico) {

}

void reportes::ReporteTodosMedicos(ArbolMedicos& medicos) {

}

void reportes::ReporteMedicosPorEspecialidad(ArbolMedicos& medicos, ArbolEspecialidad& especialidades, int idEsp) {

}

void reportes::ReporteCitasPorFecha(ArbolCitas& citas, string fecha) {

}

void reportes::ReporteCitasPorEspecialidad(ArbolCitas& citas, ArbolEspecialidad& especialidades, int idEsp) {

}

void reportes::ReporteCitasPorMedico(ArbolCitas& citas, ArbolMedicos& medicos, int idMedico) {

}

void reportes::ReporteCitasPorPaciente(ArbolCitas& citas, ArbolPacientes& pacientes, int idPaciente) {

}
*/
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



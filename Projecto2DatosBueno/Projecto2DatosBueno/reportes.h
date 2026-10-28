
#ifndef REPORTES_H
#define REPORTES_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "hpdf.h"
class ArbolPais;
class ArbolCiudad;
class ArbolHabitaciones;
class ArbolEspecialidad;
class ArbolMedicos;
class ArbolCitas;
class ArbolDiagnostico;
class ArbolTratamiento;
class ArbolPacientes;
class ArbolHospitalizaciones;

class reportes {
private:
    HPDF_Doc pdf;
    HPDF_Page paginaActual;
    HPDF_Font fuente; //letra
    int posY;
    int numPagina;
    int inicioX; // margen izquierdo 
    int altoFila; // altura de cada celda

public:
    reportes() {
        pdf = HPDF_New(NULL, NULL); //crear el obj de documento
        paginaActual = HPDF_AddPage(pdf);// AddPage crear pag nueva y la a;ade al final del doc
        // SetSize es para definir tmñ y orientacion de una pag
        // aca pone la pag actual en A4 (osea q lo pone en 595x 842), y la pone en formato vertical (portrait) 
        HPDF_Page_SetSize(paginaActual, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        // mete en lo de fuente en cual doc se pone esa fuente (aca el doc de nombre pedf) y el tipo de fuente en si, Helvetica
        // lo del 3er parametro es de noseque de codificacion q se ocupa poner
        fuente = HPDF_GetFont(pdf, "Helvetica", NULL);
        posY = 700;
        numPagina = 1;
        inicioX = 40;
        altoFila = 25;

        numPag();

    }
    void generarEncabezado(string tituloReporte);
    void escribirFilaDinamica(int cantColumnas, string textos[], int anchos[]);
    void guardarYTerminar(string nombreArchivo);
    void revisarEspacio();
    void numPag();

    void ReporteTodosPaises(ArbolPais& paises);
    void ReporteTodasCiudadesDePais(ArbolCiudad& ciudades, ArbolPais& paises, int codPaisFiltro);
    void ReporteTodosPacientes(ArbolPacientes& pacientes);
    void ReporteTodasEspecialidades(ArbolEspecialidad& especialidad);
    void ReporteHabitaciones(ArbolHabitaciones& habitaciones, int estado);
    void ReporteTodasHospitalizaciones(ArbolHospitalizaciones& hospitalizaciones);
    void ReporteHospitalizacionesPorMedico(ArbolHospitalizaciones& hospitalizaciones, ArbolMedicos& medicos, int IdMedico);
    void ReporteTodosMedicos(ArbolMedicos& medicos);
    void ReporteMedicosPorEspecialidad(ArbolMedicos& medicos, ArbolEspecialidad& especialidad, int IdEspFiltro);
    //void ReporteCitasPorFecha(ArbolCitas& citas);
    //void ReporteCitasPorEspecialidad(ArbolCitas& citas, ArbolEspecialidad& especialidad);
    //void ReporteCitasPorMedico(ArbolCitas& citas, ArbolMedicos& medicos);
    //void ReportePacientesPorPais(ArbolPacientes& paciente, ArbolPais& pais);
    //void ReportePacientesPorCiudad(ArbolPacientes& paciente, ArbolCiudad& ciudad, ArbolPais& pais);
    //void ReporteCitasPorPaciente(ArbolCitas& citas, ArbolPacientes& paciente);
    void ReporteTodosDiagnosticos(ArbolDiagnostico& diag);
    void ReporteTodosTratamientos(ArbolTratamiento& trata);

   

};
#endif
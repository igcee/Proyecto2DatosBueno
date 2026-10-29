
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
    int contador; // para totales
    HPDF_Page primeraPag;
    HPDF_Font fuenteNegrita;

public:
    reportes() {
        pdf = HPDF_New(NULL, NULL); //crear el obj de documento
        paginaActual = HPDF_AddPage(pdf);// AddPage crear pag nueva y la a;ade al final del doc
        primeraPag = paginaActual; // esto lo meti para poder volver a la primera pag en el momento en el q se ocupa escribir el chunche de totaes
        // ^ es pq no se puede escribir de una los totales al principio, pq no se saben cuantos datos se van a meter (lastimosamente el c++ no tiene una libreria para predecir el futuro :c )
        // No se ocuparia si quisiera meter lo de totales al final de todo el doc, pero creo q queda mas bonito al principio, junto al titulo y esas varas
        
        // SetSize es para definir tmñ y orientacion de una pag
        // aca pone la pag actual en A4 (osea q lo pone en 595x 842), y la pone en formato vertical (portrait) 
        HPDF_Page_SetSize(paginaActual, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        // mete en lo de fuente en cual doc se pone esa fuente (aca el doc de nombre pedf) y el tipo de fuente en si, Helvetica
        // lo del 3er parametro es de noseque de codificacion q se ocupa poner
        fuente = HPDF_GetFont(pdf, "Helvetica", NULL);
        fuenteNegrita = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
        posY = 700;
        numPagina = 1;
        inicioX = 40;
        altoFila = 25;
        contador = 0;


        numPag();

    }
    void generarEncabezado(string tituloReporte);
    void escribirFilaDinamica(int cantColumnas, string textos[], int anchos[]);
    void guardarYTerminar(string nombreArchivo);
    void revisarEspacio();
    void numPag();
    void escribirTotal();

    void ReporteTodosPaises(ArbolPais& paises);
    void ReporteTodasCiudadesDePais(ArbolCiudad& ciudades, ArbolPais& paises, int codPaisFiltro);
    void ReporteTodosPacientes(ArbolPacientes& pacientes);
    void ReporteTodasEspecialidades(ArbolEspecialidad& especialidad);
    void ReporteHabitaciones(ArbolHabitaciones& habitaciones, int estado);
    void ReporteTodasHospitalizaciones(ArbolHospitalizaciones& hospitalizaciones);
    void ReporteHospitalizacionesPorMedico(ArbolHospitalizaciones& hospitalizaciones, ArbolMedicos& medicos, int IdMedico);
    void ReporteTodosMedicos(ArbolMedicos& medicos);
    void ReporteMedicosPorEspecialidad(ArbolMedicos& medicos, ArbolEspecialidad& especialidad, int IdEspFiltro);
    //void ReporteCitasPorFecha(ArbolCitas& citas, string FechaFiltro);
    //void ReporteCitasPorEspecialidad(ArbolCitas& citas, ArbolEspecialidad& especialidad, int idEspFiltro);
    //void ReporteCitasPorMedico(ArbolCitas& citas, ArbolMedicos& medicos, int idMedFiltro);
    void ReportePacientesPorPais(ArbolPacientes& paciente, ArbolPais& pais, int codPaisFiltro);
    void ReportePacientesPorCiudad(ArbolPacientes& paciente, ArbolCiudad& ciudad, ArbolPais& pais, int codPaisFiltro, int codCiudadFiltro);
    void ReporteCitasPorPaciente(ArbolCitas& citas, ArbolPacientes& paciente, int idPacFiltro);
    void ReporteTodosDiagnosticos(ArbolDiagnostico& diag);
    void ReporteTodosTratamientos(ArbolTratamiento& trata);

   

};
#endif
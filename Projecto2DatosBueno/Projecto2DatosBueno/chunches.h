
/*
#ifndef CHUNCHES_H
#define CHUNCHES_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "hpdf.h"

class reportes {
private:
    HPDF_Doc pdf;
    HPDF_Page paginaActual;
    HPDF_Font fuente;
    int posY;
    int numPagina;
    int inicioX;  // margen izquierdo 
    int altoFila; // altura de cada celda

    void revisarEspacio();

public:
    reportes(){
        pdf = HPDF_New(NULL, NULL);
        paginaActual = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(paginaActual, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        fuente = HPDF_GetFont(pdf, "Helvetica", NULL);
        posY = 700;
        numPagina = 1;
        inicioX = 40;
        altoFila = 25;
    }
    void generarEncabezado(string tituloReporte);
    void escribirFilaDinamica(int cantColumnas, string textos[], int anchos[]);
    void guardarYTerminar(string nombreArchivo);
};
#endif

*/

/*
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "chunches.h"





void reportes::revisarEspacio() {
    if (posY < 50) {
        paginaActual = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(paginaActual, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        posY = 750; // reiniciar altura
        numPagina++;
    }
}

void reportes::generarEncabezado(string tituloReporte) {
    HPDF_Page_BeginText(paginaActual);

    // titulo general
    HPDF_Page_SetFontAndSize(paginaActual, fuente, 22);
    HPDF_Page_TextOut(paginaActual, 180, 800, "Archivo de reporte");

    // titulo especifico (el q depende de opcion)
    HPDF_Page_SetFontAndSize(paginaActual, fuente, 16);
    HPDF_Page_TextOut(paginaActual, 180, 760, tituloReporte.c_str());

    HPDF_Page_EndText(paginaActual);
    posY = 700;
}

void reportes::escribirFilaDinamica(int cantColumnas, string textos[], int anchos[]) {
    // recibe cantidad de columnas, un arreglo con textos (por ejemplo {"ID", "Nombre", "Telefono", "Especialidad"}) y un arreglo con anchos
    // la cantidad de elementos en los 2 arreglos tiene que ser igual al valor de columnas para que quede todo bien
    // el valor de la SUMA en el arreglo de ancho TIENE QUE ser 520, para evitar que aveces quede chueco
    revisarEspacio();

    int anchoTotal = 0;
    for (int i = 0; i < cantColumnas; i++) anchoTotal += anchos[i];

    // imprimir txt
    HPDF_Page_BeginText(paginaActual);
    HPDF_Page_SetFontAndSize(paginaActual, fuente, 10);

    int xActual = inicioX + 5; // el +5 es margen con la raya
    for (int i = 0; i < cantColumnas; i++) {
        HPDF_Page_TextOut(paginaActual, xActual, posY, textos[i].c_str());
        xActual += anchos[i];
    }
    HPDF_Page_EndText(paginaActual);

    // rectangulo exterior
    HPDF_Page_Rectangle(paginaActual, inicioX, posY - 5, anchoTotal, altoFila);

    // lineas verticales
    xActual = inicioX;
    for (int i = 0; i < cantColumnas - 1; i++) {
        xActual += anchos[i];
        HPDF_Page_MoveTo(paginaActual, xActual, posY - 5);
        HPDF_Page_LineTo(paginaActual, xActual, posY - 5 + altoFila);
    }

    HPDF_Page_Stroke(paginaActual); // formas

    posY -= altoFila; // bajar
}

void reportes::guardarYTerminar(string nombreArchivo) {
    HPDF_SaveToFile(pdf, nombreArchivo.c_str());
    HPDF_Free(pdf);
    cout << "Reporte guardado en un archivo de nombre: " << nombreArchivo << endl;
}

*/
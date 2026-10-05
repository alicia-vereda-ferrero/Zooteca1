/*****************************************
 * Nombre: Globales
 * Argumentos: 
 * Descripción: Define e inicializa las variables globales de Estadisticas
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: 
 *****************************************/

#include <stdio.h>

// Definición de las variables globales
struct _Estadisticas {
    char *Fichero;
    int NumeroFichas;
    int MaxFichas;
    int TiempoCarga;
    int TiempoSeleccion;
    int TiempoBurbuja;
    int TiempoInsercion;
    int TiempoQuicksort;
    int TiempoBusquedaSecuencial;
    int TiempoBusquedaBinaria;
    int TiempoBusquedaArbol;
} Estadisticas;

void InitGlobal()
{
    // Valores iniciales de las Estadísticas
    Estadisticas.Fichero=NULL;
    Estadisticas.NumeroFichas=0;
    Estadisticas.MaxFichas=0;
    Estadisticas.TiempoCarga=0;
    Estadisticas.TiempoSeleccion=0;
    Estadisticas.TiempoBurbuja=0;
    Estadisticas.TiempoInsercion=0;
    Estadisticas.TiempoQuicksort=0;
    Estadisticas.TiempoBusquedaSecuencial=0;
    Estadisticas.TiempoBusquedaBinaria=0;
    Estadisticas.TiempoBusquedaArbol=0;
    return;
}
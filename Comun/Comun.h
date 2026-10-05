// "C:\\mingw64\\opt\\include"
#ifndef NCOMUN
    #define NCOMUN

// Includes de las librerías estándar de C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>

//Include de Curses
#include <ncursesw/curses.h>

//Definición genérica de NODO
typedef struct _Nodo {
    void *Elemento;
    struct _Nodo *Siguiente;
} NODO;

//Estructura de Ficha de Animal
typedef struct _animal {
    char *Clase;
    char *Orden;
    char *Genero;
    char *Especie;
    char *Peso;
    char *Cerebro;
} ANIMAL;

//Protoripos de funciones comunes
void InitGlobal();
int DifTiempo(struct timeval,struct timeval);

// Variables globales
extern struct _Estadisticas {
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

//Defines de la aplicación
#define KEY_ESC 27
#define ORDEN_POR_PESO 0
#define ORDEN_POR_ESPECIE 1

#endif
/*****************************************
 * Nombre: LeeOpcion
 * Argumentos: WINDOW *Wopc : WINDOW donde se va a recibir la opción tecleada
 *             int maximo   : La opción debe ser numérica y entre 1 y 'maximo'
 * Descripción: Rutina para leer las diferentes opciones numéricas de un menú. La petición de opción debe estar siempre
 *              en las coordenadas (Filas-2,19), donde Filas es el número de filas de la ventana Wopc. La rutina lee un número
 *              y comprueba si está entre 1 y maximo (ambos incluidos). EN caso negativo se muestra un error y se vuelve a intentar.
 * Reglas de uso: 
 * Código de Retorno: int opcion : Numero tecleado (entre 1 y maximo)
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

int LeeOpcion(WINDOW *Wopc, int maximo)
{
    int opcion;
    char mensaje[80];
    int Fila,Columna;

    // La posición en la que se lee la opción se calcula
    if (Wopc == stdscr) {
        // stdscr = Menú principal
        Fila=15;
        Columna=41;
    }
    else {
        // Otro menú en la penúltima línea, columna 19
        Fila=getmaxy(Wopc)-2;
        Columna=19;
    }

    // Bucle infinito hasta que pulsen una opción correcta
    while(true) {
        // Limpiar el espacio de leer la opción
        mvwprintw(Wopc,Fila,Columna,"   ");
        // Actualizar el menú
        touchwin(stdscr);
        wrefresh(stdscr);
        touchwin(Wopc);
        wrefresh(Wopc);
        //Poner eco, lectura acabada en \n y cursor visible
        nocbreak();
        echo();
        curs_set(1);
        // Se lee la opción
        mvwscanw(Wopc,Fila,Columna,"%d",&opcion);
        // Volvemos a modo RAW y cursor invisible
        cbreak();
        noecho();
        curs_set(0);
        // Si la opción es correcta se retorna el valor
        if ((opcion >= 1) && (opcion <= maximo))
            return(opcion);
        // Se construye el mensaje de error y se muestra
        sprintf(mensaje,"Debe Introducir un valor entre 1 y %d",maximo);
        VentanaError(mensaje);
    }
}
/*****************************************
 * Nombre: VentanaSN
 * Argumentos: char *mensaje    : Mensaje de la pregunta 'S' o 'N'
 * Descripción: Presenta el mensaje en la penúltima línea de la pantalla stdscr en un colos diferente y lee del teclado
 *              la respuesta del usuario que solo puede ser 'S' o 'N'. La respuesta no debe ser sensible
 *              mayúsculas o minúsculas. Cualquier carácter que no sea válido se ignorará y se emitirá un
 *              beep.
 * Reglas de uso: 
 * Código de Retorno: char Tecla: Solo puede ser 'S' o 'N' (en mayúsculas)
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

char VentanaSN(char *mensaje)
{
    WINDOW *Wsn;
    char Tecla;
    int j,k;

    //Calculamos la posición de la ventana
    k=strlen(mensaje)+3;
    j=(80-k)/2;

    // Creamos una ventana para el mensaje
    Wsn=newwin(1,k,18,j);
    wcolor_set(Wsn,5,NULL);
    mvwprintw(Wsn,0,0," %s  ",mensaje);
    curs_set(1);    // Cursor visible

    // Bucle infinito hasta que pulsen 'S' o 'N'
    // No es sensible a las mayúsculas y minúsculas
    while(true) {
        // Borramos la última pulsación
        mvwaddch(Wsn,0,k-1,' ');
        wrefresh(Wsn);
        // Leemos una tecla
        Tecla=mvwgetch(Wsn,0,k-1);
        // La pasamos a mayúsculas
        if (Tecla > 'Z')
            Tecla -= 32;
        // La mostramos en pantalla
        mvwaddch(Wsn,0,k-1,Tecla);
        wrefresh(Wsn);
        // Si es 'S' o 'N' salimos del bucle
        if ((Tecla == 'S') || (Tecla == 'N'))
            break;
        // Aviso sonoro y 1 segundo de espera
        beep();
        sleep(1);
    }
    // Cursor invisible
    curs_set(0);
    // Una microespera para ver la tecla pulsada
    usleep(1000);

    // Se borra la ventana y se restaura stdscr
    delwin(Wsn);
    touchwin(stdscr);
    wrefresh(stdscr);

    // Se devuelve la tecla pulsada
    return (Tecla);
}

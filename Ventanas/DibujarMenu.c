/*****************************************
 * Nombre: DibujarMenu
 * Argumentos: Window *Wmenu:   Ventana donde se va a dibujar el patrón.
 *                              Si es NULL se crea la ventana.
 *             int x        : Coordenada x de la esquina superior izquierda del menú
 *             int y        : Coordenada y de la esquina superior izquierda del menú
 *             char *Titulo : String con el título del menú
 *             char *Opciones[]:    Array de strings con las diferentes opciones del menú.
 *                                  Si el string empieza con '* se entiende que es un separador y no una opción.
 *                                  Se detecta el últim string porque es NULL.
 * Descripción: Dibuja el menú segun las opciones del array *Opciones[]. Se calcula las dimensiones del menú según
 *              la longitud del título y la más larga de las opciones. Las opciones se numeran automaticamente. Si se pone algún 
 *              separador, este se imprime sin numeracion y sin el '*'. Se dibujan dos recueadros: uno para las opciones y otro para
 *              leer la opción elegida. Se colocan los caracteres gráficos de intersección que correspondan. Al final, dentro del segundo
 *              recuadro se imprime el testo 'Elija su opción: '. Para que la rutina 'LeeOpción' funcione correctamente, el comienzo
 *              de la captura de la opción debe ser en las coordenadas (Filas-2, 19), donde Filas es el número de filas de Wmenu.
 * Reglas de uso: 
 * Código de Retorno: La ventana creada o recibida Wmenu para su reutilización
 * Programador: J
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

WINDOW *DibujarMenu(WINDOW *Wmenu,int x, int y,char *Titulo,char *Opciones[])
{
    int i,j;
    int Columnas=0, Filas=5;

    /*Calculo de las dimensiones de la ventana
      El número de columnas es la longitud más larga del título o de las opciones
      + 8 caracteres para los recuadros y la numeración de las opciones */
    if (Titulo != NULL)
        Columnas=strlen(Titulo);
    for(i=0;Opciones[i] != NULL;i++) {
        if ((strlen(Opciones[i])+8) > Columnas)
            Columnas=strlen(Opciones[i])+8;
        Filas++;
    }

    // Creación de la ventana si es NULL
    if (Wmenu == NULL) {
        Wmenu=newwin(Filas,Columnas,x,y);
        x=y=0;
    }

    //Marco celeste para el recuadro del menú
    wcolor_set(Wmenu,2,NULL);
    Cuadrado(Wmenu,x+1,y,Filas-1,Columnas,SOLIDO);
    Cuadrado(Wmenu,x+Filas-3,y,3,Columnas,SOLIDO);
    //Caracteres gráficos de las intersecciones
    wattron(Wmenu,A_ALTCHARSET);
    mvwaddch(Wmenu,x+Filas-3,y,84);
    mvwaddch(Wmenu,x+Filas-3,y+Columnas-1,85);
    wattroff(Wmenu,A_ALTCHARSET);
    
    //Titulo del menu centrado en la ventana
    if (Titulo != NULL) {
        wcolor_set(Wmenu,6,NULL);
        i=(Columnas-strlen(Titulo))/2;
        mvwprintw(Wmenu,x,y+i,"%s",Titulo);
        wcolor_set(Wmenu,2,NULL);
    }

    // Texto de las opciones del menu en Blanco
    wcolor_set(Wmenu,0,NULL);
    for(i=0,j=0;Opciones[i] != NULL;i++) {
        if (Opciones[i][0] == '*') {
            // Es un separador
            wcolor_set(Wmenu,3,NULL);
            mvwprintw(Wmenu,x+i+2,y+2,"%s",Opciones[i]+1);
            wcolor_set(Wmenu,0,NULL);
            j++;
        }
        else
            //Es una opción
            mvwprintw(Wmenu,x+i+2,y+2,"%d - %s",i+1-j,Opciones[i]);
    }

    //Texto para leer la opción
    mvwprintw(Wmenu,x+Filas-2,y+2,"Elija su opcion:      ");

    //Se devuelve la ventana creada o recibida
    return(Wmenu);
}
#ifndef NFICHEROS
    #define NFICHEROS

//Include de Curses
#include <ncursesw/curses.h>

//Include para dibujar los menus
#include "..\Ventanas\Ventanas.h"

//Prototipos de funciones de Ficheros
void Fichero(ANIMAL **, int);
void ImportarFichero(ANIMAL **,WINDOW *,bool);
void ExportarFichero(ANIMAL **,WINDOW *);
void DescartarFichero(ANIMAL **,WINDOW *);
char *strsep(char **, char *);

#endif
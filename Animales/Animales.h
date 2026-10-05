#ifndef NANIMALES
    #define NANIMALES

//Include de Curses
#include <ncursesw/curses.h>

//Include para dibujar los menus
#include "..\Ventanas\Ventanas.h"

//Protoripos de funciones de Animales
void Animales(ANIMAL **);
void LimpiarAnimal(WINDOW *);
void NuevoAnimal(WINDOW *, ANIMAL **);

#endif
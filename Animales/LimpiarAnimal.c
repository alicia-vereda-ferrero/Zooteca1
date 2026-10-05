/*****************************************
 * Nombre: LimpiarAnimal
 * Argumentos: Window *Wanimal :   Ventana a limpiar
 * Descripción: Limpia los datos de la ventan de gestión de animales
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: 
 *****************************************/

// Include de la unidad funcional
#include "Animales.h"

void LimpiarAnimal(WINDOW *Wanimal)
{
    // Limpiar los datos de la ventana
    wcolor_set(Wanimal,9,NULL);
    mvwprintw(Wanimal,2,23,"                                                   ");
    mvwprintw(Wanimal,3,23,"                                                   ");
    mvwprintw(Wanimal,4,23,"                                                   ");
    mvwprintw(Wanimal,5,23,"                                                   ");
    mvwprintw(Wanimal,6,23,"                                                   ");
    mvwprintw(Wanimal,7,23,"                                                   ");
    mvwprintw(Wanimal,8,23,"                                                   ");
    mvwprintw(Wanimal,9,1,"                                                                          ");
    mvwprintw(Wanimal,10,1,"                                                                          ");
    return;
}
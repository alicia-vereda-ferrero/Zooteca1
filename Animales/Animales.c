/*****************************************
 * Nombre: Animales.
 * Argumentos: ANIMAL **Fichas:   Puntero al array de NumeroAnimal.
 * Descripción: Pantalla de gestión de fichas de animales. completos.
 *              Si se introduce un número, se muestra ese número de animal o error
 *              Si se pulsa ENTER se pregunta si se quiere añadir un animal
 *              Si se responde 'S' se introduce un animal nuevo
 *              Si se responde 'N', la función retorna.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: 
 *****************************************/

#include "Animales.h"

void Animales(ANIMAL **Fichas)
{
    static WINDOW *Wanimal=NULL;
    char linea[52];
    int NumeroAnimal;
    char Tecla;
    int TeclaFuncion;

    // Creación y dibujo de la ventana de gestión de Animales
    if (Wanimal == NULL) {
        Wanimal=newwin(12,76,5,2);
        DibujarAnimal(Wanimal);
    }

    // Bucle hasta que se desee salir
    while(true) {
        // Limpiar los datos de la ventana de gestión de animales y mensajes de ayuda
        LimpiarAnimal(Wanimal);
        wcolor_set(Wanimal,2,NULL);
        mvwprintw(Wanimal,11,17,"Enter=Nuevo/Salir      #-Visualizar Animal");
        wcolor_set(Wanimal,9,NULL);
        touchwin(Wanimal);
        wrefresh(Wanimal);
        curs_set(1);
        echo();

        // Captura del número de animal a visualizar
        NumeroAnimal=0;
        mvwgetnstr(Wanimal,2,23,linea,50);
        NumeroAnimal=atoi(linea);
        noecho();
        curs_set(0);

        // Si no es un número válido se pregunta si se desea salir
        if (NumeroAnimal <=0 ) {
            Tecla=VentanaSN("Desea dar de alta un nuevo animal (S/N)?");
            touchwin(Wanimal);
            wrefresh(Wanimal);
            // Se quiere introducir un animal nuevo
            if (Tecla == 'S')
                NuevoAnimal(Wanimal,Fichas);
            else
                // Se desea salir
                return;
        }
        else {
            // Es un número mayor que los animales que hay
            if (NumeroAnimal > Estadisticas.NumeroFichas) {
                VentanaError("No existe esa ficha de animal");
                continue;
            }
            // Leer anterior/siguiente o ESC=salir
            keypad(Wanimal,true);
            while(true) {
                // Visualizar el animal actual
                LimpiarAnimal(Wanimal);
                wcolor_set(Wanimal,9,NULL);
                mvwprintw(Wanimal,2,23,"%d",NumeroAnimal);
                mvwprintw(Wanimal,3,23,"%.51s",(*Fichas)[NumeroAnimal-1].Genero);
                mvwprintw(Wanimal,4,23,"%.51s",(*Fichas)[NumeroAnimal-1].Clase);
                mvwprintw(Wanimal,5,23,"%.51s",(*Fichas)[NumeroAnimal-1].Orden);
                mvwprintw(Wanimal,6,23,"%.51s",(*Fichas)[NumeroAnimal-1].Especie);
                mvwprintw(Wanimal,7,23,"%.51s",(*Fichas)[NumeroAnimal-1].Peso);
                mvwprintw(Wanimal,8,23,"%.51s",(*Fichas)[NumeroAnimal-1].Cerebro);
                wrefresh(Wanimal);
                while(true) {
                    // Si ESC salir del bucle
                    if ((TeclaFuncion=wgetch(Wanimal)) == KEY_ESC)
                        break;
                    else {
                        // Si LEFT, animal anterior
                        if (TeclaFuncion == KEY_LEFT) {
                            if (NumeroAnimal > 1) {
                                NumeroAnimal--;
                                break;
                            }
                            else
                                beep();
                        }
                        else {
                            // SI RIGHT, animal siguiente
                            if ((TeclaFuncion == KEY_RIGHT) && (NumeroAnimal < Estadisticas.NumeroFichas)) {
                                NumeroAnimal++;
                                break;
                            }
                            else
                                beep();
                        }
                    }
                }
                // Si ESC se vuelve a pedir el número de animal
                if (TeclaFuncion == KEY_ESC)
                    break;
            }
            keypad(Wanimal,false);
        }
    }
    return;
}
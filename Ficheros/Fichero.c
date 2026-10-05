/*****************************************
 * Nombre: Fichero
 * Argumentos: ANIMAL **Fichas:   Puntero al array de animales
 *             int OpcionMenu:   Opción del Menú de gestión de ficheros seleccionada
 * Descripción: Según la opción del menú seleccionada se invoca a la correspondiente función
 *              de gestión de ficheros (Importar, Exportar, Descartar).
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: 
 *****************************************/

#include "Ficheros.h"

void Fichero(ANIMAL **Fichas,int OpcionMenu)
{
    static WINDOW *Wfichero=NULL;
    char NombreFichero[256];

    // Si es la primera vez que se accede a esta ventana, se dibuja
    if (Wfichero == NULL) {
        Wfichero=newwin(5,76,5,2);
        DibujarGestionFichero(Wfichero);
    }

    // Limpiar los datos de la ventana
    mvwprintw(Wfichero,2,22,"                                                     ");
    mvwprintw(Wfichero,3,19,"                ");
    mvwprintw(Wfichero,3,55,"                    ");

    // Se invoca cada función según la opción de menú seleccionada
    switch (OpcionMenu) {
        case 21:    // Importar un fichero a una lista nueva
            ImportarFichero(Fichas,Wfichero,false);
            break;
        case 22:    // Sumar los animales de un fichero a una lista existente
            ImportarFichero(Fichas,Wfichero,true);
            break;
        case 23:    // Exportar la lista de animales a un fichero
            ExportarFichero(Fichas,Wfichero);
            break;
        case 24:    // Eliminar la lista de animales existente  
            DescartarFichero(Fichas,Wfichero);
            break;
    }

    return;
}
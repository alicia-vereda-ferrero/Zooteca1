/*****************************************
 * Nombre: NuevoAnimal
 * Argumentos: Window *Wanimal :   Ventana para la captura de los datos del animal nuevo
 *             ANIMAL **Fichas:    Puntero al array de animales
 * Descripción: Captura los datos de un nuevo animal y lo añade al final del array de animales
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: 
 *****************************************/

#include "Animales.h"

void NuevoAnimal(WINDOW *Wanimal,ANIMAL **Fichas)
{
    char linea[52];
    char linea1[52];
    char Tecla;

    // Si no hay espacio para un nuevo animales se reasigna más espacio al array de animales
    if (Estadisticas.NumeroFichas == Estadisticas.MaxFichas) {
        if ((*Fichas=realloc(*Fichas,sizeof(ANIMAL)*(Estadisticas.MaxFichas+100))) == NULL) {
            sprintf(linea,"Error %d al alocar %d bytes",errno,sizeof(ANIMAL)*(Estadisticas.MaxFichas+100));
            VentanaError(linea);
            return;
        }
        Estadisticas.MaxFichas+=100;
    }
    
    curs_set(1);
    echo();

    // Se imprime el número que tendrá el nuevo animal
    mvwprintw(Wanimal,2,23,"%d",Estadisticas.NumeroFichas+1);

    // Se captura el Genero del animal. No puede estar en blanco
    while(true) {
        linea[0]=0;
        mvwgetnstr(Wanimal,3,23,linea,50);
        if (strlen(linea) == 0) {
            Tecla=VentanaSN("El genero no puede estar vacio. Desea continuar (S/N)?");
            if (Tecla == 'N')
                return;
            touchwin(Wanimal);
            wrefresh(Wanimal);
        }
        else
            break;
    }

    // Se captura la Clase. No puede estar en blanco
    while(true) {
        linea1[0]=0;
        mvwgetnstr(Wanimal,4,23,linea1,50);
        if (strlen(linea1) == 0) {
            Tecla=VentanaSN("La clase no puede estar vacia. Desea continuar (S/N)?");
            if (Tecla == 'N')
                return;
            touchwin(Wanimal);
            wrefresh(Wanimal);
        }
        else
            break;
    }
    // Se guarda el Genero y Clase
    (*Fichas)[Estadisticas.NumeroFichas].Genero=malloc(strlen(linea)+1);
    strcpy((*Fichas)[Estadisticas.NumeroFichas].Genero,linea);
    (*Fichas)[Estadisticas.NumeroFichas].Clase=malloc(strlen(linea1)+1);
    strcpy((*Fichas)[Estadisticas.NumeroFichas].Clase,linea1);
    // Se captura la Clase del animal. Si es blanco, se guarda NULL
    linea[0]=0;
    mvwgetnstr(Wanimal,5,23,linea,50);
    if (strlen(linea) == 0)
        (*Fichas)[Estadisticas.NumeroFichas].Orden=NULL;
    else {
        (*Fichas)[Estadisticas.NumeroFichas].Orden=malloc(strlen(linea)+1);
        strcpy((*Fichas)[Estadisticas.NumeroFichas].Orden,linea);
    }
    // Se captura la Especie del animal. Si es blanco, se guarda NULL
    linea[0]=0;
    mvwgetnstr(Wanimal,6,23,linea,50);
    if (strlen(linea) == 0)
        (*Fichas)[Estadisticas.NumeroFichas].Especie=NULL;
    else {
        (*Fichas)[Estadisticas.NumeroFichas].Especie=malloc(strlen(linea)+1);
        strcpy((*Fichas)[Estadisticas.NumeroFichas].Especie,linea);
    }
    // Se captura el Peso. Si es blanco, se guarda NULL
    linea[0]=0;
    mvwgetnstr(Wanimal,7,23,linea,50);
    if (strlen(linea) == 0)
        (*Fichas)[Estadisticas.NumeroFichas].Peso=NULL;
    else {
        (*Fichas)[Estadisticas.NumeroFichas].Peso=malloc(strlen(linea)+1);
        strcpy((*Fichas)[Estadisticas.NumeroFichas].Peso,linea);
    }
    // Se captura el Cerebro del animal. Si es blanco, se guarda NULL
    linea[0]=0;
    mvwgetnstr(Wanimal,8,23,linea,50);
    if (strlen(linea) == 0)
        (*Fichas)[Estadisticas.NumeroFichas].Cerebro=NULL;
    else {
        (*Fichas)[Estadisticas.NumeroFichas].Cerebro=malloc(strlen(linea)+1);
        strcpy((*Fichas)[Estadisticas.NumeroFichas].Cerebro,linea);
    }

    // Se aumenta el número de animales
    Estadisticas.NumeroFichas++;
    noecho();    
    curs_set(0);

    // Mensaje de que se ha hecho bien
    VentanaError("El animal se ha dado de alta correctamente");
    return;
}
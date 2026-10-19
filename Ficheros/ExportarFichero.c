/*****************************************
 * Nombre: ExportarFichero
 * Argumentos: ANIMAL **Fichas:   Puntero al array de animales
 *             WINDOW *Wfichero: Ventana para capturar el nombre del fichero
 * Descripción: Lee el nombre del fichero que contendrá los datos a exportar. Exporta los datos de la estructura
 *              de todos los animales en el fichero.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: Naroa Rojo, Alicia Vereda y Mark Weber. 19/10/2026
 *****************************************/

#include "Ficheros.h"

void ExportarFichero(ANIMAL **Fichas,WINDOW *Wfichero)
{
    char NombreFichero[50];
    FILE *f;
    int i;


    //Comprobar si hay animales para exportar

    if(*Fichas == NULL) {
        VentanaError("No hay animales para exportar");
        return;
    } else {

        //Capturar el nombre del fichero a exportar
        curs_set(1);
        echo();

        mvwgetnstr(Wfichero,2,22,NombreFichero,49);

        curs_set(0);
        noecho();
        
        //Abrir el fichero para escritura. Si no se puede abrir, mostrar error
        f = fopen(NombreFichero, "w"); //Abre fichero y devuelve la dirección
        if(f == NULL) {
            VentanaError("No se pudo abrir el fichero para escritura");
            return;
        }

        //Escribir la cabecera en el fichero
        fprintf(f, "Clase;Orden;Genero;Especie;Peso;Tamaño cerebro\n");

        //Escribir los datos de cada animal en el fichero
        for(i = 0; i < Estadisticas.NumeroFichas; i++) {
            fprintf(f, "%s;%s;%s;%s;%s;%s\n", (*Fichas)[i].Clase ? (*Fichas)[i].Clase : "", (*Fichas)[i].Orden ? (*Fichas)[i].Orden : "", (*Fichas)[i].Genero ? (*Fichas)[i].Genero : "", (*Fichas)[i].Especie ? (*Fichas)[i].Especie : "", (*Fichas)[i].Peso ? (*Fichas)[i].Peso : "", (*Fichas)[i].Cerebro ? (*Fichas)[i].Cerebro : "");
        }

        //Cerrar el fichero
        fclose(f);

        //Mostrar número de animales exportados
        mvwprintw(Wfichero, 3,  19, "%d", Estadisticas.NumeroFichas);

        //Mostrar mensaje de éxito
        VentanaError("Fichero exportado");


    }

}

/*****************************************
 * Nombre: DescartarFichero
 * Argumentos: ANIMAL **Fichas:   Puntero al array de animales
 *             WINDOW *Wfichero: Ventana para mostrar el nombre del fichero
 * Descripción: Muestra los datos del fichero y los animales almacenados y descarta todos
 *              los animales en memoria y libera la memoria asignada.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: Naroa Rojo
 *****************************************/

#include "Ficheros.h"

void DescartarFichero(ANIMAL **Fichas,WINDOW *Wfichero)
{
    char Tecla;
    int i;

    //Comprobar que hay animales
    if((*Fichas) == NULL){
        //mostrar mensaje de error
        VentanaError("No hay fichas de animales para descartar");
    } else {
        //Confirmar si se quieren descartar animales
        Tecla = VentanaSN("Esta seguro de querer descartar los animales (S/N)?");
        if(Tecla == 'N'){
            return;
        } else{
            //Liberar el espacio asignado para cada campo:
            for(i=0; i<Estadisticas.NumeroFichas; i++){
                free((*Fichas)[i].Clase);
                free((*Fichas)[i].Orden);
                free((*Fichas)[i].Genero);
                free((*Fichas)[i].Especie);
                free((*Fichas)[i].Peso);
                free((*Fichas)[i].Cerebro);
            }

            //Liberar el espacio asignado para el array de animales
            free(*Fichas);

            //Inicializar estructuras a 0
            *Fichas = NULL;

            //Actualizar estadísticas
            Estadisticas.NumeroFichas = 0;
            Estadisticas.MaxFichas = 0;

            //Mensaje de que se ha realizado correctamente: 
            VentanaError("Se han descartado todos los animales");

        }
    }
}
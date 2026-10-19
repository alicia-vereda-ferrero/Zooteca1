/*****************************************
 * Nombre: ImortarFichero
 * Argumentos: ANIMAL **Fichas:   Puntero al array de animales
 *             WINDOW *Wfichero: Ventana para capturar el nombre del fichero
 *             bool sumar:       Si es true las fichas de animales se añaden a las existentes,
 *                               si es false la lista de animales tiene que estar vacía.
 * Descripción: Lee el nombre del fichero que contendrá los datos a importar. Carga los animales del fichero
 *              en el array de animales, dimensionándolo si es necesario y descartando los que no tengan título o autor.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: Alicia Vereda, Naroa Rojo & Mark Weber
 *****************************************/

#include "Ficheros.h"

void ImportarFichero(ANIMAL **Fichas,WINDOW *Wfichero,bool sumar)
{
    char NombreFichero[52];
    FILE *Fichero;
    struct timeval Inicio;
    struct timeval Fin;
    char linea[1024];       //linea leida del fichero
    char mensaje[80];       //texto de los mensajes de error e informacion
    char *resto;            //parte de la linea que falta por separar en campos
    char *campo;            //campo devuelto por strsep
    char *datos[6];         //campos del animal: Clase, Orden, Genero, Especie, Peso y Cerebro
    int i;
    int n;                  //numero de lineas del fichero (incluida la cabecera)
    int k;                  //animales cargados
    int d;                  //animales descartados
    int p;                  //posicion del array donde se guarda el siguiente animal

    //importar exige una lista vacia y sumar una lista con animales
    if (sumar == false && Estadisticas.NumeroFichas != 0) {
        VentanaError("Ya hay animales. Descartelos antes de importar");
        return;
    }
    if (sumar == true && Estadisticas.NumeroFichas == 0) {
        VentanaError("No hay animales a los que sumar el fichero");
        return;
    }

    //limpiar la ventana y capturar el nombre del fichero
    mvwprintw(Wfichero,2,22,"                                                     ");   //utlizo los mismo espacios que e utlizan en ficheo.c
    mvwprintw(Wfichero,3,19,"                ");
    mvwprintw(Wfichero,3,55,"                    ");
    touchwin(Wfichero);
    wrefresh(Wfichero);
    curs_set(1);
    echo();
    NombreFichero[0]=0;
    mvwgetnstr(Wfichero,2,22,NombreFichero,50);
    noecho();
    curs_set(0);

    //abrir el fichero en lectura
    Fichero=fopen(NombreFichero,"r");
    if (Fichero == NULL) {
        VentanaError("No se puede abrir el fichero");
        return;
    }

    //tiempo de inicio de la carga
    gettimeofday(&Inicio,NULL);

    //contar las lineas del fichero. Despues se cierra y se abre otra vez para leer desde el principio
    n=0;
    while (fgets(linea,1024,Fichero) != NULL)
        n++;
    fclose(Fichero);
    Fichero=fopen(NombreFichero,"r");

    //con 0 o 1 lineas (solo cabecera) no hay animales
    if (n <= 1) {
        fclose(Fichero);
        VentanaError("El fichero no contiene animales");
        return;
    }

    //asignar memoria para los animales que habra despues de importar/sumar (n-1 porque la 1a linea es la cabecera)
    if (Estadisticas.NumeroFichas+n-1 > Estadisticas.MaxFichas) {
        if ((*Fichas=realloc(*Fichas,sizeof(ANIMAL)*(Estadisticas.NumeroFichas+n-1))) == NULL) {
            fclose(Fichero);
            sprintf(mensaje,"Error %d al asignar memoria",errno);
            VentanaError(mensaje);
            return;
        }
        Estadisticas.MaxFichas=Estadisticas.NumeroFichas+n-1;
    }

    //descartar la cabecera
    fgets(linea,1024,Fichero);


    /* Leer el resto de lineas hasta EOF. Cada linea se separa en 6 campos con strsep.
       Los campos vacios se guardan como NULL y los demas se copian a memoria con malloc.
       Si el Genero es NULL se libera lo copiado y se descarta el animal. */

       
    k=0;
    d=0;
    p=Estadisticas.NumeroFichas;
    while (fgets(linea,1024,Fichero) != NULL) {
        //quitar los saltos de linea del final ('\n' y '\r')
        i=strlen(linea);
        while (i > 0 && (linea[i-1] == '\n' || linea[i-1] == '\r')) {
            linea[i-1]=0;
            i--;
        }

        //separar los 6 campos
        resto=linea;
        for (i = 0;i < 6;i++) {
            campo=strsep(&resto,";");
            if (campo == NULL || strlen(campo) == 0)
                datos[i]=NULL;
            else {
                datos[i]=malloc(strlen(campo)+1);
                strcpy(datos[i],campo);
            }
        }

        //guardar el animal o descartarlo si no tiene Genero
        if (datos[2] == NULL) {
            for (i = 0;i < 6;i++)
                free(datos[i]);
            d++;
        }
        else {
            (*Fichas)[p].Clase=datos[0];
            (*Fichas)[p].Orden=datos[1];
            (*Fichas)[p].Genero=datos[2];
            (*Fichas)[p].Especie=datos[3];
            (*Fichas)[p].Peso=datos[4];
            (*Fichas)[p].Cerebro=datos[5];
            p++;
            k++;
        }

        //mostrar los animales tratados y descartados
        mvwprintw(Wfichero,3,19,"%d",k + d);
        mvwprintw(Wfichero,3,55,"%d",d);
        wrefresh(Wfichero);
    }

    fclose(Fichero);

    //tiempo de fin de la carga
    gettimeofday(&Fin,NULL);

    //actualizar las estadisticas 
    Estadisticas.NumeroFichas=Estadisticas.NumeroFichas+k;
    Estadisticas.TiempoCarga=DifTiempo(Inicio,Fin);
    free(Estadisticas.Fichero);
    Estadisticas.Fichero=malloc(strlen(NombreFichero)+1);
    strcpy(Estadisticas.Fichero,NombreFichero);

    //informar del resultado
    if (sumar == true)
        sprintf(mensaje,"Se han sumado %d animales y se han descartado %d", k, d);
    else
        sprintf(mensaje,"Se han cargado %d animales y se han descartado %d", k, d);
    VentanaError(mensaje);
    return;
}

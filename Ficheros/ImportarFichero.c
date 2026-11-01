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

oid ImportarFichero(ANIMAL **Fichas,WINDOW *Wfichero,bool sumar)
{
    char NombreFichero[52];
    char linea[512];        //aqui va cada linea que leemos del csv
    char mensaje[80];       //para montar el mensaje final con los numeros
    char *puntero;          //lo que le pasamos a strsep, va avanzando por la linea
    char *token[6];         // los 6 trozos de la linea: clase, orden, genero, especie, peso y cerebro
    FILE *Fichero;
    struct timeval Inicio;
    struct timeval Fin;
    int n;                  //cuantas lineas tiene el fichero(contando la cabecera)
    int t;                  //cuantos anmales llevamos tratados
    int d;                  //cuantos animales hemos descartado
    int a;                  //posicion del array donde metemos el animal
    int i;

    //si es importar no puede haber animales, y si es sumar tiene que haberlos
    if (sumar == false) {
        if (Estadisticas.NumeroFichas != 0) {
            VentanaError("Ya hay animales cargados");
            return;
        }
    }
    else {
        if (Estadisticas.NumeroFichas == 0) {
            VentanaError("No hay animales cargados para sumar");
            return;
        }
    }

    //pintamos la ventana y pedimos el nombre del fichero (se ve lo que escribes y sale el cursor)
    touchwin(Wfichero);
    wrefresh(Wfichero);
    echo();
    curs_set(1);
    NombreFichero[0]=0;
    mvwgetnstr(Wfichero,2,22,NombreFichero,50);
    noecho();
    curs_set(0);

    //abrimos el fichero para leer, si no existe nos salimos
    Fichero=fopen(NombreFichero,"r");
    if (Fichero == NULL) {
        VentanaError("No se puede abrir el fichero");
        return;
    }

    //apuntamos la hora a la que empieza la carga
    gettimeofday(&Inicio,NULL);

    //contamos las lineas para saber cuantos animales hay (todas menos la cabecera)
    n=0;
    while (fgets(linea,512,Fichero) != NULL)
        n++;

    //si solo hay cabecera o esta vacio no hay nada que cargar
    if (n <= 1) {
        fclose(Fichero);
        VentanaError("El fichero no contiene animales");
        return;
    }

    /* pedimos memoria para los que ya habia mas los nuevos(n-1 porque la cabecera no cuenta).
       si fichas era NULL, realloc hace lo mismo que malloc, y si ya habia animales los mantiene */
    *Fichas=realloc(*Fichas,sizeof(ANIMAL)*(Estadisticas.NumeroFichas+n-1));
    if (*Fichas == NULL) {
        fclose(Fichero);
        VentanaError("Error al asignar memoria");
        return;
    }
    Estadisticas.MaxFichas=Estadisticas.NumeroFichas+n-1;

    //volvemos al principio del fichero y nos saltamos la cabecera
    rewind(Fichero);
    fgets(linea,512,Fichero);

    //vamos leyendo animal por animal hasta que se acabe el fichero
    t=0;
    d=0;
    a=Estadisticas.NumeroFichas;
    while (fgets(linea,512,Fichero) != NULL) {
        //quitamos el salto de linea del final, si no se nos queda pegado al ultimo campo
        for (i=0;linea[i] != 0;i++) {
            if (linea[i] == '\n' || linea[i] == '\r') {
                linea[i]=0;
                break;
            }
        }

        //partimos la linea por los ';' y si falta algun campo lo dejamos vacio
        puntero=linea;
        for (i=0;i<6;i++) {
            token[i]=strsep(&puntero,";");
            if (token[i] == NULL)
                token[i]="";
        }

        t++;

        //si no tiene genero lo descartamos, si no copiamos cada campo a su propia memoria
        if (strlen(token[2]) == 0)
            d++;
        else {
            (*Fichas)[a].Clase=malloc(strlen(token[0])+1);
            strcpy((*Fichas)[a].Clase,token[0]);

            (*Fichas)[a].Orden=malloc(strlen(token[1])+1);
            strcpy((*Fichas)[a].Orden,token[1]);

            (*Fichas)[a].Genero=malloc(strlen(token[2])+1);
            strcpy((*Fichas)[a].Genero,token[2]);

            (*Fichas)[a].Especie=malloc(strlen(token[3])+1);
            strcpy((*Fichas)[a].Especie,token[3]);

            (*Fichas)[a].Peso=malloc(strlen(token[4])+1);
            strcpy((*Fichas)[a].Peso,token[4]);

            (*Fichas)[a].Cerebro=malloc(strlen(token[5])+1);
            strcpy((*Fichas)[a].Cerebro,token[5]);

            a++;
        }

        //vamos poniendo en la ventana cuantos llevamos
        mvwprintw(Wfichero,3,19,"%d",t);
        mvwprintw(Wfichero,3,55,"%d",d);
        wrefresh(Wfichero);
    }

    //cerramos el fichero y apuntamos la hora a la que acaba
    fclose(Fichero);
    gettimeofday(&Fin,NULL);

    //guardamos los datos en las estadisticas (el nombre se copia porque nombrefichero se borra al salir)
    Estadisticas.NumeroFichas=a;
    Estadisticas.TiempoCarga=DifTiempo(Inicio,Fin);
    if (Estadisticas.Fichero != NULL)
        free(Estadisticas.Fichero);
    Estadisticas.Fichero=malloc(strlen(NombreFichero)+1);
    strcpy(Estadisticas.Fichero,NombreFichero);

    //avisamos de que ha ido bien y de cuantos se han cargado
    sprintf(mensaje,"Cargados %d animales y descartados %d",t-d,d);
    VentanaError(mensaje);
    return;
}

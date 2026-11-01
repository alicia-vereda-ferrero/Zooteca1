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
    char linea[512];        //aqui va cada linea que leemos del csv
    char mensaje[80];       //para montar los mensajes de error con numeros
    char *puntero;          //lo que le pasamos a strsep, va avanzando por la linea
    char *token[6];         //los 6 trozos de la linea: clase, orden, genero, especie, peso y cerebro
    FILE *Fichero;
    struct timeval Inicio;
    struct timeval Fin;
    int n;                  //cuantas lineas tiene el fichero (contando la cabecera)
    int d;                  //cuantos anmales hemos descartado
    int a;                  //cuantos animales hay en el array, y tambien donde metemos el siguiente
    int i;

    // si es importar no puede haber animales cargados
    if (sumar == false && Estadisticas.NumeroFichas != 0) {
        VentanaError("Hay fichas de animales");
        return;
    }

    // si es sumar tiene que haber animales cargados
    if (sumar == true && Estadisticas.NumeroFichas == 0) {
        VentanaError("No hay fichas de animales");
        return;
    }

    // la ventana solo se dibuja la primera vez, asi que ponemos el titulo segun sea importar o sumar
    if (sumar == false) {
        mvwprintw(Wfichero,0,21,"  Importar fichero de animales  ");
    }
    else {
        mvwprintw(Wfichero,0,21,"   Sumar fichero de animales    ");
    }
    touchwin(Wfichero);
    wrefresh(Wfichero);

    // pedimos el nombre del fichero (se ve lo que escribes y sale el cursor)
    echo();
    curs_set(1);
    NombreFichero[0]=0;
    mvwgetnstr(Wfichero,2,22,NombreFichero,50);
    noecho();
    curs_set(0);

    // abrimos el fichero para leer, si no existe nos salimos
    Fichero=fopen(NombreFichero,"r");
    if (Fichero == NULL) {
        sprintf(mensaje,"Error %d al abrir '%s'",errno,NombreFichero);
        VentanaError(mensaje);
        return;
    }

    // apuntamos la hora a la que empieza la carga
    gettimeofday(&Inicio,NULL);

    // contamos las lineas para saber cuantos animales hay (todas menos la cabecera)
    n=0;
    while (fgets(linea,512,Fichero) != NULL) {
        n++;
    }

    //si solo hay cabecera o esta vacio no hay nada que cargar
    if (n <= 1) {
        fclose(Fichero);
        sprintf(mensaje,"El fichero %s esta vacio",NombreFichero);
        VentanaError(mensaje);
        return;
    }

    /* pedimos memoria para los que ya habia mas los nuevos (n-1 porque la cabecera no cuenta).
       si fichas era NULL, realloc hace lo mismo que malloc, y si ya habia animales los mantiene */
    *Fichas=realloc(*Fichas,sizeof(ANIMAL)*(Estadisticas.NumeroFichas+n-1));
    if (*Fichas == NULL) {
        fclose(Fichero);
        sprintf(mensaje,"Error %d al alocar %d bytes",errno,(int)(sizeof(ANIMAL)*(Estadisticas.NumeroFichas+n-1)));
        VentanaError(mensaje);
        return;
    }
    Estadisticas.MaxFichas=Estadisticas.NumeroFichas+n-1;

    // volvemos al principio del fichero y nos saltamos la cabecera
    rewind(Fichero);
    fgets(linea,512,Fichero);

    // vamos leyendo animal por animal hasta que se acabe el fichero
    d=0;
    a=Estadisticas.NumeroFichas;
    while (fgets(linea,512,Fichero) != NULL) {

        // quitamos el salto de linea del final, si no se nos queda pegado al ultimo campo
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
            if (token[i] == NULL) {
                token[i]="";
            }
        }

        //si no tiene genero lo descartamos, si no copiamos cada campo a su propia memoria
        if (strlen(token[2]) == 0) {
            d++;
        }
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

        //vamos poniendo en la ventana cuantos animales hay ya en total y cuantos hemos descartado
        mvwprintw(Wfichero,3,19,"%d    ",a);
        mvwprintw(Wfichero,3,55,"%d    ",d);
        wrefresh(Wfichero);
    }

    // cerramos el fichero y apuntamos la hora a la que acaba
    fclose(Fichero);
    gettimeofday(&Fin,NULL);

    //guardamos los datos en las estadisticas (el nombre se copia porque nombrefichero se borra al salir)
    Estadisticas.NumeroFichas=a;
    Estadisticas.TiempoCarga=DifTiempo(Inicio,Fin);
    if (Estadisticas.Fichero != NULL) {
        free(Estadisticas.Fichero);
    }
    Estadisticas.Fichero=malloc(strlen(NombreFichero)+1);
    strcpy(Estadisticas.Fichero,NombreFichero);

    //avisamos de que ha ido bien
    VentanaError("Fichero importado");
    return;
}

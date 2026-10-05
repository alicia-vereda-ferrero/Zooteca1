/*****************************************
 * Nombre: Menu
 * Argumentos: bool borrar : flag para pedir el refresco de la pantalla.
 * Descripción: Función para el manejo de los menús. Comenzando con el menú principal, muestra un menú y pide una opción dentro del
 *              rango permitido. Si esa opción corresponde a otro menú, muestra el submenú y vuelve a pedir una opción permitida.
 *              En algunos casos hay un tercer submenu.
 * Reglas de uso: 
 * Código de Retorno: int OpcionMenu: es la opción elegida y se conforma de la siguiente manera, según el número de submenús:
 *                                    1 Submenú:    OpcionMenu1
 *                                    2 Submenús:   OpcionMenu1*10+OpcionMenu2
 *                                    3 Submenús:   OpcionMenu1*100+OpcionMenu2*10+OpcionMenu3
 * Programador: 
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

int Menu(bool borrar)
{
    //Punteros permanentes a las diferentes ventanas del menú
    static WINDOW *Wmenu=NULL;
    static WINDOW *WmenuFich=NULL;
    static WINDOW *WmenuOrd=NULL;
    static WINDOW *WmenuListado=NULL;
    static WINDOW *WmenuArbol=NULL;
    char *MenuTitulo;
    char *MenuOpciones[24];

    int OpcionMenu, OpcionMenu2;
        
    // Creación de la ventana del Menú principal o
    // Si se ha pedido redibujar la pantalla (se borra y se vuelve a dibujar)
    if ((Wmenu == NULL) || (borrar == true)) {
        Wmenu=stdscr;
        werase(Wmenu);
        //Título de la Ventana
        wcolor_set(Wmenu,3,NULL);
        Cuadrado(Wmenu,2,33,3,13,DOSRAYAS);
        mvwprintw(Wmenu,3,35," ZOOTECA");

        //Marco azul para toda la ventana
        wcolor_set(Wmenu,1,NULL);
        Cuadrado(Wmenu,0,0,20,80,DOSRAYAS);

        //Opciones del menu principal
        MenuTitulo=NULL;
        MenuOpciones[0]="Gestion de Animales";
        MenuOpciones[1]="Gestion de Ficheros de Animales";
        MenuOpciones[2]="Listado de Animales";
        MenuOpciones[3]="Arboles";
        MenuOpciones[4]="Estadisticas";
        MenuOpciones[5]="Refrescar ventanas";
        MenuOpciones[6]="Salir";
        MenuOpciones[7]=NULL;
        Wmenu=DibujarMenu(Wmenu,5,22,MenuTitulo,MenuOpciones);

        // Si querían refrescar la pantalla
        if (borrar == true) {
            touchwin(Wmenu);
            wrefresh(Wmenu);
            return(0);
        }
    }

    // Bucle infinito hasta que se obtenga una opción de menú
    while(true) {
        // Leer opción del menú principal
        OpcionMenu=LeeOpcion(Wmenu,7);
        
        // Análisis diferents opciones del menú
        switch(OpcionMenu) {
        case 2:     // Gestión de Ficheros
            if (WmenuFich == NULL) {
                // Opciones del menú de Gestión de ficheros
                MenuTitulo="GESTION DE FICHEROS DE ANIMALES";
                MenuOpciones[0]="Importar un fichero";
                MenuOpciones[1]="Sumar a un fichero";
                MenuOpciones[2]="Exportar a un fichero";
                MenuOpciones[3]="Descartar el fichero";
                MenuOpciones[4]="Salir";
                MenuOpciones[5]=NULL;
                WmenuFich=DibujarMenu(WmenuFich,5,40,MenuTitulo,MenuOpciones);
            }
            // Leer opción del menú de Gestión de ficheros
            OpcionMenu=LeeOpcion(WmenuFich,5);
            // Se devuelve la opción+20
            OpcionMenu+=20;
            return(OpcionMenu);
        case 3:     // Listados
            if (WmenuListado == NULL) {
                // Opciones del menú de listados
                MenuTitulo="Listado de los Animales";
                MenuOpciones[0]="*Metodo 1";
                MenuOpciones[1]="Listado por numero";
                MenuOpciones[2]="Listado por Especie";
                MenuOpciones[3]="Listado por Peso";
                MenuOpciones[4]="*Metodo 2";
                MenuOpciones[5]="Listado por numero";
                MenuOpciones[6]="Listado por Especie";
                MenuOpciones[7]="Listado por Peso";
                MenuOpciones[8]="* ";
                MenuOpciones[9]="Salir";
                MenuOpciones[10]=NULL;
                WmenuListado=DibujarMenu(WmenuListado,5,40,MenuTitulo,MenuOpciones);
            }
            // Leer opción del menú de listados
            OpcionMenu=LeeOpcion(WmenuListado,7);
            // Si no hay subopciones se devuelve 300+opcion*10
            OpcionMenu=(OpcionMenu+30)*10;
            if ((OpcionMenu == 310) || (OpcionMenu == 340) || (OpcionMenu == 370))
                return(OpcionMenu);
            if (WmenuOrd == NULL) {     // Hay que ordenar antes de listar
                // Opciones del menú de ordenación
                MenuTitulo="Ordenacion de los Animales";
                MenuOpciones[0]="Metodo de Seleccion";
                MenuOpciones[1]="Metodo de Burbuja";
                MenuOpciones[2]="Metodo de Insercion";
                MenuOpciones[3]="Metodo de Quicksort";
                MenuOpciones[4]="Salir";
                MenuOpciones[5]=NULL;
                WmenuOrd=DibujarMenu(WmenuOrd,5,40,MenuTitulo,MenuOpciones);
            }
            OpcionMenu2=LeeOpcion(WmenuOrd,5);
            // Se devuelve 300 + opción_listado*10+Opción_ordenación
            OpcionMenu+=OpcionMenu2;
            return(OpcionMenu);
        case 4:     //Árboles
            if (WmenuArbol == NULL) {
                // Opciones del menu de Búsquedas
                MenuTitulo="Arboles";
                MenuOpciones[0]="Creacion de un arbol binario";
                MenuOpciones[1]="Busqueda por Especie";
                MenuOpciones[2]="Busqueda por Peso";
                MenuOpciones[3]="Salir";
                MenuOpciones[4]=NULL;
                WmenuArbol=DibujarMenu(WmenuArbol,5,40,MenuTitulo,MenuOpciones);
            }
            OpcionMenu=LeeOpcion(WmenuArbol,4);
            // Se devuelve la opción+40
            OpcionMenu+=40;
            return(OpcionMenu);
        default:
            // Se devuelve la opción porque no tiene submenús
            return(OpcionMenu);
        }
    }
}
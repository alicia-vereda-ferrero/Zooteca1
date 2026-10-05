#ifndef NMENU
    #define NMENU
    
//Definiciones comunes
#include "..\Comun\Comun.h"

//Defines de la aplicación
#define SOLIDO 0
#define DOSRAYAS 1

//Prototipos de funciones de Ventanas
int Menu(bool);
WINDOW *DibujarMenu(WINDOW *,int,int,char *,char *[]);
void VentanaError(char *);
char VentanaSN();
void DibujarGestionFichero(WINDOW *);
void DibujarLeerEspecie(WINDOW *);
void DibujarEstadisticas(WINDOW *);
void Cuadrado(WINDOW *, int, int, int, int, char);
int LeeOpcion(WINDOW *, int);
void DibujarAnimal(WINDOW *);
void DibujarScroll(WINDOW *);
void VerEstadisticas();

#endif
/*****************************************
 * Nombre: DifTiempo
 * Argumentos: struct timeval inicio:   Tiempo de inicio
 *             struct timeval fin:      Tiempo de fin
 * Descripción: Calcula los microsegundos de diferencia entre ambos tiempos
 * Reglas de uso: 
 * Código de Retorno: Microsegundos de diferencia
 * Programador: 
 *****************************************/
int DifTiempo(struct timeval inicio,struct timeval fin)
{
    int segundos = fin.tv_sec - inicio.tv_sec;
    int microsegundos = fin.tv_usec - inicio.tv_usec;

    //segundos a microsegundos y suma
    int Diff = (segundos * 1000000) + microsegundos;
    
    return Diff;
}

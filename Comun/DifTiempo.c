/*****************************************
 * Nombre: DifTiempo
 * Argumentos: struct timeval inicio:   Tiempo de inicio
 *             struct timeval fin:      Tiempo de fin
 * Descripción: Calcula los microsegundos de diferencia entre ambos tiempos
 * Reglas de uso: 
 * Código de Retorno: Microsegundos de diferencia
 * Programador: Mark Weber Sainz
 *****************************************/
int DifTiempo(struct timeval inicio,struct timeval fin)
{
    int segundos = fin.tv_sec - inicio.tv_sec;//tv_sec es una libreria interna de los archivos del ordenador 
    int microsegundos = fin.tv_usec - inicio.tv_usec;//tv_usec es una libreria interna del ordenador 

    //segundos a microsegundos y suma
    int Diff = (segundos * 1000000) + microsegundos;
    
    return Diff;
}

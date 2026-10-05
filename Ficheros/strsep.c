/*****************************************
 * Nombre: strsep
 * Argumentos: char **stringp:   Puntero doble al string a tokenizar
 *             char *delim:      Puntero al string de delimitación de los separadores de token.
 * Descripción: If *stringp is NULL, the strsep() function returns NULL and does nothing else.  Otherwise,
 *              this function finds the first token in the string *stringp that is delimited by one of the bytes in the
 *              string delim.  This token is terminated by overwriting the delimiter with a null byte ('\0'),
 *              and *stringp is updated to point past the token.  In case no delimiter was found, the token 
 *              is taken to be the entire string *stringp, and *stringp is made NULL.
 * Reglas de uso: 
 * Código de Retorno: Puntero al token.
 * Programador:
 *****************************************/

#include "Ficheros.h"

char *strsep(char **stringp,char *delim)
{
    char *rv = *stringp;

    if (rv) {
        *stringp += strcspn(*stringp, delim);
        for(;*rv == ' ';rv++);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = NULL;
    }
    return(rv);
}
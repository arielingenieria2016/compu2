#include "urlparseo.h"

http_req_t urlparseo(int sd_conn) {

    char delim[] = "\n";
    char delim2[] = " ";
    char *token;
    char *token2;
    int i = 0, len = 0;
    http_req_t req;
    char buff[4096];

    read(sd_conn, buff, sizeof buff); //lee y va guardando en el buff lo que contiene sd_conn del cliente

    token = strtok(buff, delim);//Rompe la cadena buff en segmentos o tókens. Esta ruptura destruye buff, en el proceso. La forma de romper la cadena depende de la secuencia de caracteres de la cadena delim. Estos caracteres se denominan [caracteres] delimitadores. La función recorrerá la cadena en busca de alguno de los delimitadores de la cadena s2. Cuando lo encuentre, el proceso se detiene, ya que tiene un token. Posteriores llamadas a strtok romperán la cadena s1 en otros tókens. Estas llamadas pueden tener otra secuencia de delimitadores.

    for (token2 = strtok(token, delim2); token2;
            token2 = strtok(NULL, delim2)) {

        len = strlen(token2) + 1;

        switch (i) {

            case 0:
                strncpy(req.method, token2, len); //get Copia no más de n caracteres (caracteres posteriores al carácter nulo no son copiados) de la cadena apuntada por token2 a la cadena apuntada por len.
                break;

            case 1:
                strncpy(req.url, token2, len); //la url en si
                break;

            case 2:
                strncpy(req.ver, token2, len);
                break;
        }

        i++;
    }

    return req;

}

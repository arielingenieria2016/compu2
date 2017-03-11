#include "resultado_memoria.h"

void resultado_memoria(int sd_conn, char met, Mem_compartida *Memoria) {

    int lines = 0, i = 0;

    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char ini[] = "<html> <head> <meta charset='utf-8'> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Resultado</title> </head> <body>";
    char fin[] = "</body></html>";

    write(sd_conn, rhtml, strlen(rhtml)); //cabecera de respuesta HTML

    write(sd_conn, ini, strlen(ini));

    switch (met) {
        case 'c':
        {
            lines = 5;
            char httplines[lines][LINEMAX];
            snprintf(httplines[0], LINEMAX, "<h2>Memoria compartida con semaforos</h2>");
            snprintf(httplines[1], LINEMAX, "<table><tr><td>Valor en memoria compartida: %d</td></tr>", Memoria->valor);
			snprintf(httplines[2], LINEMAX, "<tr><td>Para determinar si es par o impar, ejecute el programa 'parimpar' desde otra consola.</td></tr>");
            snprintf(httplines[3], LINEMAX, "</table>");
            snprintf(httplines[4], LINEMAX, "<br><div><input type='button' id='volver' value='Volver' onclick='history.back()'/></div><br>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }
        }
            break;
    }

    write(sd_conn, fin, strlen(fin));
    write(sd_conn, "\n\n", 2);

    return;
}

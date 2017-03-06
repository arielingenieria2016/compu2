#include "resultado_mutex.h"

void resultado_mutex(int sd_conn, char met, int *datoGuardado, long int *idThreadLector) {

    int lines = 0, i = 0;

    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char ini[] = "<html> <head> <meta charset='utf-8'> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Resultado</title> </head> <body>";
    char fin[] = "</body></html>";

    write(sd_conn, rhtml, strlen(rhtml)); //cabecera de respuesta HTML

    write(sd_conn, ini, strlen(ini));

    switch (met) {
        case 'b':
        {
            lines = 10;
            char httplines[lines][LINEMAX];
            snprintf(httplines[0], LINEMAX, "<h2>Funcion con Mutex donde se lee un valor inicial con 5 y se le suma dos al mismo para ser leido de vuelta</h2>");
            snprintf(httplines[1], LINEMAX, "<table>");
			snprintf(httplines[2], LINEMAX, "<tr><td>El primer lector de id</td><td> %li </td></tr>", idThreadLector[0]);
			snprintf(httplines[3], LINEMAX, "<tr><td>Lee el valor</td><td> %d </td></tr>", datoGuardado[0]);
			snprintf(httplines[4], LINEMAX, "<tr><td>El segundo lector de id</td><td> %li </td></tr>", idThreadLector[1]);
			snprintf(httplines[5], LINEMAX, "<tr><td>Lee el valor</td><td> %d </td></tr>", datoGuardado[1]);
			snprintf(httplines[6], LINEMAX, "<tr><td>El tercer lector de id</td><td> %li </td></tr>", idThreadLector[2]);
			snprintf(httplines[7], LINEMAX, "<tr><td>Lee el valor</td><td> %d </td></tr>", datoGuardado[2]);
            snprintf(httplines[8], LINEMAX, "</table>");
            snprintf(httplines[9], LINEMAX, "<br><div><input type='button' id='volver' value='Volver' onclick='history.back()'/></div><br>");

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

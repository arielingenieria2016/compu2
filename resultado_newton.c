#include "resultado_newton.h"

void resultado_newton(int sd_conn, char *funcion, char met, params_Newton result) {

    int lines = 0, i = 0;

    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char ini[] = "<html> <head> <meta charset='utf-8'> <meta name='viewport' content='width=device-width, initial-scale=1'> <title>Resultado</title> </head> <body>";
    char fin[] = "</body></html>";

    write(sd_conn, rhtml, strlen(rhtml)); //cabecera de respuesta HTML

    write(sd_conn, ini, strlen(ini));

    switch (met) {
        case 'a':
        {
            lines = 7;
            char httplines[lines][LINEMAX];
            snprintf(httplines[0], LINEMAX, "<h2>Metodo de Newton-Raphson</h2>");
            snprintf(httplines[1], LINEMAX, "<table><tr><td>Funcion:</td><td> %s </td></tr>", result.func);
			snprintf(httplines[2], LINEMAX, "<tr><td>Numero maximo de iteraciones:</td><td> %lu </td></tr>", result.max_iter);
			snprintf(httplines[3], LINEMAX, "<tr><td>Aproximacion inicial xo:</td><td> %.14Lf </td></tr>", result.xo);
			snprintf(httplines[4], LINEMAX, "<tr><td>Tolerancia del metodo:</td><td> %.14Lf </td></tr>", result.eps);
            snprintf(httplines[5], LINEMAX, "<tr><td>Aproximacion de la raiz x:</td><td> %.14Lf </td></tr></table>", result.resultado);
            snprintf(httplines[6], LINEMAX, "<br><div><input type='button' id='volver' value='Volver' onclick='history.back()'/></div><br>");

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

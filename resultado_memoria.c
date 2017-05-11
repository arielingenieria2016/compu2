#include "resultado_memoria.h"

void resultado_memoria(int sd_conn, met_it_t met_it, Mem_compartida *Memoria, params_Newton result, long double valor) {

    int lines = 0, i = 0, j;
    

    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char ini[] = "<html> <head> <meta charset='utf-8'> <meta name='viewport' content='width=device-width, initial-scale=1'><link href='./css/style.css' rel='stylesheet' type='text/css'> <title>Resultado</title> </head> <body><div class='cabecera'><div class='contenidoCabecera'><span class='TituloPagina'>Computacion 2</span></div></div><div class='bodystyle'>";
    char fin[] = "</body></html>";

    write(sd_conn, rhtml, strlen(rhtml)); //cabecera de respuesta HTML

    write(sd_conn, ini, strlen(ini));

    switch (met_it.met) {
		case 'a':
        {

			if(strcmp(met_it.funcion, "Error") == 0){

            lines = 5;
            char httplines[lines][LINEMAX];
            snprintf(httplines[0], LINEMAX, "<div class='LetraTitulo'>Metodo de Newton-Raphson</div>");
            snprintf(httplines[1], LINEMAX, "<div class='contenidoResultado'><table>");
			snprintf(httplines[2], LINEMAX, "<tr><td>Ingrese un valor del 0 al 9 para realizar la operacion.</td></tr>");
            snprintf(httplines[3], LINEMAX, "</table></div>");
            snprintf(httplines[4], LINEMAX, "<br><div><input type='button' id='volver' value='Volver' onclick='history.back()'/></div><br>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }

			}else{
			
			lines = 7;

			/*Snprintf es esencialmente una función que redirige la salida de printf a un búfer. Esto es particularmente útil para evitar la repetición de una cadena formateada. El encabezado de función de snprintf es

  Int snprintf (char * str, tamaño size_t, const char * format, ...);

*str es el búfer en el que se redirigirá la salida de printf. size es el número máximo de bytes (caracteres) que se escribirán en el búfer.

El format y los argumentos opcionales ... son sólo los formatos de cadena como "%d", myint como se ve en printf . */
            char httplines[lines][LINEMAX];
            snprintf(httplines[0], LINEMAX, "<div class='LetraTitulo'>Metodo de Newton-Raphson</div>");
            snprintf(httplines[1], LINEMAX, "<div class='contenidoResultado'><table><tr><td>Funcion:</td><td> %s </td></tr>", result.func);
			snprintf(httplines[2], LINEMAX, "<tr><td>Numero maximo de iteraciones:</td><td> %lu </td></tr>", result.max_iter);
			snprintf(httplines[3], LINEMAX, "<tr><td>Aproximacion inicial xo:</td><td> %.14Lf </td></tr>", result.xo);
			snprintf(httplines[4], LINEMAX, "<tr><td>Tolerancia del metodo:</td><td> %.14Lf </td></tr>", result.eps);
            snprintf(httplines[5], LINEMAX, "<tr><td>Aproximacion de la raiz x:</td><td> %.14Lf </td></tr></table></div>", result.resultado);
            snprintf(httplines[6], LINEMAX, "<br><div><input type='button' id='volver' value='Volver' onclick='history.back()'/></div><br>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }

			}
        }
            break;

		case 'b':
        {

			if(strcmp(met_it.funcion, "Error") == 0){

			lines = 5;
            char httplines[lines][LINEMAX];
            snprintf(httplines[0], LINEMAX, "<div class='LetraTitulo'>Metodo de Simpson</div>");
            snprintf(httplines[1], LINEMAX, "<div class='contenidoResultado'><table>");
			snprintf(httplines[2], LINEMAX, "<tr><td>Ingrese un valor del 0 al 9 para realizar la operacion.</td></tr>");
            snprintf(httplines[3], LINEMAX, "</table></div>");
            snprintf(httplines[4], LINEMAX, "<br><div><input type='button' id='volver' value='Volver' onclick='history.back()'/></div><br>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }

			}else{

            lines = 6;
            char httplines[lines][LINEMAX];
            snprintf(httplines[0], LINEMAX, "<div class='LetraTitulo'>Metodo de Simpson</div>");
            snprintf(httplines[1], LINEMAX, "<div class='contenidoResultado'><table><tr><td>Funcion:</td><td> %d/(1+x*x) </td></tr>", met_it.integral);
			snprintf(httplines[2], LINEMAX, "<tr><td>Numero maximo de iteraciones:</td><td> %llu </td></tr>", met_it.it);
			snprintf(httplines[3], LINEMAX, "<tr><td>Resultado:</td><td> %.14Lf </td></tr>", valor);
            snprintf(httplines[4], LINEMAX, "</table></div>");
            snprintf(httplines[5], LINEMAX, "<br><div><input type='button' id='volver' value='Volver' onclick='history.back()'/></div><br>");

            for (i = 0; i < lines; i++) {
                write(sd_conn, httplines[i], strlen(httplines[i]));
            }

			}
        }
            break;		

        case 'c':
        {
            lines = 12;
            char httplines[lines][LINEMAX];
            snprintf(httplines[0], LINEMAX, "<div class='contenidoResultado'><table><tr><td>%.21Lf</td></tr>",Memoria->ultimo_resultado[0]);
			for ( j = 1; j <= 9; j++ ) {
			snprintf(httplines[j], LINEMAX, "<tr><td>%.21Lf</td></tr>",Memoria->ultimo_resultado[j]);
			}
            snprintf(httplines[10], LINEMAX, "</table></div>");
            snprintf(httplines[11], LINEMAX, "<br><div><input type='button' id='volver' value='Volver' onclick='history.back()'/></div><br>");

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

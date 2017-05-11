#include "respuesta_server.h"

met_it_t respuesta_server(int mime, int sd_conn, int fd, met_it_t met_it) {

    int leido = 0;
    char buff[4096];

    char rpdf[] = "HTTP/1.1 200 OK\nContent-Type: application/pdf;\nConnection:close\n\n";
    char rtxt[] = "HTTP/1.1 200 OK\nContent-Type: text/plain;\nConnection:close\n\n";
    char rjpg[] = "HTTP/1.1 200 OK\nContent-Type: image/jpeg; charset=utf-8\nConnection:close\n\n";
    char rhtml[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\nConnection:close\n\n";
    char rico[] = "HTTP/1.1 200 OK\nContent-Type: image/x-icon; charset=utf-8\nConnection:close\n\n";
    char rcss[] = "HTTP/1.1 200 OK\nContent-Type: text/css; charset=utf-8\nConnection:close\n\n";
    char rjs[] = "HTTP/1.1 200 OK\nContent-Type: application/javascript; charset=utf-8\nConnection:close\n\n";
    char rmd[] = "HTTP/1.1 200 OK\nContent-Type: text/markdown; charset=utf-8\nConnection:close\n\n";

    switch (mime) {
        case 1:
            write(sd_conn, rhtml, strlen(rhtml));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 2:
            write(sd_conn, rjpg, strlen(rjpg));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 3:
            write(sd_conn, rtxt, strlen(rtxt));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 4:
            write(sd_conn, rpdf, strlen(rpdf));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 5:
            write(sd_conn, rico, strlen(rico));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 6:
            write(sd_conn, rcss, strlen(rcss));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 7:
            write(sd_conn, rmd, strlen(rmd));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 8:
            write(sd_conn, rjs, strlen(rjs));
            memset(buff, 0, sizeof buff);
            while ((leido = read(fd, buff, sizeof buff)) > 0) {
                write(sd_conn, buff, leido);
            }
            write(sd_conn, "\n\n", 2);
            break;

        case 9:
            strcpy(met_it.funcion, "func1");
            met_it.met = 'a';
            return met_it;
            break;
		case 10:
            strcpy(met_it.funcion, "func2");
            met_it.met = 'a';
            return met_it;
			break;
		case 11:
            strcpy(met_it.funcion, "func3");
            met_it.met = 'a';
            return met_it;
			break;
		case 12:
            strcpy(met_it.funcion, "func4");
            met_it.met = 'a';
            return met_it;
			break;
		case 13:
            strcpy(met_it.funcion, "func5");
            met_it.met = 'a';
            return met_it;
			break;
		case 14:
            strcpy(met_it.funcion, "func6");
            met_it.met = 'a';
            return met_it;
			break;
		case 15:
            strcpy(met_it.funcion, "func7");
            met_it.met = 'a';
            return met_it;
			break;
		case 16:
            strcpy(met_it.funcion, "func8");
            met_it.met = 'a';
            return met_it;
			break;
		case 17:
            strcpy(met_it.funcion, "func9");
            met_it.met = 'a';
            return met_it;
			break;
		case 18:
            strcpy(met_it.funcion, "func10");
            met_it.met = 'a';
            return met_it;
			break;
		case 19:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 0;
            return met_it;
			break;
		case 20:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 1;
            return met_it;
			break;
		case 21:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 2;
            return met_it;
			break;
		case 22:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 3;
            return met_it;
			break;
		case 23:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 4;
            return met_it;
			break;
		case 24:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 5;
            return met_it;
			break;
		case 25:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 6;
            return met_it;
			break;
		case 26:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 7;
            return met_it;
			break;
		case 27:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 8;
            return met_it;
			break;
		case 28:
            strcpy(met_it.funcion, "Simpson");
            met_it.met = 'b';
			met_it.integral = 9;
            return met_it;
			break;
		case 29:
            strcpy(met_it.funcion, "Historial");
            met_it.met = 'c';
            return met_it;
			break;
		case 30:
            strcpy(met_it.funcion, "Error");
            met_it.met = 'a';
            return met_it;
			break;
		case 31:
            strcpy(met_it.funcion, "Error");
            met_it.met = 'b';
            return met_it;
			break;
    }

	strcpy(met_it.funcion, "");
    met_it.met = 0;
    
    return met_it;
}

CC=gcc 
CFLAGS=-g -Wall -std=gnu99 
TARGETS=server
LDFLAGS=-pthread -lrt

all: servidor

servidor: main.c controlador.c respuesta_server.c verificar_url.c verificar_mime.c urlparseo.c absoluto.c resultado_newton.c funcion_f.c f_prima.c newton.c lector.c resultado_mutex.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGETS) *~ core*


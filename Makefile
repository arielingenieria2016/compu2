CC=gcc 
CFLAGS=-g -Wall -std=gnu99 
TARGETS=servidor parimpar
LDFLAGS=-pthread -lrt

all: servidor parimpar

servidor: main.c controlador.c respuesta_server.c verificar_url.c verificar_mime.c urlparseo.c absoluto.c resultado_newton.c funcion_f.c f_prima.c newton.c lector.c resultado_mutex.c LlenarMemoria.c cerrarPrograma.c resultado_memoria.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

parimpar: ParImpar.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGETS) *~ core*


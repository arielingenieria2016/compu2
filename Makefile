CC=gcc 
CFLAGS=-g -Wall -std=gnu99 
TARGETS=servidor
LDFLAGS=-pthread -lrt

all: servidor

servidor: main.c controlador.c respuesta_server.c verificar_url.c verificar_mime.c urlparseo.c absoluto.c funcion_f.c f_prima.c newton.c simpson.c salvar_resultado.c resultado_memoria.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGETS) *~ core*


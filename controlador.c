#include "controlador.h"
#include "respuesta_server.h"
#include "verificar_url.h"
#include "verificar_mime.h"
#include "urlparseo.h"
#include "absoluto.h"
#include "funcion_f.h"
#include "f_prima.h"
#include "newton.h"
#include "resultado_newton.h"
#include "resultado_mutex.h"
#include "resultado_memoria.h"
#include "lector.h"
#include "LlenarMemoria.h"


// Variables globales para los hilos
int dato = 5; // Dato inicial
int punteroInicial = 0;
int datoGuardado[2];
long int idThreadLector[2];

void controlador(int sd_conn, struct sockaddr *cli_addr, Mem_compartida ParImpar, Mem_compartida *Memoria, sem_t *sem1){


  // Variables para la funcion de los thereads.
  int thread_num = 3;
  pthread_t *threads;
  threads = malloc (thread_num * sizeof (pthread_t));
  params_Leer leer;
  pthread_mutex_init(&leer.mlectores, NULL);
  pthread_cond_init (&leer.done, NULL);



  // Variables para la funcion de Newton.
  params_Newton p = {"(x*x)-3",0.1,1E-8,100000000,0,1};
  params_Newton q = {"(x*x)-2",0.1,1E-8,100000000,0,2};
  params_Newton e = {"(x*x)-1",0.1,1E-8,100000000,0,3};

  

  // variables para analizar la url
  char urlaux[256] = "";
  http_req_t req;
  int i = 0;
  int len;
  int fd, mime;
  int http_ok = 0;

  req = urlparseo (sd_conn);	// Parseamos la url y metemos sus componentes dentro de la estructura.

  if (verificar_url (req.method)){	  // Se chequea el metodo del request para confirmar que esté bien hecho, sino se devuelve el error.
    	write (1, "Metodo Correcto\n", 16);
    	http_ok++;

    	if (req.url[0] == '/' && (strlen (req.url) == 1)){		//Si la url está vacía se abre la página por defecto
      		mime = 1;
      		fd = open ("index.html", O_RDONLY, 0777);
    	}else{
      		len = 0;
      		len = strlen (req.url);

      		for (i = 1; i < len; i++){
      			urlaux[i - 1] = req.url[i];	//Se lee la url y se la copia a una variable auxiliar sin el primer caracter "/"
			}

      		mime = verificar_mime (urlaux);	//Se analiza el mime para saber que hacer con la peticion (MIME asigna un nombre a cada tipo de datos.)

      		if (mime == -1){ 
        		write (sd_conn, "501 Not Implemented\n", 20);   //El servidor web no entiende o no soporta el método HTTP que encuentra en el flujo de datos HTTP enviado por el cliente
        		printf ("MIME no valido (%s)\n", urlaux);
      		}else{
        		if (mime < 9){		//Si el mime es menor a diez significa que el request es para abrir un archivo del servidor.
          			fd = open (urlaux, O_RDONLY, 0664);
        		}
      		}
    	}

    	if ((fd < 0) && (mime < 9) && req.url[0] != '/'){
      		write (sd_conn, "404 fila no encontrada\n", 30);
      		perror ("Fila no encontrada");
    	}else{
      		write (1, "Ok Fila encontrada\n\n", 20);
      		http_ok++;
    	}
  }else{
  		write (sd_conn, "400 Bad request\n", 16);   //El servidor web cree que el flujo de datos enviado por el cliente estaba "malformado", es decir, no respetaba completamente el protocolo HTTP. Por lo tanto, el servidor web no pudo entender y procesar la solicitud.
  }


  if (http_ok == 2)
  	   met_it = respuesta_server (mime, sd_conn, fd);	//Se analiza el codigo que resulta del analisis del MIME para ver respuesta http se debe devolver al cliente.

  if (met_it.funcion)
  {				//Si la estructura contiene algún valor

    if (met_it.met=='a')	{   //Para el metodo a se realiza el metodo de newton
		
		pthread_t thread[0];
		if(strcmp(met_it.funcion, "func1") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&p);
			pthread_join(thread[0],NULL);
			resultado_newton (sd_conn, met_it.funcion, met_it.met, p);
		}

		if(strcmp(met_it.funcion, "func2") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&q);
			pthread_join(thread[0],NULL);
			resultado_newton (sd_conn, met_it.funcion, met_it.met, q);
		}

		if(strcmp(met_it.funcion, "func3") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&e);
			pthread_join(thread[0],NULL);
			resultado_newton (sd_conn, met_it.funcion, met_it.met, e);
		}

	}

	if (met_it.met=='b')	{	 //Se realiza la funcion que aplica mutex
		
		params_Leer *params_array = malloc (thread_num * sizeof (params_Leer));	//Se crea un puntero para crear una estructura para cada thread.

		for (i = 0; i < thread_num; i++){
 			pthread_create(&threads[i], NULL, lector, &params_array[i]);
  		}

		for (i = 0; i < thread_num; i++){
    		pthread_join (threads[i], NULL);	//Se espera a que los thread terminen de sumar
 		}

		pthread_mutex_destroy (&leer.mlectores);  //Se destruye el mutex
		pthread_cond_destroy (&leer.done);

		resultado_mutex(sd_conn, met_it.met, datoGuardado, idThreadLector);
		
		free(params_array);
		memset( datoGuardado, '\0', 2 );
		memset( idThreadLector, '\0', 2 );
	}
	
	if (met_it.met=='c')	{	 //Se realiza la funcion que aplica memoria compartida y semaforos
		
		LlenarMemoria(ParImpar, sem1, Memoria); //Enviamos el resultado a memoria compartida
		resultado_memoria(sd_conn, met_it.met, Memoria);

	}
    
  }


  free (threads);
  close (fd);
  close (sd_conn);
  return;
}

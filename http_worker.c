#include "http_worker.h"
#include "http_response.h"
#include "checkget.h"
#include "checkext.h"
#include "parse.h"
#include "absoluto.h"
#include "funcion_f.h"
#include "f_prima.h"
#include "newton.h"
#include "write_result.h"

void http_worker(int sd_conn, struct sockaddr *cli_addr)
{
  
  int lectores = 0; /* numero de lectores, es también un recurso, tan solo para los lectores */
  pthread_mutex_t mutexG; /* controlar el acceso a dato */
  pthread_mutex_t mlectores; /* controla acceso n_lectores */
  params_Leer Mutex = {5,0};

  params_Newton p = {"(x*x)-3",0.1,1E-8,100000000,0,1};
  params_Newton q = {"(x*x)-2",0.1,1E-8,100000000,0,2};
  params_Newton e = {"(x*x)-1",0.1,1E-8,100000000,0,3};

  char urlaux[256] = "";
  http_req_t req;
  int i = 0;
  int len;
  int fd, mime;
  int http_ok = 0;

  req = parse (sd_conn);	//Parseamos el request y lo metemos dentro de la estructura

  if (checkget (req.method))
  {				//Se chequea el metodo del request para confirmar que esté bien hecho, sino se devuelve el error.
    write (1, "Ok (Method)\n", 12);
    http_ok++;

    if (req.url[0] == '/' && (strlen (req.url) == 1))
    {			//Si la url está vacía se abre la página por defecto
      mime = 1;
      fd = open ("index.html", O_RDONLY, 0777);
    }
    else
    {
      len = 0;
      len = strlen (req.url);

      for (i = 1; i < len; i++)
      urlaux[i - 1] = req.url[i];	//Se lee la url y se la copia a una variable auxiliar sin el primer caracter "/"

      mime = checkext (urlaux);	//Se analiza el mime para saber que hacer con el request

      if (mime == -1)
      {
        write (sd_conn, "501 Not Implemented\n", 20);
        printf ("MIME no valido (%s)\n", urlaux);
      }
      else
      {
        if (mime < 10)
        {		//Si el mime es menor a diez significa que el request es para abrir un archivo del servidor.
          fd = open (urlaux, O_RDONLY, 0664);
        }
      }
    }

    if ((fd < 0) && (mime < 9) && req.url[0] != '/')
    {
      write (sd_conn, "404 File Not Found\n", 19);
      perror ("File Not Found");
    }
    else
    {
      write (1, "Ok (File)\n\n", 11);
      http_ok++;
    }
  }
  else
  write (sd_conn, "400 Bad request\n", 16);

  if (http_ok == 2)
  met_it = http_response (mime, sd_conn, fd);	//Se analiza el codigo que resulta del analisis del MIME para ver respuesta http se debe devolver al cliente.

  if (met_it.funcion)
  {				//Si la estructura contiene algún valor

    if (met_it.met=='a')	{
		
		if(strcmp(met_it.funcion, "func1") == 0){
			pthread_t thread[1];
			pthread_create(&thread[0],NULL,newton,(void*)&p);
			pthread_join(thread[0],NULL);
			write_result (sd_conn, met_it.funcion, met_it.met, p);
		}

		if(strcmp(met_it.funcion, "func2") == 0){
			pthread_t thread[1];
			pthread_create(&thread[0],NULL,newton,(void*)&q);
			pthread_join(thread[0],NULL);
			write_result (sd_conn, met_it.funcion, met_it.met, q);
		}

		if(strcmp(met_it.funcion, "func3") == 0){
			pthread_t thread[1];
			pthread_create(&thread[0],NULL,newton,(void*)&e);
			pthread_join(thread[0],NULL);
			write_result (sd_conn, met_it.funcion, met_it.met, e);
		}

	}

	if (met_it.met=='b')	{

		/*
 * Código del escritor
 */
void *Escritor(void *args) {
 	params_Leer *Mutex = (params_Leer *)args;
 	pthread_mutex_lock(&mutexG);
	int i = Mutex->punteroInicial;
	Mutex->idThreadEscritor[i]=(unsigned long)pthread_self();
 	Mutex->dato = Mutex->dato + 2; /* aumenta el dato*/
 	printf(" (pthread id %lu) Escritor has started\n", (unsigned long)pthread_self()); /* leemos el dato dato */
 	pthread_mutex_unlock(&mutexG);
 	pthread_exit(NULL);
}
 
/*
 * Código del lector
 */
void *Lector(void *args) {
 	params_Leer *Mutex = (params_Leer *)args;
 	pthread_mutex_lock(&mlectores);
 	lectores++;
 	if (lectores == 1){
  		pthread_mutex_lock(&mutexG);
 		pthread_mutex_unlock(&mlectores);
		int i = Mutex->punteroInicial;
		Mutex->idThreadLector[i]=(unsigned long)pthread_self();
		printf("%d\n", Mutex->dato);
 		printf(" (pthread id %lu) Lector has started\n", (unsigned long)pthread_self()); /* leemos el dato dato */
		Mutex->punteroInicial= Mutex->punteroInicial+1;
 		pthread_mutex_lock(&mlectores);
 		lectores--;
	}
 	if (lectores == 0){
  		pthread_mutex_unlock(&mutexG);
 		pthread_mutex_unlock(&mlectores);
	}
 	pthread_exit(NULL);
}
		
		pthread_t th1, th2, th3, th4, th5, th6;
 		pthread_mutex_init(&mutexG, NULL);
 		pthread_mutex_init(&mlectores, NULL);
		pthread_create(&th1, NULL, Lector, (void*)&Mutex);
		pthread_create(&th2, NULL, Escritor, (void*)&Mutex);
		pthread_create(&th3, NULL, Lector, (void*)&Mutex);
		pthread_create(&th4, NULL, Escritor, (void*)&Mutex);
		pthread_create(&th5, NULL, Lector, (void*)&Mutex);
		pthread_create(&th6, NULL, Escritor, (void*)&Mutex);
  
 		pthread_join(th1, NULL);
		pthread_join(th2, NULL);
		pthread_join(th3, NULL);
		pthread_join(th4, NULL);
		pthread_join(th5, NULL);
		pthread_join(th6, NULL);
 		
  
 		pthread_mutex_destroy(&mutexG);
 		pthread_mutex_destroy(&mlectores);

		for(i = 0; i < 10; i++){
			printf("El elemento %d vale %li\n", i, Mutex.idThreadLector[i]);
		}
		for(i = 0; i < 10; i++){
			printf("El elemento %d vale %li\n", i, Mutex.idThreadEscritor[i]);
		}
		write_result (sd_conn, met_it.funcion, met_it.met, Mutex);

	}
    
  }



  close (fd);
  close (sd_conn);
  return;
}

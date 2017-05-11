#include "controlador.h"
#include "respuesta_server.h"
#include "verificar_url.h"
#include "verificar_mime.h"
#include "urlparseo.h"
#include "absoluto.h"
#include "funcion_f.h"
#include "f_prima.h"
#include "newton.h"
#include "resultado_memoria.h"
#include "simpson.h"
#include "salvar_resultado.h"


// Variables globales para los hilos
long double suma = 0.0;

void controlador(int sd_conn, struct sockaddr *cli_addr, Mem_compartida *Memoria, sem_t *semaforo){
  
  // Variables para la funcion de los thereads.
  int thread_num = 10;
  pthread_t *threads;
  threads = malloc (thread_num * sizeof (pthread_t));
  params_Simpson *params_array;	//Se crea un puntero para crear una estructura para cada thread.
  params_array = malloc (thread_num * sizeof (params_Simpson));
  params_Simpson simpson;
  pthread_mutex_init(&simpson.mutex, NULL); //Inicializa el mutex
  pthread_cond_init(&simpson.done, NULL); //condiciones de la variable es por defecto

  /* Variables para los cálculos */
  long double valor = 0.0;
  unsigned long long int coef;
  long double h;
  resultado_calculado calculo;

  // Variables para la funcion de Newton.
  params_Newton a = {"(x*x)-0",0.1,1E-8,100000000,0,0};
  params_Newton p = {"(x*x)-1",0.1,1E-8,100000000,0,1};
  params_Newton q = {"(x*x)-2",0.1,1E-8,100000000,0,2};
  params_Newton r = {"(x*x)-3",0.1,1E-8,100000000,0,3};
  params_Newton s = {"(x*x)-4",0.1,1E-8,100000000,0,4};
  params_Newton b = {"(x*x)-5",0.1,1E-8,100000000,0,5};
  params_Newton c = {"(x*x)-6",0.1,1E-8,100000000,0,6};
  params_Newton d = {"(x*x)-7",0.1,1E-8,100000000,0,7};
  params_Newton e = {"(x*x)-8",0.1,1E-8,100000000,0,8};
  params_Newton f = {"(x*x)-9",0.1,1E-8,100000000,0,9};

  // variables para analizar la url
  char urlaux[256] = "";
  http_req_t req;
  met_it_t met_it;
  int i = 0;
  int len;
  int fd, mime;
  int http_ok = 0;

  req = urlparseo (sd_conn);	// Parseamos la url y metemos sus componentes dentro de la estructura.

  if (verificar_url (req.method)){	  // Se chequea el metodo del request para confirmar que esté bien hecho, sino se devuelve el error.
    	write (1, "Metodo Correcto\n", 16);// 0, 1, or 2, para referirse a standard input, standard output, or standard error, respectivamente.
    	http_ok++;

    	if (req.url[0] == '/' && (strlen (req.url) == 1)){		//Si la url está vacía se abre la página por defecto
      		mime = 1;
			/*La función open devuelve un número entero que identifica a un descriptor de fichero o -1 en caso de error, y tiene como parámetros un puntero a la ruta del fichero que queramos abrir y unas banderas (flags) que indican la forma de apertura, solo lectura y permisos, leer, escribir y ejecutar*/
      		fd = open ("index.html", O_RDONLY, 0777);
    	}else{
      		len = 0;
      		len = strlen (req.url); // cuantas letras tiene la palabra (longitud de cadena);
			
      		for (i = 1; i < len; i++){
      			urlaux[i - 1] = req.url[i];	//Se lee la url y se la copia a una variable auxiliar sin el primer caracter "/"
			}

      		mime = verificar_mime (urlaux);	//Se analiza el mime para saber que hacer con la peticion (MIME asigna un nombre a cada tipo de datos.)

      		if (mime == -1){ 
        		write (sd_conn, "501 Not Implemented\n", 20);   /*El servidor web no entiende o no soporta el método HTTP que encuentra en el flujo de datos HTTP enviado por el cliente, sd_conn el file descriptor de donde escribir la salida y la cantidad a escribir*/
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
  		write (sd_conn, "400 Bad request\n", 16);   /*El servidor web cree que el flujo de datos enviado por el cliente estaba "malformado", es decir, no respetaba completamente el protocolo HTTP. Por lo tanto, el servidor web no pudo entender y procesar la solicitud.*/
  }


  if (http_ok == 2)
  	   met_it = respuesta_server (mime, sd_conn, fd, met_it);	//Se analiza el codigo que resulta del analisis del MIME para ver respuesta http se debe devolver al cliente.

  if (met_it.funcion)
  {				//Si la estructura contiene algún valor

    if (met_it.met=='a')	{   //Para el metodo a se realiza el metodo de newton

	/* En análisis numérico, el método de Newton (conocido también como el método de Newton-Raphson o el método de Newton-Fourier) es un algoritmo para encontrar aproximaciones de los ceros o raíces de una función real. El método de Newton-Raphson es un método abierto, en el sentido de que no está garantizada su convergencia global. La única manera de alcanzar la convergencia es seleccionar un valor inicial lo suficientemente cercano a la raíz buscada. Así, se ha de comenzar la iteración con un valor razonablemente cercano al cero (denominado punto de arranque o valor supuesto). Una vez que se ha hecho esto, el método linealiza la función por la recta tangente en ese valor supuesto. La abscisa en el origen de dicha recta será, según el método, una mejor aproximación de la raíz que el valor anterior. Se realizarán sucesivas iteraciones hasta que el método haya convergido lo suficiente. Sea f: [a, b] -> R función derivable definida en el intervalo real [a, b]. Empezamos con un valor inicial x0 y definimos para cada número natural n

    x n+1 = x n − (f (x n)/ f′ (x n))

Donde f' denota la derivada de f.

Nótese que el método descrito es de aplicación exclusiva para funciones de una sola variable
Error relativo entre dos aproximaciones sucesivas:

    E = | x k+1 − x k | / | x k+1 |

Con lo cual se toma el error relativo como si la última aproximación fuera el valor exacto. Se detiene el proceso iterativo cuando este error relativo es aproximadamente menor que una cantidad fijada previamente.

Fuente:https://es.wikipedia.org/wiki/M%C3%A9todo_de_Newton */

		pthread_t thread[0];

		if(strcmp(met_it.funcion, "func1") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&a);  // crea el hilo,ejecuta una funcion y pasa el parametro que puede ser una estructura
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, a, valor);
			calculo.resultado_final=a.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func2") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&p);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, p, valor);
			calculo.resultado_final=p.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func3") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&q);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, q, valor);
			calculo.resultado_final=q.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func4") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&r);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, r, valor);
			calculo.resultado_final=r.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func5") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&s);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, s, valor);
			calculo.resultado_final=s.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func6") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&b);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, b, valor);
			calculo.resultado_final=b.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func7") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&c);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, c, valor);
			calculo.resultado_final=c.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func8") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&d);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, d, valor);
			calculo.resultado_final=d.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func9") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&e);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, e, valor);
			calculo.resultado_final=e.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else if(strcmp(met_it.funcion, "func10") == 0){
			pthread_create(&thread[0],NULL,newton,(void*)&f);
			pthread_join(thread[0],NULL);
			resultado_memoria (sd_conn, met_it, Memoria, f, valor);
			calculo.resultado_final=f.resultado;
			salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		}else{
			resultado_memoria (sd_conn, met_it, Memoria, f, valor);
		}

	}

	if (met_it.met=='b')	{	 //Se realiza la funcion que aplica mutex

	/*La regla de simpson es un método de integración numérica para obtener la aproximación de una integral. Utilizaremos la integral entre 0 y 1 de [varialble aleatoria/(1+x²)], dividimos el intervalo de integración entre el total de hilos involucrados y hacer que cada uno calcule un intervalo definido de la integral. Una vez obtenido cada resultado parcial, se suman todos para obtener la aproximación de la funcion. Es decir, que sobre cada subintervalo en el que se divide [a,b] que en este caso es 0 y 1 se aproxima f por un polinomio de segundo grado, para luego calcular la integral como suma de las áreas formados en esos subintervalos.*/
    if(strcmp(met_it.funcion, "Error") == 0){

		resultado_memoria(sd_conn, met_it, Memoria, p, valor);

	}else{

		met_it.it=100000;
      	coef = met_it.it / thread_num;	//Calculo cuantas iteraciones le corresponde a cada thread del pool.
      	h = 1.0 / (long double) met_it.it;

		for (i = 0; i < thread_num; i++){
			(params_array + i)->coef = coef;
        	(params_array + i)->h = h;
      		(params_array + i)->thr_id = i + 1;
			(params_array + i)->integral = met_it.integral;
 			pthread_create(&threads[i], NULL, simp, &params_array[i]);
  		}

		for (i = 0; i < thread_num; i++){
    		pthread_join (threads[i], NULL);	//Se espera a que los thread terminen de sumar
 		}

		pthread_mutex_destroy (&simpson.mutex);  //Destruye el mutex (lo elimina de la memoria).
		pthread_cond_destroy (&simpson.done);

		valor = suma * h;	//Termino de Calcular Pi
        calculo.resultado_final = valor;	//Meto el resultado en la estructura de los resultados

		suma = 0.0;  

		printf("Resultado: %.21Lf\n",calculo.resultado_final);
		salvar_resultado(calculo, semaforo, Memoria); //Enviamos el resultado a memoria compartida
		
		resultado_memoria(sd_conn, met_it, Memoria, p, valor);
	}
		
		free(params_array);
	}
	
	if (met_it.met=='c')	{	 //Se realiza la funcion que aplica memoria compartida y semaforos
		
		resultado_memoria(sd_conn, met_it, Memoria, p, valor);

	}
    
  }

  free (threads); /*Cuando se ha terminado de utilizar un bloque de memoria previamente asignado por malloc ( ) , u otras funciones de asignación, se puede liberar el espacio de memoria y dejarlo disponible para otros usos, mediante una llamada a la función free ( ) . El bloque de memoria suprimido se devuelve al espacio de almacenamiento libre, de modo que habrá más memoria disponible para asignar otros bloques de memoria. El formato de la llamada es
free (puntero)*/
  close (fd); //La función close cierra el descriptor de fichero que le pasemos como parámetro. Devuelve 0 en caso de éxito y -1 en caso de error.
  close (sd_conn); /*Normalmente el servidor cierra el descriptor del cliente (Descriptor_Cliente), no el del socket (Descriptor), ya que este se suele dejar abierto para volver a realizar una llamada a accept() y sacar al siguiente cliente de la cola.*/
  return;
}

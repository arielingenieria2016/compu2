#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ctype.h>

#include "controlador.h"

int main(int argc, char *const *argv) {
  int sd, sd_conn, c, port_num = 8000;
  int reuse = 1;
  socklen_t addrlen;
  struct sockaddr_in6 srv_addr;
  struct sockaddr_in6 cli_addr;
  char client_addr_ipv6[100];

  while ((c = getopt (argc, argv, "p:")) != -1)
  switch (c)
  {
    case 'p':
    if (atoi(optarg) > 0) {
      port_num = atoi(optarg);
    } else {
      fprintf(stderr, "Puerto no valido\n");
      exit(EXIT_FAILURE);
    }
    break;

    default:
    abort();
  }

  printf("\nPuerto: %d \n", port_num);

  sd = socket(AF_INET6, SOCK_STREAM, 0);

  if (sd < 0) {
    perror("SOCKET Error");
    exit(EXIT_FAILURE); }

  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof (reuse)) < 0)
  perror("setsockopt(SO_REUSEADDR) error");

  srv_addr.sin6_flowinfo = 0;
  srv_addr.sin6_family = AF_INET6;
  srv_addr.sin6_addr = in6addr_any;
  srv_addr.sin6_port = htons(port_num);

  if (bind(sd, (struct sockaddr *) &srv_addr, sizeof (srv_addr)) == -1) {
    perror("BIND Error");
    exit(EXIT_FAILURE); }

  if (listen(sd, 5) < 0) {
    perror("Listen Error.");
    exit(EXIT_FAILURE); }

  addrlen = sizeof(cli_addr);

  while ((sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
    switch (fork()) {
      case 0: // hijo
      controlador(sd_conn, (struct sockaddr *) &cli_addr);
      return 0;

      case -1: // error
      perror("Fork() Error");
      break;

      default: // padre

      if(sd_conn < 0) {
        perror("Accept Error");
        exit(EXIT_FAILURE); 
      }
        inet_ntop(AF_INET6, &(cli_addr.sin6_addr),client_addr_ipv6, 100);
        printf("Conexion Recibida: %s\n",client_addr_ipv6);
        close(sd_conn);
        break;
      }
    }

  return 0;
}

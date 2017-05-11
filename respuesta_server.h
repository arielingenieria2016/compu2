#ifndef RESPUESTA_SERVER_H
#define	RESPUESTA_SERVER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <unistd.h>
#include <string.h>
#include "controlador.h" 

    met_it_t respuesta_server(int mime, int sd_conn, int fd, met_it_t met_it);


#ifdef	__cplusplus
}
#endif

#endif	/* RESPUESTA_SERVER_H */


#ifndef URLPARSEO_H
#define	URLPARSEO_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "controlador.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

    extern http_req_t req;
    http_req_t urlparseo(int sd_conn);

#ifdef	__cplusplus
}
#endif

#endif	/* URLPARSEO_H */

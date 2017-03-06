#include "verificar_mime.h"

int verificar_mime(char *arch) {

    char *token; //Para guardar la extension del archivo
    char *token2; //Para guardar la peticion get de la extension  despues del ?
    int dif, dif2;
    token = strrchr(arch, '.'); //Localizamos el caracter del punto
    token = token + 1; //Nos paramos en el caracter siguiente al punto
    dif = strcmp(token, "html");
    if (dif == 0) {
        return 1;
    } else {
        dif = strcmp(token, "jpg");
        dif2 = strcmp(token, "jpeg");

        if (dif == 0 || dif2 == 0) {
            return 2;
        } else {
            dif = strcmp(token, "txt");
            if (dif == 0) {
                return 3;
            } else {
                dif = strcmp(token, "pdf");
                if (dif == 0) {
                    return 4;
                } else {
                    dif = strcmp(token, "ico");
                    if (dif == 0) {
                        return 5;
                    } else {
                        dif = strcmp(token, "css");
                        if (dif == 0) {
                            return 6;
                        } else {
                            dif = strcmp(token, "md");
                            if (dif == 0) {
                                return 7;
                            } else {
                            dif = strcmp(token, "js");
                            if (dif == 0) {
                                return 8;
                            } else {
                                token2 = strrchr(token, '?'); //Si encuentra un '?' es por que no es un documento sino una operación

                                if (token2[0] == '?') {
									token2 = token2 + 1;

                                    	switch (token2[0]) {
                                            //Cálculo de Newton
                                        	case 'a':
                                            	token2 = token2 + 1;
                                            	switch (token2[0]) {
                                    				case '1':
                                        				return 9;
                                        				break;
													case '2':
                                                    	return 10;
                                                    	break;
													case '3':
                                                    	return 11;
                                                    	break;
												}
												break;
											case 'b':
                                            	token2 = token2 + 1;
                                            	switch (token2[0]) {
                                                	case '1':
                                                    	return 12;
                                                    	break;
                                            	}
                                            	break;
                                    	 }

                                } else {
                                    return -1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return -1;
}


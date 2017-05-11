#include "verificar_mime.h"

int verificar_mime(char *arch) {

    char *token; //Para guardar la extension del archivo
    char *token2; //Para guardar la peticion get de la extension despues del ?
    int dif, dif2;
    token = strrchr(arch, '.'); //Localizamos el caracter del punto
    token = token + 1; //Nos paramos en el caracter siguiente al punto
    dif = strcmp(token, "html"); //devuelve cero si son iguales
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
                                token2 = strrchr(token, '?'); //Si encuentra un '?' es por que no es un documento sino una operación,La función retorna un puntero a partir del carácter encontrado. Si no se ha encontrado el carácter, c, entonces retorna un puntero nulo.

                                if (token2[0] == '?') {
									token2 = token2 + 1;

                                    	switch (token2[0]) {
                                            //Cálculo de Newton
                                        	case 'a':
                                            	token2 = token2 + 2;
                                            	switch (token2[0]) {
													case '0':
                                        				return 9;
                                        				break;
                                    				case '1':
                                        				return 10;
                                        				break;
													case '2':
                                                    	return 11;
                                                    	break;
													case '3':
                                                    	return 12;
                                                    	break;
													case '4':
                                                    	return 13;
                                                    	break;
													case '5':
                                                    	return 14;
                                                    	break;
													case '6':
                                                    	return 15;
                                                    	break;
													case '7':
                                                    	return 16;
                                                    	break;
													case '8':
                                                    	return 17;
                                                    	break;
													case '9':
                                                    	return 18;
                                                    	break;
													default:
														return 30;
														break;
												}
												break;
											case 'b':
                                            	token2 = token2 + 2;
                                            	switch (token2[0]) {
                                                	case '0':
                                                    	return 19;
                                                    	break;
													case '1':
                                                    	return 20;
                                                    	break;
													case '2':
                                                    	return 21;
                                                    	break;
													case '3':
                                                    	return 22;
                                                    	break;
													case '4':
                                                    	return 23;
                                                    	break;
													case '5':
                                                    	return 24;
                                                    	break;
													case '6':
                                                    	return 25;
                                                    	break;
													case '7':
                                                    	return 26;
                                                    	break;
													case '8':
                                                    	return 27;
                                                    	break;
													case '9':
                                                    	return 28;
                                                    	break;
													default:
														return 31;
														break;
                                            	}
                                            	break;
											case 'c':
                                            	token2 = token2 + 1;
                                            	switch (token2[0]) {
                                                	case '1':
                                                    	return 29;
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


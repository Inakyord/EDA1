#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesCancion.h"
#include "menu.h"

int extraerContadores(int *iCuentas, int *iPerfiles, int *iPlaylists){
    FILE *archivoContadores;


    archivoContadores = fopen("contadores.txt", "r");
    if(archivoContadores == NULL){
        return 0;
    }
    fscanf(archivoContadores, "%i\n%i\n%i\n", iCuentas, iPerfiles, iPlaylists);
    fclose(archivoContadores);

    return 1;
}

int guardarContadores(int iCuentas, int iPerfiles, int iPlaylists){
    FILE *archivoContadores;

    archivoContadores = fopen("contadores.txt", "w");
    if(archivoContadores == NULL)
        return 0;
    fprintf(archivoContadores, "%i\n%i\n%i\n", iCuentas, iPerfiles, iPlaylists);
    fclose(archivoContadores);

    return 1;
}

int bajarArchivoCuentas(Cuenta *cuentas, int iCuentas){
    int i;
    FILE *archivoCuentas;

	archivoCuentas = fopen("cuentas.txt", "rb");
    if (archivoCuentas == NULL)
		return 0;


    for (i=0; i <= iCuentas; i++){
        crearCuenta(cuentas);
        fscanf(archivoCuentas, "%s %s %s %i %i %i %i %s %i %s %i %s %i %s %s %s %s %s %i %i %i %f %i", cuentas->duenoCuenta->nombre, cuentas->duenoCuenta->email, cuentas->duenoCuenta->contrasena, &(cuentas->duenoCuenta->edad), &(cuentas->duenoCuenta->dia), &(cuentas->duenoCuenta->mes), &(cuentas->duenoCuenta->ano), cuentas->duenoCuenta->genero, &(cuentas->duenoCuenta->numCuenta), cuentas->domicilio->calle, &(cuentas->domicilio->numeroDomicilio), cuentas->domicilio->colonia, &(cuentas->domicilio->CP), cuentas->domicilio->ciudad, cuentas->domicilio->pais, cuentas->tipoPlan->paquete, cuentas->tipoPlan->formaPago->formaPago, cuentas->tipoPlan->formaPago->numeroTarjeta, &(cuentas->tipoPlan->formaPago->mesVencimiento), &(cuentas->tipoPlan->formaPago->anoVencimiento), &(cuentas->tipoPlan->formaPago->CVV), &(cuentas->tipoPlan->formaPago->precio), &(cuentas->numCuenta));
        if (!strcmp(cuentas->tipoPlan->paquete, "Duo")){
            realloc(cuentas->perfiles, 2*sizeof(int));
            fscanf(archivoCuentas, " %i\n", &cuentas->perfiles[1]);
        } else if (!strcmp(cuentas->tipoPlan->paquete, "Familiar")){
            fscanf(archivoCuentas, " %i %i %i %i\n", &cuentas->perfiles[1], &cuentas->perfiles[2], &cuentas->perfiles[3], &cuentas->perfiles[4]);
        }else{
            realloc(cuentas->perfiles, 1*sizeof(int));
            fscanf(archivoCuentas, "\n");
        }
        descomprimir(cuentas->duenoCuenta->nombre);
        descomprimir(cuentas->duenoCuenta->email);
        descomprimir(cuentas->duenoCuenta->contrasena);
        descomprimir(cuentas->domicilio->calle);
        descomprimir(cuentas->domicilio->ciudad);
        descomprimir(cuentas->domicilio->colonia);
        descomprimir(cuentas->domicilio->pais);
        descomprimir(cuentas->tipoPlan->formaPago->numeroTarjeta);
        cuentas++;
    }
    fclose(archivoCuentas);

	return 1;
}

int bajarArchivoPerfiles(Perfil *perfiles, int iPerfiles){
    int i;
    FILE *archivoPerfiles;

	archivoPerfiles = fopen("perfiles.txt", "rb");
    if (archivoPerfiles == NULL)
		return 0;

    for (i=0; i<=iPerfiles; i++){
        fscanf(archivoPerfiles, "%s %s %s %i %i %i %i %s %i %i\n", (perfiles->nombre), (perfiles->email), (perfiles->contrasena), &(perfiles->edad), &(perfiles->dia), &(perfiles->mes), &(perfiles->ano), (perfiles->genero), &(perfiles->numCuenta), &(perfiles->numPerfil));
        descomprimir(perfiles->nombre);
        descomprimir(perfiles->email);
        descomprimir(perfiles->contrasena);
        perfiles++;
    }
	fclose(archivoPerfiles);

	return 1;
}

int bajarArchivoPlaylists(Playlist *playlists, int iPlaylists){
    int i, j;
    FILE *archivoPlaylists;

	archivoPlaylists = fopen("playlists.txt", "rb");
    if (archivoPlaylists == NULL)
		return 0;

	for (i = 0; i <= iPlaylists ; i++){
        crearPlaylist(playlists);
        fscanf(archivoPlaylists, "%s %i %s %i", (playlists->nombrePlaylist), &(playlists->numeroCanciones), (playlists->creador), &(playlists->descargas));
        playlists->canciones = crearCanciones(playlists->numeroCanciones);
        for(j = 0; j<playlists->numeroCanciones; j++){
            fscanf(archivoPlaylists, " %s %s %i", playlists->canciones[j].nombre, playlists->canciones[j].artista, &playlists->canciones[j].lanzada);
            descomprimir(playlists->canciones[j].nombre);
            descomprimir(playlists->canciones[j].artista);
        }
        fscanf(archivoPlaylists, "\n");
        descomprimir(playlists->nombrePlaylist);
        descomprimir(playlists->creador);

        playlists++;
	}

	fclose(archivoPlaylists);

	return 1;
}


void crearCuenta(Cuenta *nuevaCuenta){

    nuevaCuenta->duenoCuenta = (Perfil *) malloc(sizeof(Perfil));
    if (nuevaCuenta == NULL){
        printf("ERROR al crear perfil");
        exit(-1);
    }

    nuevaCuenta->domicilio = (Domicilio *) malloc(sizeof(Domicilio));
    if (nuevaCuenta == NULL){
        printf("ERROR al crear domicilio");
        exit(-1);
    }

    nuevaCuenta->tipoPlan = (Plan *) malloc(sizeof(Plan));
    if (nuevaCuenta == NULL){
        printf("ERROR al crear plan");
        exit(-1);
    }

    nuevaCuenta->tipoPlan->formaPago = (Pago *) malloc(sizeof(Pago));
    if (nuevaCuenta == NULL){
        printf("ERROR al crear pago");
        exit(-1);
    }

    nuevaCuenta->perfiles = (int *) malloc(5*sizeof(int));
    if (nuevaCuenta == NULL){
        printf("ERROR al crear plan");
        exit(-1);
    }
}

void crearPlaylist(Playlist *nuevaPlaylist){
    nuevaPlaylist->creador = (char *)malloc(30*sizeof(char));
    if (nuevaPlaylist->creador == NULL){
        printf("Error al crear creador playlist...");
        exit(-1);
    }
    nuevaPlaylist->nombrePlaylist = (char *)malloc(30*sizeof(char));
    if (nuevaPlaylist->nombrePlaylist == NULL){
        printf("Error al crear nombre playlist...");
        exit(-1);
    }
}

Cancion *crearCanciones(int numCanciones){
    int i;
    Cancion *canciones;

    canciones = (Cancion *) calloc(numCanciones, sizeof(Cancion));
    if (canciones == NULL){
        printf("Error al crear canciones");
        exit(-1);
    }
    for (i=0; i<numCanciones; i++){
        canciones[i].nombre = (char *) calloc(30, sizeof(char));
        if (canciones[i].nombre == NULL){
            printf("Error al crear nombre cancion");
            exit(-1);
        }
        canciones[i].artista = (char *) calloc(30, sizeof(char));
        if (canciones[i].artista == NULL){
            printf("Error al crear nombre artista");
            exit(-1);
        }
    }
    return canciones;
}

int validarEspacioCuentas(int iCuentas, int MAXcuentas){
	if (iCuentas < MAXcuentas)
		return 1;
	else
		return 0;
}
int validarEspacioPerfiles(int iPerfiles, int MAXperfiles){
	if (iPerfiles < MAXperfiles)
		return 1;
	else
		return 0;
}
int validarEspacioPlaylists(int iPlaylists, int MAXplaylists){
	if (iPlaylists < MAXplaylists)
		return 1;
	else
		return 0;
}


void capturarCuenta(Cuenta *unacuenta, Perfil *perfiles, int *iPerfiles){
	int i, tipo, auxiliar;
    char paquetes[6][16] = {"Gratis", "Mes-Prueba", "Individual", "Duo", "Familiar", "Universitario"};
    char tarjetas[4][18] = {"Visa", "MasterCard", "AmericanExpress", "PayPal"};
    int numCuenta = unacuenta->numCuenta;

    capturarPerfil(perfiles, iPerfiles, numCuenta);
    unacuenta->duenoCuenta = &perfiles[*iPerfiles];

    printf("\nDIRECCION\nCalle: ");
    fflush(stdin);
    gets(unacuenta->domicilio->calle);
    printf("Numero calle: ");
    scanf("%i", &unacuenta->domicilio->numeroDomicilio);
    printf("Colonia: ");
    fflush(stdin);
    gets(unacuenta->domicilio->colonia);
    printf("Codigo postal: ");
    scanf("%i", &unacuenta->domicilio->CP);
    printf("Ciudad: ");
    fflush(stdin);
    gets(unacuenta->domicilio->ciudad);
    printf("Pais: ");
    fflush(stdin);
    gets(unacuenta->domicilio->pais);
    printf("\nPAQUETE DESEADO");
    for(i=0; i<6; i++)
        printf("\n\t[%i] %s", i+1, paquetes[i]);
    printf("\nOpcion deseada: ");
    scanf("%i", &tipo);
    while(tipo<1 || tipo>6){
        printf("Opcion no valida, vuelva a ingresar una opcion valida.\nOpcion: ");
        scanf("%i", &tipo);
    }
    strcpy(unacuenta->tipoPlan->paquete, paquetes[tipo-1]);
    if (tipo==1 ||tipo==2){
        realloc(unacuenta->perfiles, 1*sizeof(int));
        unacuenta->perfiles[0] = unacuenta->duenoCuenta->numPerfil;
        strcpy(unacuenta->tipoPlan->formaPago->formaPago, "NO-APLICA");
        strcpy(unacuenta->tipoPlan->formaPago->numeroTarjeta, "NO-APLICA");
        unacuenta->tipoPlan->formaPago->mesVencimiento = 0;
        unacuenta->tipoPlan->formaPago->anoVencimiento = 0;
        unacuenta->tipoPlan->formaPago->CVV = 0;
        unacuenta->tipoPlan->formaPago->precio = 0;
    } else {
        printf("\nTIPO TARJETA");
        for(i=0; i<4; i++)
            printf("\n\t[%i] %s", i+1, tarjetas[i]);
        printf("\nOpcion deseada: ");
        scanf("%i", &i);
        while(i<1 || i>4){
            printf("Opcion no valida, vuelva a ingresar una opcion valida.\nOpcion: ");
            scanf("%i", &i);
        }
        strcpy(unacuenta->tipoPlan->formaPago->formaPago, tarjetas[i-1]);
        printf("\nDATOS TARJETA.\n");
        printf("Numero tarjeta: ");
        fflush(stdin);
        gets(unacuenta->tipoPlan->formaPago->numeroTarjeta);
        printf("Mes de vencimiento (nn): ");
        scanf("%i", &unacuenta->tipoPlan->formaPago->mesVencimiento);
        printf("Ano de vencimiento (nnnn): ");
        scanf("%i", &unacuenta->tipoPlan->formaPago->anoVencimiento);
        printf("Codigo de seguridad (CVV): ");
        scanf("%i", &unacuenta->tipoPlan->formaPago->CVV);
        switch (tipo){
            case 3:
                unacuenta->tipoPlan->formaPago->precio = 99;
                realloc(unacuenta->perfiles, 1*sizeof(int));
                unacuenta->perfiles[0] = unacuenta->duenoCuenta->numPerfil;
                break;
            case 4:
                unacuenta->tipoPlan->formaPago->precio = 129;
                realloc(unacuenta->perfiles, 2*sizeof(int));
                unacuenta->perfiles[0] = unacuenta->duenoCuenta->numPerfil;
                printf("Usted puede agregar 1 perfil mas.\nDesea hacerlo ahora?");
                printf("\n [1] Si, [2] No\nOpcion: ");
                scanf("%i", &i);
                while (i!=1 && i!=2){
                    printf("Opcion no valida, ingrese opcion valida: ");
                    scanf("%i", &i);
                }
                if (i == 1){
                    capturarPerfil(perfiles, iPerfiles, numCuenta);
                    unacuenta->perfiles[1] = *iPerfiles;
                }else
                    unacuenta->perfiles[1] = -1;
                break;
            case 5:
                unacuenta->tipoPlan->formaPago->precio = 149;
                realloc(unacuenta->perfiles, 5*sizeof(int));
                unacuenta->perfiles[0] = unacuenta->duenoCuenta->numPerfil;
                printf("\nPERFILES EXTRA\n");
                printf("Usted puede agregar 4 perfiles mas.\nDesea agregar alguno ahora?");
                printf("\n [1] Si, [2] No\nOpcion: ");
                scanf("%i", &auxiliar);
                while (auxiliar!=1 && auxiliar!=2){
                    printf("Opcion no valida, ingrese opcion valida: ");
                    scanf("%i", &auxiliar);
                }
                if (auxiliar == 1){
                    printf("Cuantos deseas agregar?: ");
                    scanf("%i", &auxiliar);
                    while (auxiliar<1 || auxiliar>4){
                        printf("No puedes agregar esa cantidad de perfiles.\n Opcion valida: ");
                        scanf("%i", &auxiliar);
                    }
                    for (i=1; i<=auxiliar; i++){
                        printf("\n\nPERFIL %i.\n", i);
                        capturarPerfil(perfiles, iPerfiles, numCuenta);
                        unacuenta->perfiles[i] = *iPerfiles;
                    }
                    for(i=auxiliar; i<4; i++){
                        unacuenta->perfiles[i+1] = -1;
                    }
                }
                break;
            case 6:
                unacuenta->tipoPlan->formaPago->precio = 49;
                realloc(unacuenta->perfiles, 1*sizeof(int));
                unacuenta->perfiles[0] = unacuenta->duenoCuenta->numPerfil;
                break;
        }

    }
}

int comprobarCorreo(Perfil *perfiles, int iPerfiles){
	int i;
	for (i=0; i<iPerfiles; i++)
        if (!strcmp(perfiles[iPerfiles].email, perfiles[i].email))
			return 0;

	return 1;
}

void capturarPerfil(Perfil *perfiles, int *iPerfiles, int numCuenta){
	int aux;
    char contra_1[30], contra_2[30];
    char generos[3][12] = {"Masculino", "Femenino", "No-Binario"};

    *iPerfiles += 1;

    perfiles[*iPerfiles].numCuenta = numCuenta;
    perfiles[*iPerfiles].numPerfil = *iPerfiles;

    printf("\nDATOS PERSONA.\n");
    printf("Nombre: ");
    fflush(stdin);
    gets(perfiles[*iPerfiles].nombre);
    printf("Email: ");
    fflush(stdin);
    gets(perfiles[*iPerfiles].email);
    while (!comprobarCorreo(perfiles, *iPerfiles)){
    	printf("\nEse correo ya esta utilizado!!!\nPor favor ingrese uno nuevo.\nEmail: ");
    	fflush(stdin);
    	gets(perfiles[*iPerfiles].email);
    }
    printf("Contrasena: ");
    fflush(stdin);
    gets(contra_1);
    printf("Comprobar contrasena: ");
    fflush(stdin);
    gets(contra_2);
    while (strcmp(contra_1, contra_2)){
        printf("Las contrasenas no coinciden!!!\n");
        printf("Vuelva a ingresar contrasena: ");
        fflush(stdin);
        gets(contra_1);
        printf("Vuelva a comprobar contrasena: ");
        fflush(stdin);
        gets(contra_2);
    }
    strcpy(perfiles[*iPerfiles].contrasena, contra_1);
    printf("Edad: ");
    scanf("%i", &perfiles[*iPerfiles].edad);
    printf("Dia de nacimiento (nn): ");
    scanf("%i", &perfiles[*iPerfiles].dia);
    printf("Mes de nacimiento (nn): ");
    scanf("%i", &perfiles[*iPerfiles].mes);
    printf("Ano de nacimiento (nnnn): ");
    scanf("%i", &perfiles[*iPerfiles].ano);
    printf("Genero. [1]Masculino    [2]Femenino     [3]No Binario\nOpcion: ");
    scanf("%i", &aux);
    while (aux<1 || aux>3){
        printf("Opcion no valida, ingrese otra.\nOpcion: ");
        scanf("%i", &aux);
    }
    strcpy(perfiles[*iPerfiles].genero, generos[aux-1]);
}

void capturarPlaylist(Playlist *playlist, char creador[]){
    int i;

    crearPlaylist(playlist);
    printf("\n Nombre playlist: ");
    fflush(stdin);
    gets(playlist->nombrePlaylist);
    printf(" Numero de canciones: ");
    scanf("%i", &playlist->numeroCanciones);
    playlist->canciones = crearCanciones(playlist->numeroCanciones);
    printf(" Numero de descargas: ");
    scanf("%i", &playlist->descargas);
    playlist->creador = creador;
    for (i=0; i<playlist->numeroCanciones; i++){
        printf("\n Cancion %i\n", i+1);
        printf(" Nombre cancion: ");
        fflush(stdin);
        gets(playlist->canciones[i].nombre);
        printf(" Nombre artista: ");
        fflush(stdin);
        gets(playlist->canciones[i].artista);
        printf(" Ano de lanzamiento: ");
        scanf("%i", &playlist->canciones[i].lanzada);
    }
}

void listarCuenta(Cuenta cuenta, Perfil *perfiles){
    int i;
    printf("\n\tCuenta [%i] ...\n", cuenta.duenoCuenta->numCuenta);
    printf("\tPerfil dueno.\n\t\tNombre: %s\n",cuenta.duenoCuenta->nombre);
	printf("\t\tEmail: %s\n",cuenta.duenoCuenta->email);
	printf("\t\tContrasena: %s\n",cuenta.duenoCuenta->contrasena);
	printf("\t\tEdad: %i\n",cuenta.duenoCuenta->edad);
	printf("\t\tDia: %i\n",cuenta.duenoCuenta->dia);
	printf("\t\tMes: %i\n",cuenta.duenoCuenta->mes);
	printf("\t\tAno: %i\n",cuenta.duenoCuenta->ano);
	printf("\t\tGenero: %s\n",cuenta.duenoCuenta->genero);
	printf("\tDomicilio.\n\t\tCalle: %s\n",cuenta.domicilio->calle);
	printf("\t\tNumero: %i\n",cuenta.domicilio->numeroDomicilio);
	printf("\t\tColonia: %s\n",cuenta.domicilio->colonia);
	printf("\t\tCP: %i\n",cuenta.domicilio->CP);
	printf("\t\tCiudad: %s\n",cuenta.domicilio->ciudad);
	printf("\t\tPais: %s\n",cuenta.domicilio->pais);
	printf("\tTipo de plan.\n\t\tPaquete: %s\n",cuenta.tipoPlan->paquete);
	printf("\t\tForma de pago: %s\n",cuenta.tipoPlan->formaPago->formaPago);
	printf("\t\tNumero de tarjeta: %s\n",cuenta.tipoPlan->formaPago->numeroTarjeta);
	printf("\t\tMes de vencimiento: %i\n",cuenta.tipoPlan->formaPago->mesVencimiento);
	printf("\t\tAno de vencimiento: %i\n",cuenta.tipoPlan->formaPago->anoVencimiento);
	printf("\t\tCVV: %i\n",cuenta.tipoPlan->formaPago->CVV);
	printf("\t\tPrecio: %3.2f\n",cuenta.tipoPlan->formaPago->precio);
	printf("\tOtros perfiles.\n");
	if(!strcmp(cuenta.tipoPlan->paquete, "Duo")){
        printf("\t\tperfil 1: %s\n", perfiles[cuenta.perfiles[1]].nombre);
	} else if (!strcmp(cuenta.tipoPlan->paquete, "Familiar")){
	    for (i=1; i<5; i++)
                printf("\t\tperfil %i: %s\n", i, perfiles[cuenta.perfiles[i]].nombre);
	} else
        printf("\t\tEn este plan no se tienen perfiles extra.\n");
}

void listarPerfil(Perfil perfil){
    printf("\n\tPerfil [%i]...\n", perfil.numPerfil);
    printf("\t\tNombre: %s\n", perfil.nombre);
    printf("\t\tEmail: %s\n", perfil.email);
    printf("\t\tContrasena: %s\n", perfil.contrasena);
    printf("\t\tEdad: %i\n", perfil.edad);
    printf("\t\tDia de nacimiento: %i\n", perfil.dia);
    printf("\t\tMes de nacimiento: %i\n", perfil.mes);
    printf("\t\tAno de nacimiento: %i\n", perfil.ano);
    printf("\t\tGenero: %s\n", perfil.genero);
    printf("\t\tNumero de cuenta: %i\n", perfil.numCuenta);
}

void listarPlaylist(Playlist playlist){
    int i;

    printf("\n Playlist \"%s\", creador: \"%s\", descargas: %i", playlist.nombrePlaylist, playlist.creador, playlist.descargas);
    for(i=0; i<playlist.numeroCanciones; i++){
        printf("\n\tCancion %i", i+1);
        printf("\n\t\t\"%s\"", playlist.canciones->nombre);
        printf("\n\t\tPor: %s", playlist.canciones->artista);
        printf("\n\t\tDe %i", playlist.canciones->lanzada);
        playlist.canciones++;
    }
    printf("\n\n");
}

int buscarCuenta(Cuenta *cuentas, char correo[], int iCuentas){
    int i;

    for (i=0; i<=iCuentas; i++){
        if(!strcmp(correo, cuentas[i].duenoCuenta->email))
            return cuentas[i].numCuenta;
    }

    return -1;
}

int buscarPerfil(Perfil *perfiles, char correo[], int iPerfiles){
    int i;

    for (i=0; i<=iPerfiles; i++){
        if(!strcmp(correo, perfiles[i].email))
            return perfiles[i].numPerfil;
    }

    return -1;
}


int checarContrasenaCuenta(Cuenta *cuentas, int iCuentas, int *numCuenta){
    char correo[30];
    char contra[30];
    int auxiliar;

    printf(" Cual es el correo de la cuenta?: ");
    fflush(stdin);
    gets(correo);
    auxiliar = buscarCuenta(cuentas, correo, iCuentas);
    if (auxiliar != -1){
        printf("\n Cual es la contrasena de la cuenta?: ");
        fflush(stdin);
        gets(contra);
        if(!strcmp(contra, cuentas[auxiliar].duenoCuenta->contrasena)){
            *numCuenta = auxiliar;
            return 1;
        }else{
            printf("\n La contrasena no coincide.\n");
            return 0;
        }
    }else{
        printf("\n No hay cuentas con ese correo.\n");
    }
        return 0;
}

int checarContrasenaPerfil(Perfil *perfiles, int iPerfiles, int *numPerfil){
    char correo[30];
    char contra[30];
    int auxiliar;

    printf(" Cual es el correo del perfil?: ");
    fflush(stdin);
    gets(correo);
    auxiliar = buscarPerfil(perfiles, correo, iPerfiles);
    if (auxiliar != -1){
        printf("\n Cual es la contrasena del perfil?: ");
        fflush(stdin);
        gets(contra);
        if(!strcmp(contra, perfiles[auxiliar].contrasena)){
            *numPerfil = auxiliar;
            return 1;
        }else{
            printf("\n La contrasena no coincide.\n");
            return 0;
        }
    }else{
        printf("\n No hay perfiles con ese correo.\n");
    }
        return 0;
}


void cambiarDatosCuenta(Cuenta *cuenta, Perfil *perfiles, int iPerfiles){
    int i, tipo, opcion, eleccion, aux;
    char contra_1[30], contra_2[30];
    char generos[3][12] = {"Masculino", "Femenino", "No-Binario"};
    char paquetes[6][16] = {"Gratis", "Mes de Prueba", "Individual", "Duo", "Familiar", "Universitario"};
    char tarjetas[4][18] = {"Visa", "MasterCard", "AmericanExpress", "PayPal"};

    do{
        opcion = Menu("\n - Menu Cambio Info Cuenta - \n\t1)Cambiar info dueno de la cuenta \n\t2)Cambiar info domicilio\n\t3)Cambiar info Plan\n\t4)Regresar\n Opcion: ", 4);
        switch (opcion){
            case 1:
                listarPerfil(*cuenta->duenoCuenta);
                do{
                    eleccion = Menu("\n ~ Cambio dueno cuenta ~\n\t1)Nombre\n\t2)Email\n\t3)Contrasena\n\t4)Edad\n\t5)Dia de nacimiento\n\t6)Mes\n\t7)Ano\n\t8)Genero\n\t9)Regresar\n Opcion: ", 9);
                    switch (eleccion){
                        case 1:
                            printf("Nombre: ");
                            fflush(stdin);
                            gets(cuenta->duenoCuenta->nombre);
                            break;

                        case 2:
                            printf("Email: ");
                            fflush(stdin);
                            gets(cuenta->duenoCuenta->email);
                            while (!comprobarCorreo(cuenta->duenoCuenta, iPerfiles)){
                                printf("\nEse correo ya esta utilizado!!!\nPor favor ingrese uno nuevo.\nEmail: ");
                                fflush(stdin);
                                gets(cuenta->duenoCuenta->email);
                            }
                            break;

                        case 3:
                            printf("Contrasena: ");
                            fflush(stdin);
                            gets(contra_1);
                            printf("Comprobar contrasena: ");
                            fflush(stdin);
                            gets(contra_2);
                            while (strcmp(contra_1, contra_2)){
                                printf("Las contrasenas no coinciden!!!\n");
                                printf("Vuelva a ingresar contrasena: ");
                                fflush(stdin);
                                gets(contra_1);
                                printf("Vuelva a comprobar contrasena: ");
                                fflush(stdin);
                                gets(contra_2);
                            }
                            strcpy(cuenta->duenoCuenta->contrasena, contra_1);
                            break;

                        case 4:
                            printf("Edad: ");
                            scanf("%i", &cuenta->duenoCuenta->edad);
                            break;

                        case 5:
                            printf("Dia de nacimiento (nn): ");
                            scanf("%i", &cuenta->duenoCuenta->dia);
                            break;

                        case 6:
                            printf("Mes de nacimiento (nn): ");
                            scanf("%i", &cuenta->duenoCuenta->mes);
                            break;

                        case 7:
                            printf("Ano de nacimiento (nnnn): ");
                            scanf("%i", &cuenta->duenoCuenta->ano);
                            break;

                        case 8:
                            printf("Genero. [1]Masculino    [2]Femenino     [3]No Binario\nOpcion: ");
                            scanf("%i", &aux);
                            while (aux<1 || aux>3){
                                printf("Opcion no valida, ingrese otra.\nOpcion: ");
                                scanf("%i", &aux);
                            }
                            strcpy(cuenta->duenoCuenta->genero, generos[aux-1]);
                            break;
                        }
                    }while (eleccion != 9);
                break;

            case 2:
                printf("\nNUEVA DIRECCION\nCalle: ");
                fflush(stdin);
                gets(cuenta->domicilio->calle);
                printf("Numero calle: ");
                scanf("%i", &cuenta->domicilio->numeroDomicilio);
                printf("Colonia: ");
                fflush(stdin);
                gets(cuenta->domicilio->colonia);
                printf("Codigo postal: ");
                scanf("%i", &cuenta->domicilio->CP);
                printf("Ciudad: ");
                fflush(stdin);
                gets(cuenta->domicilio->ciudad);
                printf("Pais: ");
                fflush(stdin);
                gets(cuenta->domicilio->pais);
                break;

            case 3:
                printf("\n ~ Datos nuevo plan ~\n");
                for(i=0; i<6; i++)
                    printf("\n\t[%i] %s", i+1, paquetes[i]);
                printf("\nOpcion deseada: ");
                scanf("%i", &tipo);
                while(tipo<1 || tipo>6){
                    printf("Opcion no valida, vuelva a ingresar una opcion valida.\nOpcion: ");
                    scanf("%i", &tipo);
                }
                strcpy(cuenta->tipoPlan->paquete, paquetes[tipo-1]);
                if (tipo==1 ||tipo==2){
                    realloc(cuenta->duenoCuenta, 1*sizeof(Perfil));
                    cuenta->duenoCuenta[0] = *cuenta->duenoCuenta;
                    strcpy(cuenta->tipoPlan->formaPago->formaPago, "NO APLICA");
                    strcpy(cuenta->tipoPlan->formaPago->numeroTarjeta, "NO APLICA");
                    cuenta->tipoPlan->formaPago->mesVencimiento = 0;
                    cuenta->tipoPlan->formaPago->anoVencimiento = 0;
                    cuenta->tipoPlan->formaPago->CVV = 0;
                    cuenta->tipoPlan->formaPago->precio = 0;
                }else {
                    printf("\nTIPO TARJETA");
                    for(i=0; i<4; i++)
                        printf("\n\t[%i] %s", i+1, tarjetas[i]);
                    printf("\nOpcion deseada: ");
                    scanf("%i", &i);
                    while(i<1 || i>4){
                        printf("Opcion no valida, vuelva a ingresar una opcion valida.\nOpcion: ");
                        scanf("%i", &i);
                    }
                    strcpy(cuenta->tipoPlan->formaPago->formaPago, tarjetas[i-1]);
                    printf("\nDATOS TARJETA.\n");
                    printf("Numero tarjeta: ");
                    fflush(stdin);
                    gets(cuenta->tipoPlan->formaPago->numeroTarjeta);
                    printf("Mes de vencimiento (nn): ");
                    scanf("%i", &cuenta->tipoPlan->formaPago->mesVencimiento);
                    printf("ano de vencimiento (nnnn): ");
                    scanf("%i", &cuenta->tipoPlan->formaPago->anoVencimiento);
                    printf("Codigo de seguridad (CVV): ");
                    scanf("%i", &cuenta->tipoPlan->formaPago->CVV);
                    switch(tipo){
                        case 3:
                            cuenta->tipoPlan->formaPago->precio = 99;
                            realloc(cuenta->duenoCuenta, 1*sizeof(Perfil));
                            cuenta->duenoCuenta[0] = *cuenta->duenoCuenta;
                            break;

                        case 4:
                            cuenta->tipoPlan->formaPago->precio = 129;
                            realloc(cuenta->duenoCuenta, 2*sizeof(Perfil));
                            cuenta->duenoCuenta[0] = *cuenta->duenoCuenta;
                            break;
                        case 5:
                            cuenta->tipoPlan->formaPago->precio = 149;
                            realloc(cuenta->duenoCuenta, 6*sizeof(Perfil));
                            cuenta->duenoCuenta[0] = *cuenta->duenoCuenta;
                            break;
                        case 6:
                            cuenta->tipoPlan->formaPago->precio = 49;
                            realloc(cuenta->duenoCuenta, 1*sizeof(Perfil));
                            cuenta->duenoCuenta[0] = *cuenta->duenoCuenta;
                            break;
                    }
                }
                break;
            }

        }while (opcion !=4);
}

void cambiarDatosPerfil(Perfil *perfil, Perfil *perfiles, int iPerfiles){
    int eleccion, aux;
    char contra_1[30], contra_2[30];
    char generos[3][12] = {"Masculino", "Femenino", "No-Binario"};

    listarPerfil(*perfil);
    do{
        eleccion = Menu("\n ~ Cambio perfil ~\n\t1)Nombre\n\t2)Email\n\t3)Contrasena\n\t4)Edad\n\t5)Dia de nacimiento\n\t6)Mes\n\t7)Ano\n\t8)Genero\n\t9)Regresar\n Opcion: ", 9);
        switch (eleccion){
            case 1:
                printf("Nombre: ");
                fflush(stdin);
                gets(perfil->nombre);
                break;

            case 2:
                printf("Email: ");
                fflush(stdin);
                gets(perfil->email);
                while (!comprobarCorreo(perfil, iPerfiles)){
                    printf("\nEse correo ya esta utilizado!!!\nPor favor ingrese uno nuevo.\nEmail: ");
                    fflush(stdin);
                    gets(perfil->email);
                }
                break;

            case 3:
                printf("Contrasena: ");
                fflush(stdin);
                gets(contra_1);
                printf("Comprobar contrasena: ");
                fflush(stdin);
                gets(contra_2);
                while (strcmp(contra_1, contra_2)){
                    printf("Las contrasenas no coinciden!!!\n");
                    printf("Vuelva a ingresar contrasena: ");
                    fflush(stdin);
                    gets(contra_1);
                    printf("Vuelva a comprobar contrasena: ");
                    fflush(stdin);
                    gets(contra_2);
                }
                strcpy(perfil->contrasena, contra_1);
                break;

            case 4:
                printf("Edad: ");
                scanf("%i", &perfil->edad);
                break;

            case 5:
                printf("Dia de nacimiento (nn): ");
                scanf("%i", &perfil->dia);
                break;

            case 6:
                printf("Mes de nacimiento (nn): ");
                scanf("%i", &perfil->mes);
                break;

            case 7:
                printf("Ano de nacimiento (nnnn): ");
                scanf("%i", &perfil->ano);
                break;

            case 8:
                printf("Genero. [1]Masculino    [2]Femenino     [3]No Binario\nOpcion: ");
                scanf("%i", &aux);
                while (aux<1 || aux>3){
                    printf("Opcion no valida, ingrese otra.\nOpcion: ");
                    scanf("%i", &aux);
                }
                strcpy(perfil->genero, generos[aux-1]);
                break;
            }
        }while (eleccion != 9);

}


void borrarPerfil(Cuenta *cuenta, Perfil *perfiles, int *iPerfiles, int iBorrar){

    strcpy(perfiles[cuenta->perfiles[iBorrar]].nombre, perfiles[*iPerfiles].nombre);
    strcpy(perfiles[cuenta->perfiles[iBorrar]].email, perfiles[*iPerfiles].email);
    strcpy(perfiles[cuenta->perfiles[iBorrar]].contrasena, perfiles[*iPerfiles].contrasena);
    perfiles[cuenta->perfiles[iBorrar]].edad = perfiles[*iPerfiles].edad;
    perfiles[cuenta->perfiles[iBorrar]].dia = perfiles[*iPerfiles].dia;
    perfiles[cuenta->perfiles[iBorrar]].mes = perfiles[*iPerfiles].mes;
    perfiles[cuenta->perfiles[iBorrar]].ano = perfiles[*iPerfiles].ano;
    strcpy(perfiles[cuenta->perfiles[iBorrar]].genero, perfiles[*iPerfiles].genero);
    perfiles[cuenta->perfiles[iBorrar]].numCuenta = perfiles[*iPerfiles].numCuenta;
    cuenta->perfiles[iBorrar] = -1;

    *iPerfiles-=1;

}

void gestionarPerfilesCuenta(Cuenta *cuenta, int numCuenta, Perfil *perfiles, int *iPerfiles){
    int i, eleccion, opcion, aux=0;

    printf("\n Tu cuenta es...\n");
    listarCuenta(*cuenta, perfiles);
    if(!strcmp(cuenta->tipoPlan->paquete, "Duo")){
        do{
            eleccion = Menu("\n ~ Menu Gestion Perfiles ~ \n\t1)Agregar perfil\n\t2)Eliminar perfil\n\t3)Regresrar\n Opcion: ", 3);
            switch (eleccion){
                case 1:
                    if(cuenta->perfiles[1] == -1){
                        printf("\n Tiene un perfil vacio desea agregarlo?\n 1)SI   2)NO\n Opcion: ");
                        scanf("%i", &opcion);
                        while (opcion<1 || opcion>2){
                            printf(" Opcion no valida, ingrese nuevamente.\n Opcion: ");
                            scanf("%i", &opcion);
                        }
                        if(opcion==1){
                            capturarPerfil(perfiles, iPerfiles, cuenta->numCuenta);
                            cuenta->perfiles[1] = *iPerfiles;
                        }
                    }else
                        printf("\n Todos sus perfiles estan llenos.\n");
                    break;

                case 2:
                    if(cuenta->perfiles[1] != -1){
                        borrarPerfil(cuenta, perfiles, iPerfiles, 1);
                    }
                    break;
            }
        }while (eleccion!=3);

    }else if(!strcmp(cuenta->tipoPlan->paquete, "Familiar")){
        do{
            eleccion = Menu("\n ~ Menu Gestion Perfiles ~ \n\t1)Agregar perfil\n\t2)Eliminar perfil\n\t3)Regresrar\n Opcion: ", 3);
            switch (eleccion){
                case 1:
                    for(i=1; i<5; i++)
                        if(cuenta->perfiles[i]==-1)
                            aux++;

                    if(aux>0){
                        printf("\n Tiene %i perfiles vacios desea agregar alguno?\n 1)SI   2)NO\n Opcion: ", aux);
                        scanf("%i", &opcion);
                        while (opcion<1 || opcion>aux){
                            printf(" Opcion no valida, ingrese nuevamente.\n Opcion: ");
                            scanf("%i", &opcion);
                        }
                        if(opcion==1){
                            printf(" Cuantos perfiles deseas agregar?: ");
                            scanf("%i", &opcion);
                            while(opcion<1 ||opcion>aux){
                                printf(" Opcion no valida, ingrese nuevamente.\n Opcion: ");
                                scanf("%i", &opcion);
                            }
                            for(i=5-aux; i<5-aux+opcion; i++){
                                capturarPerfil(perfiles, iPerfiles, numCuenta);
                                cuenta->perfiles[i] = *iPerfiles;
                            }
                        }else
                            printf("\n Sin cambio en perfiles.\n");

                    }else
                        printf("\n Todos sus perfiles estan llenos.\n");
                    break;

                case 2:
                    printf("\n Los perfiles");
                    aux=0;
                    for(i=1; i<5; i++)
                        if(cuenta->perfiles[i]!= -1){
                            aux++;
                            printf(" %i,", i);
                        }
                    printf(" estan llenos, cual quiere borrar?\n Opcion: ");
                    scanf("%i", &opcion);
                    while(opcion<5-aux || opcion>4){
                        printf(" Opcion no valida, ingrese nuevamente.\n Opcion: ");
                        scanf("%i", &opcion);
                    }
                    borrarPerfil(cuenta, perfiles, iPerfiles, opcion);
                    for(i=1; i<4; i++){
                        if(cuenta->perfiles[i]==-1 && cuenta->perfiles[i+1] != -1){
                            cuenta->perfiles[i] = cuenta->perfiles[i+1];
                            cuenta->perfiles[i+1] = -1;
                        }
                    }
                    break;
            }
        }while (eleccion!=3);

    }else
        printf("\nSu plan no cuenta con perfiles extra que gestionar.\n");
}



void Estad_1_porcentajeHombresYMujeres(Perfil *perfiles, int iPerfiles){
    int i;
    int hombres=0, mujeres=0, otros=0, total=0;
    float porcentajeHombres, porcentajeMujeres;

    for (i=0; i<=iPerfiles; i++){
        if (strcmp(perfiles[i].genero,"Masculino") == 0)
            hombres++;
        else if (strcmp(perfiles[i].genero,"Femenino") == 0)
            mujeres++;
        else
            otros++;
    }
    printf("\n\tHay registros de:\n\t\t%i Hombres\n\t\t%i Mujeres\n\t\t%i No especificado", hombres, mujeres, otros);
    total = hombres + mujeres + otros;
    porcentajeHombres = (hombres*100)/total;
    porcentajeMujeres = (mujeres*100)/total;
    printf("\n\n\t ~~ EL %.2f%% de los usuarios registrados son MUJERES mientras que el %.2f%% son HOMBRES ~~\n\n", porcentajeMujeres, porcentajeHombres);
}

void Estad_2_porcentajeCuentas(Cuenta *cuentas, int iCuentas){
    int i;
    int free=0, premium=0, total=0;
    float porcentajeFree, porcentajePremium;

    for (i=0; i<=iCuentas; i++){
        if (strcmp(cuentas[i].tipoPlan->paquete,"Gratis") == 0)
            free++;
        else if (strcmp(cuentas[i].tipoPlan->paquete, "Mes-Prueba") == 0)
            free++;
        else
            premium++;
    }
    printf("\n\tHay registros de:\n\t\t%i Cuentas Gratis\n\t\t%i Cuentas Premium", free, premium);
    total = free + premium;
    porcentajeFree = (free*100)/total;
    porcentajePremium = (premium*100)/total;
    printf("\n\n\t ~~ El %.2f%% de los usuarios registrados tienen CUENTAS GRATIS mientras que el %.2f%% tienen CUENTAS PREMIUM ~~\n\n", porcentajeFree, porcentajePremium);
}

void Estad_3_playlistsRegistradas(int iPlaylists){
    printf("\n\n\t ~~ Hay %i playlists registradas en la plataforma. ~~\n\n", iPlaylists+1);
}

void Estad_4_ingresosRegistrados(Cuenta *cuentas, int iCuentas){
    int i;
    float totalIngreso=0;

    for(i=0; i<=iCuentas; i++)
        totalIngreso+= cuentas[i].tipoPlan->formaPago->precio;
    printf("\n\t ~~ El ingreso mensual de la plataforma asciende a $%.2f MXN ~~\n\n", totalIngreso);

}

void Estad_5_metodoPago(Cuenta *cuentas,int iCuentas){
    int i, Visa = 0, MasterCard = 0, AmericanExpress = 0, Paypal = 0;
    printf("\n\n\t El metodo mas usual de pago:");
    for(i=0; i<=iCuentas;i++){
        if(!strcmp("Visa",cuentas[i].tipoPlan->formaPago->formaPago))
            Visa++;
        else if(!strcmp("MasterCard",cuentas[i].tipoPlan->formaPago->formaPago))
            MasterCard++;
        else if(!strcmp("AmericanExpress",cuentas[i].tipoPlan->formaPago->formaPago))
            AmericanExpress++;
        else if(!strcmp("PayPal",cuentas[i].tipoPlan->formaPago->formaPago))
            Paypal++;
    }
    if(Visa>=MasterCard && Visa>=AmericanExpress && Visa>=Paypal)
        printf("\n\t ~~ Visa ~~");
    if(MasterCard>=Visa && MasterCard>=AmericanExpress && MasterCard>=Paypal)
        printf("\n\t ~~ MasterCard ~~");
    if(AmericanExpress>=Visa && AmericanExpress>=MasterCard && AmericanExpress>=Paypal)
        printf("\n\t ~~ AmericanExpress ~~");
    if(Paypal>=Visa && Paypal>=MasterCard && Paypal>=AmericanExpress)
        printf("\n\t ~~ Paypal ~~");
    printf("\n\n");
}

void Estad_6_edadPromedio(Perfil *perfiles,int iPerfiles){
    int i;
    float edadprom = 0;
    for(i=0; i<=iPerfiles; i++){
        edadprom = edadprom + perfiles[i].edad;
    }
    edadprom = edadprom/(iPerfiles+1);
    printf("\n\n\t ~~ Edad promedio de los usuarios que usan Spotify: %2.1f ~~\n\n", edadprom);
}

void Estad_7_usuariosRegistrados(int iPerfiles){
    printf("\n\n\t ~~ El numero de usuarios registrados es: %i ~~\n\n",iPerfiles+1);
}

void Estad_8_cuentaMasCostosa(Cuenta *cuentas, int iCuentas){
    int i;
    float mayorCosto=0;

    for (i=0; i<iCuentas; i++){
        if(cuentas[i].tipoPlan->formaPago->precio>mayorCosto)
            mayorCosto = cuentas[i].tipoPlan->formaPago->precio;
    }
    printf("\n\tLa cuenta mas costosa registrada es: ");
    for (i=0; i<iCuentas; i++){
    if ((cuentas[i].tipoPlan->formaPago->precio)== mayorCosto)
            printf("\n\n\t~~ %s\t\t%s\t\t%.2f ~~\n\n", cuentas[i].duenoCuenta->nombre, cuentas[i].duenoCuenta->email, cuentas[i].tipoPlan->formaPago->precio);
        }
    }

void Estad_9_playlistsReistrados(Playlist *playlists, int iPlaylists){
    int i, x=0, xp;

    printf("\n\tTotal de playlists: %i", iPlaylists+1);

    for(i=0; i<=iPlaylists; i++)
        x = x + playlists[i].numeroCanciones;
    xp = x/(iPlaylists+1);
    printf("\n\t ~~ El numero total de canciones es de: %i ~~", x);
    printf("\n\t ~~ El promedio de canciones por playlist es: %i ~~\n\n", xp);

}

void Estad_10_masCanciones(Playlist *playlists, int iPlaylists){
    int i, mayorPlay = 0, aux;
    for (i=0; i<=iPlaylists; i++){
        if(playlists[i].numeroCanciones > mayorPlay){
            mayorPlay = playlists[i].numeroCanciones;
            aux = i;
        }
    }
    printf("\n\t ~~ La playist con mas canciones es \"%s\" del perfil %s y tiene:  %i canciones ~~\n\n", playlists[aux].nombrePlaylist, playlists[aux].creador, mayorPlay);
}

void Estad_11_epoca(Playlist *playlists, int iPlaylist){
    int i, j, total=0, totCanciones=0;
    for (i=0; i<=iPlaylist; i++){
        for (j=0; j<playlists[i].numeroCanciones; j++){
            total += playlists[i].canciones[j].lanzada;
            totCanciones++;
        }
    }
    printf("\n\t ~~ En promedio las canciones que se escuchan se lanzaron en: %i ~~\n\n", total/totCanciones);
}


int subirArchivoCuentas(Cuenta *cuentas, int iCuentas){
    int i;
    FILE *archivoCuentas;

	archivoCuentas = fopen("cuentas.txt", "wb");
	if (archivoCuentas == NULL)
		return 0;


	for (i = 0; i <= iCuentas ; i++){
        comprimir(cuentas->duenoCuenta->nombre);
        comprimir(cuentas->duenoCuenta->email);
        comprimir(cuentas->duenoCuenta->contrasena);
        comprimir(cuentas->domicilio->calle);
        comprimir(cuentas->domicilio->ciudad);
        comprimir(cuentas->domicilio->colonia);
        comprimir(cuentas->domicilio->pais);
        comprimir(cuentas->tipoPlan->formaPago->numeroTarjeta);
        if(!strcmp(cuentas->tipoPlan->paquete, "Duo"))
            fprintf(archivoCuentas, "%s %s %s %i %i %i %i %s %i %s %i %s %i %s %s %s %s %s %i %i %i %3.2f %i %i\n", cuentas->duenoCuenta->nombre, cuentas->duenoCuenta->email, cuentas->duenoCuenta->contrasena, cuentas->duenoCuenta->edad, cuentas->duenoCuenta->dia, cuentas->duenoCuenta->mes, cuentas->duenoCuenta->ano, cuentas->duenoCuenta->genero, cuentas->duenoCuenta->numCuenta, cuentas->domicilio->calle, cuentas->domicilio->numeroDomicilio, cuentas->domicilio->colonia, cuentas->domicilio->CP, cuentas->domicilio->ciudad, cuentas->domicilio->pais, cuentas->tipoPlan->paquete, cuentas->tipoPlan->formaPago->formaPago, cuentas->tipoPlan->formaPago->numeroTarjeta, cuentas->tipoPlan->formaPago->mesVencimiento, cuentas->tipoPlan->formaPago->anoVencimiento, cuentas->tipoPlan->formaPago->CVV, cuentas->tipoPlan->formaPago->precio, cuentas->numCuenta, cuentas->perfiles[1]);
		else if (!strcmp(cuentas->tipoPlan->paquete, "Familiar"))
            fprintf(archivoCuentas, "%s %s %s %i %i %i %i %s %i %s %i %s %i %s %s %s %s %s %i %i %i %3.2f %i %i %i %i %i\n", cuentas->duenoCuenta->nombre, cuentas->duenoCuenta->email, cuentas->duenoCuenta->contrasena, cuentas->duenoCuenta->edad, cuentas->duenoCuenta->dia, cuentas->duenoCuenta->mes, cuentas->duenoCuenta->ano, cuentas->duenoCuenta->genero, cuentas->duenoCuenta->numCuenta, cuentas->domicilio->calle, cuentas->domicilio->numeroDomicilio, cuentas->domicilio->colonia, cuentas->domicilio->CP, cuentas->domicilio->ciudad, cuentas->domicilio->pais, cuentas->tipoPlan->paquete, cuentas->tipoPlan->formaPago->formaPago, cuentas->tipoPlan->formaPago->numeroTarjeta, cuentas->tipoPlan->formaPago->mesVencimiento, cuentas->tipoPlan->formaPago->anoVencimiento, cuentas->tipoPlan->formaPago->CVV, cuentas->tipoPlan->formaPago->precio, cuentas->numCuenta, cuentas->perfiles[1], cuentas->perfiles[2], cuentas->perfiles[3], cuentas->perfiles[4]);
		else
            fprintf(archivoCuentas, "%s %s %s %i %i %i %i %s %i %s %i %s %i %s %s %s %s %s %i %i %i %3.2f %i\n", cuentas->duenoCuenta->nombre, cuentas->duenoCuenta->email, cuentas->duenoCuenta->contrasena, cuentas->duenoCuenta->edad, cuentas->duenoCuenta->dia, cuentas->duenoCuenta->mes, cuentas->duenoCuenta->ano, cuentas->duenoCuenta->genero, cuentas->duenoCuenta->numCuenta, cuentas->domicilio->calle, cuentas->domicilio->numeroDomicilio, cuentas->domicilio->colonia, cuentas->domicilio->CP, cuentas->domicilio->ciudad, cuentas->domicilio->pais, cuentas->tipoPlan->paquete, cuentas->tipoPlan->formaPago->formaPago, cuentas->tipoPlan->formaPago->numeroTarjeta, cuentas->tipoPlan->formaPago->mesVencimiento, cuentas->tipoPlan->formaPago->anoVencimiento, cuentas->tipoPlan->formaPago->CVV, cuentas->tipoPlan->formaPago->precio, cuentas->numCuenta);

		cuentas++;
	}
	fflush(archivoCuentas);
	fclose(archivoCuentas);
	return 1;
}

int subirArchivoPerfiles(Perfil *perfiles, int iPerfiles){
    int i;
    FILE *archivoPerfiles;

	archivoPerfiles = fopen("perfiles.txt", "wb");
	if (archivoPerfiles == NULL)
		return 0;

	for (i = 0; i <= iPerfiles ; i++){
    comprimir(perfiles->nombre);
    comprimir(perfiles->email);
    comprimir(perfiles->contrasena);
    fprintf(archivoPerfiles, "%s %s %s %i %i %i %i %s %i %i\n", perfiles->nombre, perfiles->email, perfiles->contrasena, perfiles->edad, perfiles->dia, perfiles->mes, perfiles->ano, perfiles->genero, perfiles->numCuenta, perfiles->numPerfil);
		perfiles++;
	}
	fflush(archivoPerfiles);
	fclose(archivoPerfiles);
	return 1;
}

int subirArchivoPlaylists(Playlist *playlists, int iPlaylists){
    int i, j;
    FILE *archivoPlaylists;

	archivoPlaylists = fopen("playlists.txt", "wb");
	if (archivoPlaylists == NULL)
		return 0;


	for (i = 0; i <= iPlaylists ; i++){
        comprimir(playlists->nombrePlaylist);
        comprimir(playlists->creador);
		fprintf(archivoPlaylists, "%s %i %s %i", (playlists->nombrePlaylist), playlists->numeroCanciones, (playlists->creador), playlists->descargas);
		for (j=0; j<playlists->numeroCanciones; j++){
            comprimir(playlists->canciones->nombre);
            comprimir(playlists->canciones->artista);
            fprintf(archivoPlaylists, " %s %s %i", playlists->canciones->nombre, playlists->canciones->artista, playlists->canciones->lanzada);
            playlists->canciones++;
		}
		fprintf(archivoPlaylists, "\n");
		playlists++;
	}
	fflush(archivoPlaylists);
	fclose(archivoPlaylists);
	return 1;
}


void liberarMDCuenta(Cuenta *unacuenta){
    free(unacuenta->perfiles);
    free(unacuenta->tipoPlan->formaPago);
    free(unacuenta->tipoPlan);
    free(unacuenta->domicilio);
    free(unacuenta->duenoCuenta);
    free(unacuenta);

    unacuenta = NULL;
}

void liberarMDPerfil(Perfil *unperfil){
    free(unperfil);
    unperfil = NULL;
}

void liberarMDPlaylist(Playlist *unaplaylist){
    free(unaplaylist->creador);
    free(unaplaylist->nombrePlaylist);
    free(unaplaylist->canciones);
    free(unaplaylist);
    unaplaylist = NULL;
}

void liberarMDCancion(Cancion *canciones, int numCanciones){
    int i;
    for(i=0; i<numCanciones; i++){
        free(canciones[i].nombre);
        free(canciones[i].artista);
    }
    free(canciones);
}

void comprimir(char *frase){
    int i;
    for (i=0; i<strlen(frase); i++){
        if(frase[i] == ' ')
            frase[i] = '}';
    }
}

void descomprimir(char *frase){
    int i;
    for (i=0; i<strlen(frase); i++){
        if(frase[i] == '}')
            frase[i] = ' ';
    }
}

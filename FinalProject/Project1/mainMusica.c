#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "funcionesCancion.h"

#define MAXcuentas 20
#define MAXperfiles 35
#define MAXplaylists 40

int main(){
	int i, opcion, iCuentas, iPerfiles, iPlaylists, numCuenta, numPerfil;

	if (!extraerContadores(&iCuentas, &iPerfiles, &iPlaylists)){
        printf("No se pudo acceder a las variables de cuentas, perfiles, y playlists");
        return -1;
	}

	Cuenta *cuentas;
	Perfil *perfiles;
	Playlist *playlists;

	cuentas = (Cuenta *) malloc(MAXcuentas*sizeof(Cuenta));
	if(cuentas == NULL){
        printf("Error al crear cuentas...");
        return -1;
	}
	perfiles = (Perfil *) malloc(MAXperfiles*sizeof(Perfil));
	if(perfiles == NULL){
        printf("Error al crear perfiles...");
        return -1;
	}
	playlists = (Playlist *) malloc(MAXplaylists*sizeof(Playlist));
	if(playlists == NULL){
        printf("Error al crear playlists...");
        return -1;
	}

	if (!bajarArchivoCuentas(cuentas, iCuentas)){
        printf("\n\n No se pudieron leer las cuentas.\n\n");
        return -1;
	}
	if (!bajarArchivoPerfiles(perfiles, iPerfiles)){
        printf("\n\n No se pudieron leer los perfiles.\n\n");
        return -1;
	}
	if (!bajarArchivoPlaylists(playlists, iPlaylists)){
        printf("\n\n No se pudieron leer las playlists.\n\n");
        return -1;
	}

	do{
		opcion = Menu("\n - STREAMING DE MUSICA - \n\t1)Agregar Cuenta\n\t2)Listar Cuentas\n\t3)Listar Perfiles\n\t4)Listar Playlists\n\t5)Acceder Cuenta\n\t6)Acceder Perfil\n\t7)Generar Estadisticas\n\t8)Salir\n Opcion: ", 8);
		switch (opcion){
			case 1:
				if(validarEspacioCuentas(iCuentas, MAXcuentas) && validarEspacioPerfiles(iPerfiles+5, MAXperfiles)){
					iCuentas++;
					crearCuenta(&cuentas[iCuentas]);
					cuentas[iCuentas].numCuenta = iCuentas;
					capturarCuenta(&(cuentas[iCuentas]), perfiles, &iPerfiles);
				}else
					printf("\n\n Ya no hay espacio para mas cuentas o perfiles en el servidor.\n");
				break;

			case 2:
			    if (iCuentas == -1)
                    printf("\n No hay cuentas existentes.\n");
			    else{
			        for (i=0; i<=iCuentas; i++)
                        listarCuenta(cuentas[i], perfiles);
			    }
				break;

			case 3:
			    if (iPerfiles == -1)
                    printf("\n No hay perfiles existentes.\n");
                else{
                    for (i=0; i<=iPerfiles; i++)
                        listarPerfil(perfiles[i]);
                }
				break;

			case 4:
			    if (iPlaylists == -1)
                    printf("\n No hay playlists existentes.\n");
                else{
                    for (i=0; i<=iPlaylists; i++)
                        listarPlaylist(playlists[i]);
                }
			    break;

            case 5:
				if (checarContrasenaCuenta(&cuentas[0], iCuentas, &numCuenta)){
					do{
						opcion = Menu("\n - Menu Cuenta - \n\t1)Mostrar datos\n\t2)Cambiar datos\n\t3)Administrar perfiles\n\t4)Regresar\n Opcion: ", 4);
						switch (opcion){
							case 1:
								listarCuenta(cuentas[numCuenta], perfiles);
								break;

							case 2:
								cambiarDatosCuenta(&cuentas[numCuenta], perfiles, iPerfiles);
								break;

							case 3:
								gestionarPerfilesCuenta(&cuentas[numCuenta], numCuenta, perfiles, &iPerfiles);
								break;
						}
					}while (opcion !=4);
				}
				break;

			case 6:
				if (checarContrasenaPerfil(&perfiles[0], iPerfiles, &numPerfil)){
					do{
						opcion = Menu("\n - Menu Perfil - \n\t1)Mostrar datos\n\t2)Cambiar datos\n\t3)Crear Playlist\n\t4)Regresar\n Opcion: ", 4);
						switch (opcion){
							case 1:
								listarPerfil(perfiles[numPerfil]);
								break;

							case 2:
								cambiarDatosPerfil(&perfiles[numPerfil], perfiles, iPerfiles);
								break;

							case 3:
                                if(validarEspacioPlaylists(iPlaylists, MAXplaylists)){
                                    iPlaylists++;
                                    capturarPlaylist(&playlists[iPlaylists], perfiles[numPerfil].email);
                                }else
                                    printf("\n No hay espacio en el servidor para crear mas playlists.\n");
								break;
						}
					}while (opcion !=4);
				}
				break;

			case 7:
				do{
                    opcion = Menu("\n - Estadisticas - \n\t1)Porcentaje de hombres y mujeres\n\t2)Porcentaje de cuentas premium y cuentas free\n\t3)Cantidad de playlist registradas\n\t4)Ingresos economicos\n\t5)Forma de pago usada con mayor frecuencia\n\t6)Edad promedio de los usuarios aplicados\n\t7)Numero de usuarios registrados\n\t8)Cuentas mas costosas registradas\n\t9)Promedio del numero de canciones en Playlists\n\t10)Playlist con mas canciones\n\t11)Epoca canciones\n\t12)Salir\n Opcion: ", 12);
                    switch (opcion){
                    case 1:
                        if (iPerfiles>-1)
                            Estad_1_porcentajeHombresYMujeres(perfiles,iPerfiles);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 2:
                        if (iCuentas>-1)
                            Estad_2_porcentajeCuentas(cuentas,iCuentas);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 3:
                        if (iPlaylists>-1)
                            Estad_3_playlistsRegistradas(iPlaylists);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 4:
                        if (iCuentas>-1)
                            Estad_4_ingresosRegistrados(cuentas,iCuentas);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 5:
                        if (iCuentas>-1)
                            Estad_5_metodoPago(cuentas, iCuentas);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 6:
                        if (iPerfiles>-1)
                            Estad_6_edadPromedio(perfiles, iPerfiles);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 7:
                        if (iPerfiles>-1)
                            Estad_7_usuariosRegistrados(iPerfiles);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 8:
                        if (iCuentas>-1)
                            Estad_8_cuentaMasCostosa(cuentas,iCuentas);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 9:
                        if (iPlaylists>-1)
                            Estad_9_playlistsReistrados(playlists, iPlaylists);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 10:
                        if (iPlaylists>-1)
                            Estad_10_masCanciones(playlists, iPlaylists);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    case 11:
                        if (iPlaylists>-1)
                            Estad_11_epoca(playlists, iPlaylists);
                        else
                            printf("\n No hay datos registrados...\n");
                        break;
                    }
			    }while(opcion != 12);
			    break;
		}
	}while(opcion != 8);

	subirArchivoCuentas(cuentas, iCuentas);
	subirArchivoPerfiles(perfiles, iPerfiles);
	subirArchivoPlaylists(playlists, iPlaylists);

	guardarContadores(iCuentas, iPerfiles, iPlaylists);

	for (i=0; i<=iCuentas; i++)
        liberarMDCuenta(&cuentas[i]);

    for (i=0; i<=iPerfiles; i++)
        liberarMDPerfil(&perfiles[i]);

    for (i=0; i<=iPlaylists; i++){
        liberarMDPlaylist(&playlists[i]);
    }
	return 0;
}

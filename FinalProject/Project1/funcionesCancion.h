#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nombre[30];
	char email[30];
	char contrasena[30];
	int edad;
	int dia;
	int mes;
	int ano;
	char genero[30];
	int numCuenta;
	int numPerfil;
} Perfil;

typedef struct{
	char calle[30];
	int numeroDomicilio;
	char colonia[30];
	int CP;
	char ciudad[30];
	char pais[30];
} Domicilio;

typedef struct{
	char formaPago[30];
	char numeroTarjeta[30];
	int mesVencimiento;
	int anoVencimiento;
	int CVV;
	float precio;
} Pago;

typedef struct{
	char paquete[30];
	Pago *formaPago;
} Plan;

typedef struct{
	Perfil *duenoCuenta;
	Domicilio *domicilio;
	Plan *tipoPlan;
	int *perfiles;
	int numCuenta;
} Cuenta;

typedef struct{
    char *nombre;
    char *artista;
    int lanzada;
}Cancion;

typedef struct{
	char *nombrePlaylist;
	int numeroCanciones;
	char *creador;
	int descargas;
	Cancion *canciones;
} Playlist;


int extraerContadores(int *iCuentas, int *iPerfiles, int *iPlaylists);
int guardarContadores(int iCuentas, int iPerfiles, int iPlaylists);

int bajarArchivoCuentas(Cuenta *cuentas, int iCuentas);
int bajarArchivoPerfiles(Perfil *perfiles, int iPerfiles);
int bajarArchivoPlaylists(Playlist *playlists, int iPlaylists);

void crearCuenta(Cuenta *nuevaCuenta);
void crearPlaylist(Playlist *nuevaPlaylist);
Cancion *crearCanciones(int numCanciones);

int validarEspacioCuentas(int iCuentas, int MAXcuentas);
int validarEspacioPerfiles(int iPerfiles, int MAXperfiles);
int validarEspacioPlaylists(int iPlaylists, int MAXplaylists);

int comprobarCorreo(Perfil *perfiles, int iPerfiles);

void capturarCuenta(Cuenta *unacuenta, Perfil *perfiles, int *iPerfiles);
void capturarPerfil(Perfil *perfiles, int *iPerfiles, int numCuenta);
void capturarPlaylist(Playlist *playlist, char creador[]);

void listarCuenta(Cuenta cuenta, Perfil *perfiles);
void listarPerfil(Perfil perfil);
void listarPlaylist(Playlist playlist);

int buscarCuenta(Cuenta *cuentas, char correo[], int iCuentas);
int buscarPerfil(Perfil *perfiles, char correo[], int iPerfiles);

int checarContrasenaCuenta(Cuenta *cuentas, int iCuentas, int *numCuenta);
int checarContrasenaPerfil(Perfil *perfiles, int iPerfiles, int *numPerfil);

void cambiarDatosCuenta(Cuenta *cuenta, Perfil *perfiles, int iPerfiles);
void cambiarDatosPerfil(Perfil *perfil, Perfil *perfiles, int iPerfiles);
void borrarPerfil(Cuenta *cuenta, Perfil *perfiles, int *iPerfiles, int Borrar);
void gestionarPerfilesCuenta(Cuenta *cuentas, int numCuenta, Perfil *perfiles, int *iPerfiles);

void Estad_1_porcentajeHombresYMujeres(Perfil *perfiles, int iPerfiles);
void Estad_2_porcentajeCuentas(Cuenta *cuentas, int iCuentas);
void Estad_3_playlistsRegistradas(int iPlaylists);
void Estad_4_ingresosRegistrados(Cuenta *cuentas, int iCuentas);
void Estad_5_metodoPago(Cuenta *cuentas,int iCuentas);
void Estad_6_edadPromedio(Perfil *perfiles,int iPerfiles);
void Estad_7_usuariosRegistrados(int iPerfiles);
void Estad_8_cuentaMasCostosa(Cuenta *cuentas, int iCuentas);
void Estad_9_playlistsReistrados(Playlist *playlists, int iPlaylists);
void Estad_10_masCanciones(Playlist *playlists, int iPlaylists);
void Estad_11_epoca(Playlist *playlists, int iPlaylists);

int subirArchivoCuentas(Cuenta *cuentas, int iCuentas);
int subirArchivoPerfiles(Perfil *perfiles, int iPerfiles);
int subirArchivoPlaylists(Playlist *playlists, int iPlaylists);

void liberarMDCuenta(Cuenta *cuenta);
void liberarMDPerfil(Perfil *perfil);
void liberarMDPlaylist(Playlist *playlist);
void liberarMDCancion(Cancion *canciones, int numCanciones);

void comprimir(char *frase);
void descomprimir(char *frase);

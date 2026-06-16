#ifndef GENEROS_H_INCLUDED
#define GENEROS_H_INCLUDED

#define ARCHIVO_GENEROS "generos.dat"
#define MAX_GENEROS 20
#define ACTIVO 1
#define INACTIVO 0

typedef struct{
 int idGenero;
 char nombre[50];
 char descripcion[150];
 int activo;
}stGenero;

int cargarGen(stGenero lista[], int *cantidad);
int guardarGen(stGenero lista[],int cantidad);
void altaGen(stGenero lista[],int *cantidad);
void bajaGen(stGenero lista[],int cantidad,int cantContenido,int idGenContenido[]);
void modificarGen(stGenero lista[],int cantidad);
void consultarGen(stGenero lista[],int cantidad);
void listarGen(stGenero lista[],int cantidad);
int buscarGenXid(stGenero lista[], int cantidad, int id);
int buscarGenXNombre(stGenero lista[], int cantidad, const char nombre[]);
int generarIDGEN(stGenero lista[],int cantidad);

#endif

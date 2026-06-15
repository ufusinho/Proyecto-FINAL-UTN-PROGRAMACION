#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Generos.h"

void limpiarBuffer(void)
{
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
}
///CARGAR Y GUARDAR///
int cargarGen(stGenero lista[],int cantidad)
{
    FILE *archi = fopen(ARCHIVO_GENEROS,"rb");
    cantidad = -1;

    if(archi == NULL){
        printf("El archivo no se puede abrir");
        return 0;
    }else{
        while(cantidad < MAX_GENEROS && fread(&lista[cantidad], sizeof(stGenero), 1 , archi)>0){
              cantidad++;
        }
        fclose(archi);
    }
 return 0;
}
int guardarGen(stGenero lista[],int cantidad)
{
    FILE *archi = fopen(ARCHIVO_GENEROS,"rb");
    cantidad = 0;

    if(archi == NULL){
        printf("El archivo no se puede abrir");
        return -1;
    }else{
        fwrite(lista,sizeof(stGenero),cantidad,archi);
        fclose(archi);
    }

 return 0;
}
///ABMCyL///
void altaGen(stGenero lista[],int cantidad)
{
    stGenero nuevo;

    if(cantidad >= MAX_GENEROS){
        printf("Llegaste al limite de generos");
        return;
    }
    printf("\n ALTA DE NUEVO GENERO \n");
    do{
        printf("Nombre: ");
        fgets(nuevo.nombre,sizeof(nuevo.nombre),stdin);
        if(strlen(nuevo.nombre) == 0){
            printf("ERROR: EL NOMBRE ESTA VACIO");
            continue;
        }
    } while (strlen(nuevo.nombre) == 0);
}
void bajaGen(stGenero lista[],int cantidad,int cantContenido,int idGenContenido[])
{
    int id;
    int pos;
    int cont = 0;

    printf("\nBAJA DE GENERO\n");
    listarGen(lista,cantidad);
    limpiarBuffer();
    printf("Ingrese el ID del genero para poder darlo de baja: ");
    scanf("%d",&id);

    pos = buscarGenXid(lista,cantidad,id);
    if(pos == -1 ||lista[pos].activo == INACTIVO){
        printf("Genero no encontrado o ya esta dado de baja \n");
        return ;
    }
    for(int i = 0;i<cantContenido;i++){
        if(idGenContenido[i] == id){
            cont = 1;
            return;
        }
    }
    if(cont){
        printf("No es posible darlo de baja, hay contenido activo con este genero\n");
        return;
    }
    lista[pos].activo = INACTIVO;
    printf("El genero %s fue dado de baja\n",lista[pos].nombre);
}
void modificarGen(stGenero lista[],int cantidad)
{
    int id;
    int pos;
    int idXDupl;
    char nuevoNombre[30];
    char nuevaDesc[200];

    printf("\n MODIFICACION DE GENERO\n");
    listarGen(lista, cantidad);

    printf("Ingrese el ID del genero que desee modificar: ");
    scanf("%d",&id);
    limpiarBuffer();

    pos=buscarGenXid(lista,cantidad,id);
    if(pos == -1 || lista[pos].activo == INACTIVO){
        printf("Genero no encontrado/inactivo\n");
        return;
    }
    printf("Nombre actual: %s\n",lista[pos].nombre);
    printf("Nuevo nombre: \n");
    fgets(nuevoNombre, sizeof(nuevoNombre), stdin);

    if (strlen(nuevoNombre) > 0) {
        idXDupl = buscarGenXNombre(lista, cantidad, nuevoNombre);
        if (idXDupl != -1 && idXDupl != pos) {
            printf("Ya existe otro genero con ese nombre. Modificacion cancelada.\n");
            return;
        }
        strcpy(lista[pos].nombre, nuevoNombre);

    printf("Descripcion actual: %s\n", lista[pos].descripcion);
    printf("Nueva descripcion (Enter para no cambiar): ");
    fgets(nuevaDesc, sizeof(nuevaDesc), stdin);

    if (strlen(nuevaDesc) > 0)
        strcpy(lista[pos].descripcion, nuevaDesc);

    printf("Genero modificado correctamente.\n");
    }

}
void consultarGen(stGenero lista[],int cantidad)
{
    char nombre[30];
    int pos;

    printf("\n--- CONSULTA DE GENERO ---\n");
    printf("Ingrese el nombre a buscar: ");
    fgets(nombre, sizeof(nombre), stdin);

    pos = buscarGenXNombre(lista, cantidad, nombre);
    if (pos == -1) {
        printf("No se encontro un genero activo con ese nombre.\n");
        return;
    }
    printf("\nID: %d\n", lista[pos].idGenero);
    printf("Nombre: %s\n",  lista[pos].nombre);
    printf("Descripcion: %s\n",  lista[pos].descripcion);
}
void listarGen(stGenero lista[],int cantidad)
{
    int i = 0 ;
    int hayActivos = 0;

    printf("\n--- GENEROS ACTIVOS ---\n");
    printf("%-5s %-50s %s\n", "ID", "Nombre", "Descripcion");

    for (i = 0; i < cantidad; i++) {
        if (lista[i].activo == ACTIVO) {
            printf("%5d %50s %s\n", lista[i].idGenero, lista[i].nombre, lista[i].descripcion);
            hayActivos = 1;
        }
    }

    if (hayActivos == 0){
        printf("No hay generos activos\n");
    }


}
///FdB///
int buscarGenXid(stGenero lista[], int cantidad, int id)
{
    int i;
    for (i = 0; i < cantidad; i++) {
        if (lista[i].idGenero == id)
            return i;
    }
    return -1;
}
int buscarGenXNombre(stGenero lista[], int cantidad, const char nombre[])
{
    int i;
    for (i = 0; i < cantidad; i++) {
        if (lista[i].activo == INACTIVO)
            continue;
        if (strcmp(lista[i].nombre, nombre) == 0)
            return i;
}
  return -1;

}
int generarIDGEN(stGenero lista[],int cantidad)
{
    int i;
    int max = 0;
    for (i = 0; i < cantidad; i++) {
        if (lista[i].idGenero > max)
            max = lista[i].idGenero;
    }
    return max + 1;
}

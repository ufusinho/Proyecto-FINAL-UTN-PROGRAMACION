#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Generos.h"

///Funciones extras///
void limpiarBuffer(void)
{
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
}
void limpiarNewline(char *s)
{
    int len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}
void aMinusculas(const char *origen, char *destino, int tam)
{
    int i;

    for (i = 0; i < tam - 1 && origen[i] != '\0'; i++)
    {
        destino[i] = tolower(origen[i]);
    }

    destino[i] = '\0';
}
void menuGeneros(stGenero lista[], int *cantidad,int cantContenido,int idGenContenido[],int esAdmin)
{
    int opcion;
    do
    {
        puts("\n\n===== MENU GENEROS =====");
        if(esAdmin)
        {
            printf("\n1. Alta de genero");
            printf("\n2. Baja de genero");
            printf("\n3. Listar generos");
            printf("\n0. Volver");
        }
        else
        {
            printf("\n1. Consultar genero");
            printf("\n2. Listar generos");
            printf("\n0. Volver");
        }

        printf("\n\nOpcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        if(esAdmin)
        {
            switch(opcion)
            {
            case 1:
                altaGen(lista, cantidad);
                break;

            case 2:
                bajaGen(lista, *cantidad,cantContenido,idGenContenido);
                break;

            case 3:
                listarGen(lista, *cantidad);
                break;

            case 0:
                printf("\nVolviendo...");
                break;

            default:
                printf("\nOpcion invalida.");
            }
        }
        else
        {
            switch(opcion)
            {
            case 1:
                consultarGen(lista, *cantidad);
                break;

            case 2:
                listarGen(lista, *cantidad);
                break;

            case 0:
                printf("\nVolviendo...");
                break;

            default:
                printf("\nOpcion invalida.");
            }
        }

    }while(opcion != 0);
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
    int  i;
    char nombreLista[50], nombreBuscar[50];

    aMinusculas(nombre, nombreBuscar, 50);

    for (i = 0; i < cantidad; i++) {
        if (lista[i].activo == INACTIVO)
            continue;
        aMinusculas(lista[i].nombre, nombreLista, 50);
        if (strcmp(nombreLista, nombreBuscar) == 0)
            return i;
    }
    return -1;
}
int generarIDGEN(stGenero lista[], int cantidad)
{
    int i;
    int max = 0;
    for (i = 0; i < cantidad; i++) {
        if (lista[i].idGenero > max)
            max = lista[i].idGenero;
    }
    return max + 1;
}
///LISTADO///
void listarGen(stGenero lista[], int cantidad)
{
    int i;
    int hayActivos = 0;

    printf("\n--- GENEROS ACTIVOS ---\n");
    printf("%-5s %-50s %s\n", "ID", "Nombre", "Descripcion");

    for (i = 0; i < cantidad; i++) {
        if (lista[i].activo == ACTIVO) {
            printf("%-5d %-50s %s\n", lista[i].idGenero, lista[i].nombre, lista[i].descripcion);
            hayActivos = 1;
        }
    }

    if (hayActivos == 0)
        printf("No hay generos activos\n");
}
///ABMyC///
void altaGen(stGenero lista[], int *cantidad)
{
    stGenero nuevo;

    if (*cantidad >= MAX_GENEROS) {
        printf("Llegaste al limite de generos\n");
        return;
    }

    printf("\n ALTA DE NUEVO GENERO \n");

    limpiarBuffer();

    do {
        printf("Nombre: ");
        fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
        limpiarNewline(nuevo.nombre);

        if (strlen(nuevo.nombre) == 0) {
            printf("ERROR: EL NOMBRE ESTA VACIO\n");
        } else if (buscarGenXNombre(lista, *cantidad, nuevo.nombre) != -1) {
            printf("Ya existe un genero con ese nombre, ingrese otro\n");
            nuevo.nombre[0] = '\0';
        }

    } while (strlen(nuevo.nombre) == 0);

    do {
        printf("Descripcion: ");
        fgets(nuevo.descripcion, sizeof(nuevo.descripcion), stdin);
        limpiarNewline(nuevo.descripcion);

        if (strlen(nuevo.descripcion) == 0)
            printf("ERROR: LA DESCRIPCION ESTA VACIA\n");

    } while (strlen(nuevo.descripcion) == 0);

    nuevo.idGenero = generarIDGEN(lista, *cantidad);
    nuevo.activo   = ACTIVO;

    lista[*cantidad] = nuevo;
    (*cantidad)++;

    printf("Genero \"%s\" agregado con ID %d.\n", nuevo.nombre, nuevo.idGenero);
}
void bajaGen(stGenero lista[], int cantidad, int cantContenido, int idGenContenido[])
{
    int id;
    int pos;
    int cont = 0;
    int i;

    printf("\nBAJA DE GENERO\n");
    listarGen(lista, cantidad);
    limpiarBuffer();
    printf("Ingrese el ID del genero para poder darlo de baja: ");
    scanf("%d", &id);

    pos = buscarGenXid(lista, cantidad, id);
    if (pos == -1 || lista[pos].activo == INACTIVO) {
        printf("Genero no encontrado o ya esta dado de baja\n");
        return;
    }
    for (i = 0; i < cantContenido; i++) {
        if (idGenContenido[i] == id) {
            cont = 1;
            break;
        }
    }
    if (cont) {
        printf("No es posible darlo de baja, hay contenido activo con este genero\n");
        return;
    }
    lista[pos].activo = INACTIVO;
    printf("El genero %s fue dado de baja\n", lista[pos].nombre);
}
void modificarGen(stGenero lista[], int cantidad)
{
    int id;
    int pos;
    int idXDupl;
    char nuevoNombre[50];
    char nuevaDesc[150];

    printf("\n MODIFICACION DE GENERO\n");
    listarGen(lista, cantidad);
    printf("Ingrese el ID del genero que desee modificar: ");
    scanf("%d", &id);
    limpiarBuffer();

    pos = buscarGenXid(lista, cantidad, id);
    if (pos == -1 || lista[pos].activo == INACTIVO) {
        printf("Genero no encontrado/inactivo\n");
        return;
    }

    printf("Nombre actual: %s\n", lista[pos].nombre);
    printf("Nuevo nombre (Enter para no cambiar): ");
    fgets(nuevoNombre, sizeof(nuevoNombre), stdin);
    limpiarNewline(nuevoNombre);

    if (strlen(nuevoNombre) > 0) {
        idXDupl = buscarGenXNombre(lista, cantidad, nuevoNombre);
        if (idXDupl != -1 && idXDupl != pos) {
            printf("Ya existe otro genero con ese nombre. Modificacion cancelada.\n");
            return;
        }
        strcpy(lista[pos].nombre, nuevoNombre);
    }

    printf("Descripcion actual: %s\n", lista[pos].descripcion);
    printf("Nueva descripcion (Enter para no cambiar): ");
    fgets(nuevaDesc, sizeof(nuevaDesc), stdin);
    limpiarNewline(nuevaDesc);

    if (strlen(nuevaDesc) > 0)
        strcpy(lista[pos].descripcion, nuevaDesc);

    printf("Genero modificado correctamente.\n");
}
void consultarGen(stGenero lista[], int cantidad)
{
    char nombre[50];
    int pos;

    printf("\n--- CONSULTA DE GENERO ---\n");
    printf("Ingrese el nombre a buscar: ");
    fgets(nombre, sizeof(nombre), stdin);
    limpiarNewline(nombre);

    pos = buscarGenXNombre(lista, cantidad, nombre);
    if (pos == -1) {
        printf("No se encontro un genero activo con ese nombre.\n");
        return;
    }
    printf("\nID: %d\n", lista[pos].idGenero);
    printf("Nombre: %s\n", lista[pos].nombre);
    printf("Descripcion: %s\n", lista[pos].descripcion);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Visualizaciones.h"

void limpiarBufferBis(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menuVisualizaciones(stVisualizacion lista[], int *cantidad,int idUsuarioLogueado,int esAdmin,int *idsContenidosActivos,int totalActivos)
{
    int opcion;
    do{
        puts("\n\n===== MENU VISUALIZACIONES =====");
        if(esAdmin){
            printf("\n 1. Listar visualizaciones");
            printf("\n 2. Dar de baja visualizacion");
            printf("\n 0. Volver");
        }else{
            printf("\n 1. Registrar visualizacion");
            printf("\n 2. Listar mis visualizaciones");
            printf("\n 3. Eliminar una visualizacion");
            printf("\n 0. Volver");
        }
        printf("\n\n Opcion: ");
        scanf("%d", &opcion);
        limpiarBufferBis();
        if(esAdmin){

            switch(opcion){
                case 1:
                    listarVisualizaciones(lista,*cantidad,idUsuarioLogueado,esAdmin);
                    break;
                case 2:
                    bajaVisualizacion(lista,*cantidad,idUsuarioLogueado,esAdmin);
                    break;
                case 0:
                    printf("\n Volviendo...");
                    break;
                default:
                    printf("\nOpcion invalida.");
            }
        }else{

            switch(opcion){

                case 1:
                    altaVisualizacion(lista,cantidad,idUsuarioLogueado,idsContenidosActivos,totalActivos);
                    break;
                case 2:
                    listarVisualizaciones(lista,*cantidad,idUsuarioLogueado,esAdmin);
                    break;
                case 3:
                    bajaVisualizacion(lista,*cantidad,idUsuarioLogueado,esAdmin);
                    break;
                case 0:
                    printf("\n Volviendo...");
                    break;
                default:
                    printf("\nOpcion invalida.");
            }
        }

    }while(opcion != 0);
}

///FdB Y AUXILIARES///
int generarIDVisualizacion(stVisualizacion lista[], int cantidad)
{
    int maxId = 0;
    int nuevoID = 0;
    for(int i = 0; i < cantidad; i++){
        if(lista[i].idVisualizacion > maxId){
            maxId = lista[i].idVisualizacion;
        }
    }

    nuevoID = maxId + 1;

    return nuevoID;
}

int buscarVisualizacionDuplicada(stVisualizacion lista[], int cantidad,int idUsuario, int idContenido,int dia, int mes, int anio)
{
    for(int i = 0; i < cantidad; i++){
        if(lista[i].activo == 1 &&
           lista[i].idUsuario   == idUsuario  &&
           lista[i].idContenido == idContenido &&
           lista[i].fechaDia    == dia         &&
           lista[i].fechaMes    == mes         &&
           lista[i].fechaAnio   == anio){
            return i;
        }
    }
    return -1;
}

int validarFecha(int dia, int mes, int anio)
{
    if(anio < 1900 || anio > 2100) return 0;
    if(mes  < 1    || mes  > 12)   return 0;
    if(dia  < 1)                   return 0;

    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)){
        diasPorMes[2] = 29;
    }
        if(dia > diasPorMes[mes]){
            valido = 0;
        }
    }

    return valido;
}

void cargarFecha(int *dia, int *mes, int *anio)
{
    do{
        printf("\n Dia  : "); scanf("%d", dia);
        printf("\n Mes  : "); scanf("%d", mes);
        printf("\n Anio : "); scanf("%d", anio);
        limpiarBufferBis();

        if(!validarFecha(*dia, *mes, *anio)){
            printf("\n Fecha invalida. Intente nuevamente.");
        }

    }while(!validarFecha(*dia, *mes, *anio));
}

int cargarCalificacion(void)
{
    int cal = 0;
    do{
        printf("\n Calificacion (1 al 10): ");
        scanf("%d", &cal);
        limpiarBufferBis();

        if(cal < 1 || cal > 10){
            printf("\n Calificacion invalida.");
        }

    }while(cal < 1 || cal > 10);

    return cal;
}

///ABMyC///
void altaVisualizacion(stVisualizacion lista[], int *cantidad,int idUsuarioLogueado,int *idsContenidosActivos, int totalActivos)
{

    if(*cantidad >= MAX_VISUALIZACIONES){
        printf("\n No hay espacio para mas visualizaciones.");
        return;
    }

    if(totalActivos == 0){
        printf("\n No hay contenidos activos disponibles.");
        return;
    }

    printf("\n Contenidos disponibles:\n");
    for(int i = 0; i < totalActivos; i++){
        printf("\n ID: %d", idsContenidosActivos[i]);
    }

    int idContenido = 0;
    int esValido    = 0;

    do{
        printf("\n\n Ingrese el ID del contenido visto: ");
        scanf("%d", &idContenido);
        limpiarBufferBis();

        esValido = 0;
        for(int i = 0; i < totalActivos; i++){
            if(idsContenidosActivos[i] == idContenido){
                esValido = 1;
                break;
            }
        }

        if(esValido == 0){
            printf("\n ID invalido. Intente nuevamente.");
        }

    }while(esValido == 0);

    int dia, mes, anio;
    printf("\n Ingrese la fecha en que vio el contenido:");
    cargarFecha(&dia, &mes, &anio);

    int calificacion = cargarCalificacion();
    int posDup = buscarVisualizacionDuplicada(lista, *cantidad,
                                               idUsuarioLogueado, idContenido,
                                               dia, mes, anio);

    if(posDup != -1){
        printf("\n Ya habia registrado ese contenido en esa fecha.");
        printf("\n Se actualiza la calificacion de %d a %d.", lista[posDup].calificacion, calificacion);
        lista[posDup].calificacion = calificacion;
        return;
    }
    stVisualizacion nueva;

    nueva.idVisualizacion = generarIDVisualizacion(lista, *cantidad);
    nueva.idUsuario       = idUsuarioLogueado;
    nueva.idContenido     = idContenido;
    nueva.fechaDia        = dia;
    nueva.fechaMes        = mes;
    nueva.fechaAnio       = anio;
    nueva.calificacion    = calificacion;
    nueva.activo          = 1;

    lista[*cantidad] = nueva;
    (*cantidad)++;

    printf("\n Visualizacion registrada correctamente con ID %d.", nueva.idVisualizacion);
}

void bajaVisualizacion(stVisualizacion lista[], int cantidad,int idUsuarioLogueado, int esAdmin)
{

    int idBuscar = 0;
    int pos      = -1;

    printf("\n Ingrese el ID de la visualizacion a eliminar: ");
    scanf("%d", &idBuscar);
    limpiarBufferBis();

    for(int i = 0; i < cantidad; i++){
        if(lista[i].idVisualizacion == idBuscar){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        printf("\n No se encontro una visualizacion con ese ID.");
        return;
    }

    if(lista[pos].activo == 0){
        printf("\n La visualizacion ya esta dada de baja.");
        return;
    }

    if(esAdmin == 0 && lista[pos].idUsuario != idUsuarioLogueado){
        printf("\n Acceso denegado. No puede eliminar visualizaciones de otro usuario.");
        return;
    }

    printf("\n Visualizacion encontrada:");
    printf("\n ID visualizacion : %d", lista[pos].idVisualizacion);
    printf("\n ID usuario       : %d", lista[pos].idUsuario);
    printf("\n ID contenido     : %d", lista[pos].idContenido);
    printf("\n Fecha            : %02d/%02d/%04d", lista[pos].fechaDia, lista[pos].fechaMes, lista[pos].fechaAnio);
    printf("\n Calificacion     : %d", lista[pos].calificacion);

    char confirmacion;
    printf("\n\n Confirma la baja? (s/n): ");
    scanf(" %c", &confirmacion);
    limpiarBufferBis();

    if(confirmacion == 's' || confirmacion == 'S'){
        lista[pos].activo = 0;
        printf("\n Visualizacion dada de baja correctamente.");
    }else{
        printf("\n Baja cancelada.");
    }
}

///LISTADO///
void listarVisualizaciones(stVisualizacion lista[], int cantidad,int idUsuarioLogueado, int esAdmin)
{

    int total = 0;

    printf("\n\n ========== VISUALIZACIONES ==========");

    for(int i = 0; i < cantidad; i++){

        if(esAdmin == 0){
            if(lista[i].idUsuario != idUsuarioLogueado) continue;
            if(lista[i].activo != 1) continue;
        }

        printf("\n ID visualizacion : %d", lista[i].idVisualizacion);
        printf("\n ID usuario       : %d", lista[i].idUsuario);
        printf("\n ID contenido     : %d", lista[i].idContenido);
        printf("\n Fecha            : %02d/%02d/%04d", lista[i].fechaDia, lista[i].fechaMes, lista[i].fechaAnio);
        printf("\n Calificacion     : %d", lista[i].calificacion);
        printf("\n Activo           : %s", lista[i].activo ? "Si" : "No");
        printf("\n --------------------------------------");
        total++;
    }

    if(total == 0){
        printf("\n No hay visualizaciones para mostrar.");
    }else{
        printf("\n Total: %d", total);
    }
}

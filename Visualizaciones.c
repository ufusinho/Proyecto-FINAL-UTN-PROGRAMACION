#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "Visualizaciones.h"

void limpiarBufferVis(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
///CARGAR Y GUARDAR///
int cargarVisualizaciones(stVisualizacion lista[], int *cantidad)
{

    FILE *fp = fopen(ARCHIVO_VISUALIZACIONES, "rb");
    *cantidad = 0;

    if(fp == NULL){
        fp = fopen(ARCHIVO_VISUALIZACIONES, "wb");
        if(fp == NULL){
            printf("\n Error: no se pudo crear el archivo de visualizaciones.");
            return 0;
        }
        fclose(fp);
        return 1;
    }

    while(*cantidad < MAX_VISUALIZACIONES && fread(&lista[*cantidad], sizeof(stVisualizacion), 1, fp) > 0){
        (*cantidad)++;
    }

    fclose(fp);
    return 1;
}
int guardarVisualizaciones(stVisualizacion lista[], int cantidad)
{

    FILE *fp = fopen(ARCHIVO_VISUALIZACIONES, "wb");

    if(fp == NULL){
        printf("\n Error: no se pudo abrir el archivo de visualizaciones.");
        return 0;
    }

    fwrite(lista, sizeof(stVisualizacion), cantidad, fp);
    fclose(fp);
    return 1;
}
///FdB Y AUXILIARES///
int generarIDVisualizacion(stVisualizacion lista[], int cantidad)
{
    int maxId = 0;

    for(int i = 0; i < cantidad; i++){
        if(lista[i].idVisualizacion > maxId){
            maxId = lista[i].idVisualizacion;
        }
    }

    return maxId + 1;
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

    return dia <= diasPorMes[mes];
}
void cargarFecha(int *dia, int *mes, int *anio)
{
    do{
        printf("\n Dia  : "); scanf("%d", dia);
        printf("\n Mes  : "); scanf("%d", mes);
        printf("\n Anio : "); scanf("%d", anio);
        limpiarBufferVis();

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
        limpiarBufferVis();

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
        limpiarBufferVis();

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
    limpiarBufferVis();

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
    limpiarBufferVis();

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
///BUSQUEDA///
void buscarContenidoVistoPorUsuario(stVisualizacion lista[], int cantidad,int *idsUsuarios, char nombresUsuarios[][40],int totalUsuarios,int *idsContenidos, char titulos[][60],int totalContenidos)
{

    int idBuscar = 0;
    int u, i, c;
    int encontrado = 0;
    int total      = 0;

    printf("\n Usuarios registrados:");
    for(u = 0; u < totalUsuarios; u++){
        printf("\n [%d] %s", idsUsuarios[u], nombresUsuarios[u]);
    }

    printf("\n\n Ingrese el ID del usuario a consultar: ");
    scanf("%d", &idBuscar);
    limpiarBufferVis();

    for(u = 0; u < totalUsuarios; u++){
        if(idsUsuarios[u] == idBuscar){
            encontrado = 1;
            break;
        }
    }

    if(encontrado == 0){
        printf("\n No se encontro un usuario con ese ID.");
        return;
    }

    printf("\n\n ===== CONTENIDO VISTO POR: %s =====", nombresUsuarios[u]);

    for(i = 0; i < cantidad; i++){

        if(lista[i].idUsuario != idBuscar || lista[i].activo != 1) continue;

        char *titulo = "Desconocido";
        for(c = 0; c < totalContenidos; c++){
            if(idsContenidos[c] == lista[i].idContenido){
                titulo = titulos[c];
                break;
            }
        }
        printf("\n Contenido    : %s", titulo);
        printf("\n Fecha        : %02d/%02d/%04d", lista[i].fechaDia, lista[i].fechaMes, lista[i].fechaAnio);
        printf("\n Calificacion : %d", lista[i].calificacion);
        printf("\n -------------------------------");
        total++;
    }

    if(total == 0){
        printf("\n El usuario no tiene visualizaciones registradas.");
    }else{
        printf("\n Total: %d", total);
    }
}
///REPORTES///
void reportePromedioCalificaciones(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos)
{
    printf("\n\n ===== PROMEDIO DE CALIFICACIONES POR CONTENIDO =====");

    for(int c = 0; c < totalContenidos; c++){

        int suma   = 0;
        int vistos = 0;

        for(int i = 0; i < cantidad; i++){
            if(lista[i].activo == 1 && lista[i].idContenido == idsContenidos[c]){
                suma += lista[i].calificacion;
                vistos++;
            }
        }

        if(vistos > 0){
            printf("\n %-40s Promedio: %.2f (%d vistas)", titulos[c], (float)suma / vistos, vistos);
        }else{
            printf("\n %-40s Sin visualizaciones", titulos[c]);
        }
    }
}
void reporteTop5Contenidos(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos)
{
    int   idsAux[MAX_VISUALIZACIONES];
    char  titulosAux[MAX_VISUALIZACIONES][60];
    float promedios[MAX_VISUALIZACIONES];
    int   vistos[MAX_VISUALIZACIONES];
    int   total = 0;

    for(int c = 0; c < totalContenidos; c++){

        int suma = 0;
        int cant = 0;

        for(int i = 0; i < cantidad; i++){
            if(lista[i].activo == 1 && lista[i].idContenido == idsContenidos[c]){
                suma += lista[i].calificacion;
                cant++;
            }
        }

        if(cant > 0){
            idsAux[total] = idsContenidos[c];
            strcpy(titulosAux[total], titulos[c]);
            promedios[total] = (float)suma / cant;
            vistos[total] = cant;
            total++;
        }
    }
    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - i - 1; j++){
            if(promedios[j] < promedios[j+1]){

                float pAux = promedios[j];
                promedios[j] = promedios[j+1];
                promedios[j+1] = pAux;

                int vAux = vistos[j];
                vistos[j] = vistos[j+1];
                vistos[j+1] = vAux;

                int idAux = idsAux[j];
                idsAux[j] = idsAux[j+1];
                idsAux[j+1] = idAux;

                char tituloAux[60];
                strcpy(tituloAux, titulosAux[j]);
                strcpy(titulosAux[j], titulosAux[j+1]);
                strcpy(titulosAux[j+1], tituloAux);
            }
        }
    }

    printf("\n\n ===== TOP 5 CONTENIDOS POR CALIFICACION =====");

    if(total == 0){
        printf("\n No hay contenidos con visualizaciones registradas.");
    }else{
        int limite = (total < 5) ? total : 5;
        for(int i = 0; i < limite; i++){
            printf("\n %d. %-40s Promedio: %.2f (%d vistas)", i + 1, titulosAux[i], promedios[i], vistos[i]);
        }
    }

}
void reporteUsuarioMasVisualizaciones(stVisualizacion lista[], int cantidad,int *idsUsuarios, char nombresUsuarios[][40],int totalUsuarios)
{
    int maxCant = 0;
    int maxIdx  = -1;

    for(int u = 0; u < totalUsuarios; u++){

        int contador = 0;

        for(int i = 0; i < cantidad; i++){
            if(lista[i].activo == 1 && lista[i].idUsuario == idsUsuarios[u]){
                contador++;
            }
        }
        if(contador > maxCant){
            maxCant = contador;
            maxIdx  = u;
        }
    }

    printf("\n\n ===== USUARIO CON MAS VISUALIZACIONES =====");

    if(maxIdx == -1){
        printf("\n Ningun usuario tiene visualizaciones registradas.");
    }else{
        printf("\n Usuario : %s (ID %d)", nombresUsuarios[maxIdx], idsUsuarios[maxIdx]);
        printf("\n Total   : %d visualizaciones", maxCant);
    }

}
void reporteContenidosSinVisualizaciones(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos)
{
    int sinVistas = 0;

    printf("\n\n ===== CONTENIDOS SIN VISUALIZACIONES =====");

    for(int c = 0; c < totalContenidos; c++){

        int tieneVistas = 0;

        for(int i = 0; i < cantidad; i++){
            if(lista[i].activo == 1 && lista[i].idContenido == idsContenidos[c]){
                tieneVistas = 1;
                break;
            }
        }

        if(tieneVistas == 0){
            printf("\n [%d] %s", idsContenidos[c], titulos[c]);
            sinVistas++;
        }
    }

    if(sinVistas == 0){
        printf("\n Todos los contenidos tienen al menos una visualizacion.");
    }else{
        printf("\n Total sin visualizaciones: %d", sinVistas);
    }
}
void reporteVisualizacionesUsuario(stVisualizacion lista[], int cantidad,int idUsuario,int *idsContenidos, char titulos[][60],int totalContenidos)
{
    int total = 0;

    printf("\n\n ===== MIS VISUALIZACIONES =====");

    for(int i = 0; i < cantidad; i++){

        if(lista[i].idUsuario != idUsuario || lista[i].activo != 1) continue;

        char *titulo = "Desconocido";
        for(int c = 0; c < totalContenidos; c++){
            if(idsContenidos[c] == lista[i].idContenido){
                titulo = titulos[c];
                break;
            }
        }

        printf("\n Contenido    : %s", titulo);
        printf("\n Fecha        : %02d/%02d/%04d", lista[i].fechaDia, lista[i].fechaMes, lista[i].fechaAnio);
        printf("\n Calificacion : %d", lista[i].calificacion);
        printf("\n -------------------------------");
        total++;
    }

    if(total == 0){
        printf("\n No tiene visualizaciones registradas.");
    }else{
        printf("\n Total: %d", total);
    }
}
void reportePromedioUsuario(stVisualizacion lista[], int cantidad, int idUsuario)
{
    int suma   = 0;
    int vistos = 0;

    for(int i = 0; i < cantidad; i++){
        if(lista[i].idUsuario == idUsuario && lista[i].activo == 1){
            suma += lista[i].calificacion;
            vistos++;
        }
    }
    printf("\n\n ===== MI PROMEDIO DE CALIFICACIONES =====");

    if(vistos == 0){
        printf("\n No tiene visualizaciones registradas.");
    }else{
        printf("\n Promedio: %.2f (basado en %d visualizaciones)", (float)suma / vistos, vistos);
    }

}

#include <stdio.h>
#include <stdlib.h>
#include "Persistencia.h"

// Contenidos
int cargarContenido(stContenido contenidos[], int *validosContenidos){

    FILE *archi = fopen(ARCHIVO_CONTENIDOS, "rb");
    *validosContenidos = 0;

    if(archi == NULL){
        archi = fopen(ARCHIVO_CONTENIDOS, "wb");
        if(archi == NULL){
            printf("\n Error al crear el archivo de contenidos. ");
            return 0;
        }
        fclose(archi);
        return 1;
    }

    while(*validosContenidos < MAX_CONTENIDOS && fread(&contenidos[*validosContenidos], sizeof(stContenido), 1, archi) > 0){

            (*validosContenidos)++;
    }

    fclose(archi);
    return 1;
}
int guardarContenidos(stContenido contenidos[], int validosContenidos){

    FILE *archi = fopen(ARCHIVO_CONTENIDOS, "wb");

    if(archi == NULL){

            printf("\n Error al abrir el archivo de contenidos. ");
            return 0;
    }

    fwrite(contenidos, sizeof(stContenido), validosContenidos, archi);

    fclose(archi);

    return 1;
}
// Generos
int cargarGeneros(stGenero lista[], int *cantidad){

    FILE *archi = fopen(ARCHIVO_GENEROS, "rb");
    *cantidad = 0;

    if (archi == NULL) {
        archi = fopen(ARCHIVO_GENEROS, "wb");
        if (archi == NULL) {
            printf("Error: no se pudo crear el archivo\n");
            return 0;
        }
        fclose(archi);
        return 1;
    }

    while (*cantidad < MAX_GENEROS && fread(&lista[*cantidad], sizeof(stGenero), 1, archi) > 0){

        (*cantidad)++;
    }


    fclose(archi);
    return 1;
}
int guardarGeneros(stGenero lista[], int cantidad){

    FILE *archi = fopen(ARCHIVO_GENEROS, "wb");

    if (archi == NULL) {
        printf("El archivo no se puede abrir\n");
        return 0;
    }

    fwrite(lista, sizeof(stGenero), cantidad, archi);
    fclose(archi);

    return 1;
}
// Usuarios
int cargarUsuarios(stUsuario usuarios[], int *validosUsuarios){

    FILE *archi = fopen(ARCHIVO_USUARIOS, "rb");

    *validosUsuarios = 0;

    if(archi == NULL){
        archi = fopen(ARCHIVO_USUARIOS, "wb");

        if(archi == NULL){
            printf("\n Error al crear el archivo de usuarios.");
            return 0;
        }

        fclose(archi);
        return 1;
    }

    while(*validosUsuarios < MAX_USUARIOS &&
          fread(&usuarios[*validosUsuarios], sizeof(stUsuario), 1, archi) > 0)
    {
        (*validosUsuarios)++;
    }

    fclose(archi);
    return 1;
}
int guardarUsuarios(stUsuario usuarios[], int validosUsuarios){

    FILE *archi = fopen(ARCHIVO_USUARIOS, "wb");

    if(archi == NULL){
        printf("\n Error al abrir el archivo de usuarios.");
        return 0;
    }

    fwrite(usuarios, sizeof(stUsuario), validosUsuarios, archi);

    fclose(archi);
    return 1;
}
// visualizaciones
int cargarVisualizaciones(stVisualizacion lista[], int *cantidad){

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
int guardarVisualizaciones(stVisualizacion lista[], int cantidad){

    FILE *fp = fopen(ARCHIVO_VISUALIZACIONES, "wb");

    if(fp == NULL){
        printf("\n Error: no se pudo abrir el archivo de visualizaciones.");
        return 0;
    }

    fwrite(lista, sizeof(stVisualizacion), cantidad, fp);
    fclose(fp);
    return 1;
}
// General
void cargarTodo(stContenido contenidos[], int *validosContenidos, stGenero generos[], int *validosGeneros, stUsuario usuarios[], int *validosUsuarios, stVisualizacion visualizaciones[], int *validosVisualizaciones){

    cargarContenido(contenidos, validosContenidos);
    cargarGeneros(generos, validosGeneros);
    cargarUsuarios(usuarios, validosUsuarios);
    cargarVisualizaciones(visualizaciones, validosVisualizaciones);

}
void guardarTodo(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros, stUsuario usuarios[], int validosUsuarios, stVisualizacion visualizaciones[], int validosVisualizaciones){

    guardarContenidos(contenidos, validosContenidos);
    guardarGeneros(generos, validosGeneros);
    guardarUsuarios(usuarios, validosUsuarios);
    guardarVisualizaciones(visualizaciones, validosVisualizaciones);
}

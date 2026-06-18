#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "Contenido.h"

void limpiarBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Carga y guardado.
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
// Alta de contenidos(solo admis).
int obtenerProximoIDContenido(stContenido contenidos[], int validos){

    int mayorID = 0;

        for(int i = 0; i < validos; i++){
            if(contenidos[i].idContenido > mayorID){
                mayorID = contenidos[i].idContenido;
            }
        }

    return mayorID + 1;
}
int existenciaDeTitulo(stContenido contenidos[], int validos, char titulo[]){



    for(int i = 0; i < validos; i++){
        if(strcmpi(contenidos[i].titulo, titulo)== 0 && contenidos[i].activo == ACTIVO){

            return 1;
        }
    }

    return 0;

}
int seleccionDeTipoContenido(){

    int opcion = 0;

    do{
    printf("\n\t\t\t Seleccione el tipo: \n");
    printf("\n1- Pelicula.");
    printf("\n2- Serie.");
    opcion = getch() - '0';
    if(opcion < 1 || opcion > 2){
        printf("\n Opcion invalida. ");
        Sleep(300);
        }
    }while(opcion < 1 || opcion > 2);

    return opcion;


}
int cargarDuracionPelicula(){

    int duracion = 0;

    do{
        printf("\n Ingrese la duracion de la pelicula. (Entre 40 y 300 minutos)");
        scanf("%d", &duracion);
        if(duracion < 40 || duracion > 300){

            printf("\n Duracion invalida. Entre 40 y 300 minutos. ");

            }

        }while(duracion < 40 || duracion > 300);

        return duracion;

}
int cargarEstadoDeSerie(){

    int estado = 0;
    int opcion = 0;

    do{

        printf("\n Ingrese en que estado se encuentra la serie. ");
        printf("\n1- En emision. ");
        printf("\n2- Finalizada. ");
        opcion = getch() - '0';
        if(opcion < 1 || opcion > 2){

            printf("\n Opcion invalida. Intente de nuevo. ");
            printf("\n");

        }else{

            if(opcion == 1){
                estado = 1;

            }else{

                estado = 0;

            }

        }

    }while(opcion < 1 || opcion > 2);

    return estado;


}
int cargarAnio(){

    int anio = 0;

    do{
    printf("\n Ingrese el anio. ");
    scanf("%d", &anio);
    if(anio < 1895 || anio > 2026){

        printf("\n Anio invalido. (Rango entre 1895 y 2026)\n");

        }

    }while(anio < 1895 || anio > 2026);

    return anio;

}
void mostrarGeneros(stGenero generos[], int validosGeneros){

    for(int i = 0; i < validosGeneros; i++){

            if(generos[i].activo == ACTIVO){
                printf("\nID: %d", generos[i].idGenero);
                printf("\nNombre: %s", generos[i].nombre);
                printf("\nDescripcion: %s", generos[i].descripcion);
                printf("\n-----------------------------\n");
            }
        }
}
int existenciaDeGenero(stGenero generos[], int validosGeneros, int idGenero){

    for(int i = 0; i < validosGeneros; i++){

            if(generos[i].idGenero == idGenero && generos[i].activo == ACTIVO){
                return 1;
        }
    }

    return 0;
}
int seleccionarGenero(stGenero generos[], int validosGeneros){
    int opcion = 0;
    int existe = 0;

    do{
        mostrarGeneros(generos, validosGeneros);

        printf("\n Ingrese el ID del genero: ");
        scanf("%d", &opcion);

        existe = existenciaDeGenero(generos, validosGeneros, opcion);

        if(existe == 0){
            printf("\n Genero invalido. ");
        }

    }while(existe == 0);

    return opcion;
}
stContenido cargarUnContenido(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros){

    stContenido nuevoContenido;
    int existencia = 0;
    int opcion;

    nuevoContenido.idContenido = obtenerProximoIDContenido(contenidos, validosContenidos);

    do{
        printf("\n Ingrese el titulo: ");
        limpiarBuffer();
        fgets(nuevoContenido.titulo, 60, stdin);
        nuevoContenido.titulo[strcspn(nuevoContenido.titulo, "\n")] = '\0';

        existencia = existenciaDeTitulo(contenidos, validosContenidos, nuevoContenido.titulo);

        if(existencia == 1){
            printf("\n Titulo ya existente. ");
        }

    }while(existencia == 1);

    opcion = seleccionDeTipoContenido();

    switch(opcion){

    case 1:
        strcpy(nuevoContenido.tipo, "pelicula");
        nuevoContenido.duracion = cargarDuracionPelicula();
        nuevoContenido.estado = -1;
        break;

    case 2:
        strcpy(nuevoContenido.tipo, "serie");
        nuevoContenido.estado = cargarEstadoDeSerie();
        nuevoContenido.duracion = 0;
        break;
    }

    nuevoContenido.anio = cargarAnio();

    printf("\n Escriba la sinopsis: ");
    limpiarBuffer();
    fgets(nuevoContenido.sinopsis, 300, stdin);
    nuevoContenido.sinopsis[strcspn(nuevoContenido.sinopsis, "\n")] = '\0';

    nuevoContenido.idGenero = seleccionarGenero(generos, validosGeneros);
    nuevoContenido.activo = ACTIVO;

    return nuevoContenido;
}
void altaContenido(stContenido contenidos[], int *validosContenidos, int dimensionContenidos, stGenero generos[], int validosGeneros){

    stContenido nuevo;

    if(*validosContenidos >= dimensionContenidos){
        printf("\n No hay espacio para mas contenidos. ");
        return;
    }

    nuevo = cargarUnContenido(contenidos, *validosContenidos, generos, validosGeneros);

   contenidos[*validosContenidos] = nuevo;
   (*validosContenidos)++;

   printf("\n Contenido cargado correctamente. ");

}
// Baja de contenido.
void mostrarContenido(stContenido contenido){


    printf("\n ID: %d ", contenido.idContenido);
    printf("\n Titulo: %s", contenido.titulo);
    printf("\n Tipo: %s", contenido.tipo);
    printf("\n Anio: %d", contenido.anio);
    printf("\n id genero: %d", contenido.idGenero);
    if(strcmpi(contenido.tipo, "pelicula")== 0){

        printf("\n Duracion: %d minutos", contenido.duracion);

    }else{

        if(contenido.estado == 1){
            printf("\n Estado: En emision. ");

        }else{

            printf("\n Estado: Finalizada. ");

        }


    }
        if(contenido.activo == ACTIVO){
            printf("\n Contenido activo. ");
        }else{
            printf("\n Contenido inactivo. ");

        }

}
int verificarVisualizaciones(stVisualizacion visualizaciones[], int validosVisualizaciones, int idContenido){

    for(int i = 0; i < validosVisualizaciones; i++){
        if(visualizaciones[i].idContenido == idContenido && visualizaciones[i].activo == ACTIVO){
            return 1;
        }
    }

    return 0;
}
int buscarPosicionContenido(stContenido contenidos[], int validos, int idContenido){

    for(int i = 0; i < validos; i++){
        if(contenidos[i].idContenido == idContenido && contenidos[i].activo == ACTIVO){
            return i;
        }
    }

    return -1;
}
void bajaDeContenido(stContenido contenidos[], int validosContenidos, stVisualizacion visualizaciones[], int validosVisualizaciones){

    int idContenido = 0;
    int pos = 0;

    do{
        listarContenidoActivo(contenidos, validosContenidos);

        printf("\n Ingrese el ID del contenido que desea dar de baja: ");
        scanf("%d", &idContenido);

        pos = buscarPosicionContenido(contenidos, validosContenidos, idContenido);

        if(pos == -1){
            printf("\n El contenido no existe. ");
        }

    }while(pos == -1);

    if(verificarVisualizaciones(visualizaciones, validosVisualizaciones, idContenido) == 1){
        printf("\n Error! El contenido tiene visualizaciones activas. ");
        return;
    }

    contenidos[pos].activo = INACTIVO;

    printf("\n Contenido dado de baja correctamente. ");
}
// Modificaciones.
void menuDeModificaciones(){

    printf("\n1- Modificar titulo.");
    printf("\n2- Modificar anio.");
    printf("\n3- Modificar genero.");
    printf("\n4- Modificar sinopsis.");
    printf("\n5- Modificar duracion o estado.");
    printf("\n0- Guardar todo. ");

}
int existenciaDeTituloExceptoID(stContenido contenidos[], int validos, char titulo[], int idContenido){

    for(int i = 0; i < validos; i++){
        if(strcmpi(contenidos[i].titulo, titulo) == 0 && contenidos[i].idContenido != idContenido && contenidos[i].activo == ACTIVO){
            return 1;
        }
    }

    return 0;
}
void modificarDatosDeContenidos(stContenido *contenidoActual, stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros){

    int opcion = 0;
    int existencia = 0;

    do{
        menuDeModificaciones();
        scanf("%d", &opcion);

        switch(opcion){

        case 1:
            do{
                printf("\n Ingrese el nuevo titulo: ");
                limpiarBuffer();
                fgets(contenidoActual->titulo, 60, stdin);
                contenidoActual->titulo[strcspn(contenidoActual->titulo, "\n")] = '\0';

                existencia = existenciaDeTituloExceptoID(contenidos, validosContenidos, contenidoActual->titulo, contenidoActual->idContenido);
                if(existencia == 1){
                    printf("\n El titulo ya existe. ");
                }

            }while(existencia == 1);
            break;

        case 2:
            contenidoActual->anio = cargarAnio();
            break;

        case 3:
            contenidoActual->idGenero = seleccionarGenero(generos, validosGeneros);
            break;

        case 4:
            printf("\n Ingrese la nueva sinopsis: ");
            limpiarBuffer();
            fgets(contenidoActual->sinopsis, 300, stdin);
            contenidoActual->sinopsis[strcspn(contenidoActual->sinopsis, "\n")] = '\0';
            break;

        case 5:
            if(strcmpi(contenidoActual->tipo, "pelicula") == 0){
                contenidoActual->duracion = cargarDuracionPelicula();
            }else{
                contenidoActual->estado = cargarEstadoDeSerie();
            }
            break;
        }

    }while(opcion != 0);

}
void modificarContenido(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros){
    int idContenido;
    int pos;

    do{
        listarContenidoActivo(contenidos, validosContenidos);

        printf("\n Ingrese el ID del contenido a modificar: ");
        scanf("%d", &idContenido);

        pos = buscarPosicionContenido(contenidos, validosContenidos, idContenido);

        if(pos == -1){
            printf("\n Contenido inexistente. ");
        }

    }while(pos == -1);

    printf("\n Datos actuales: ");
    mostrarContenido(contenidos[pos]);

    modificarDatosDeContenidos(&contenidos[pos], contenidos, validosContenidos, generos, validosGeneros);

    printf("\n Contenido modificado correctamente. ");

}
// Consulta y listado.
void consultarContenidoPorTitulo(stContenido contenidos[], int validosContenidos){

    char tituloBuscado[60];


    printf("\n Ingrese el titulo buscado: ");
    limpiarBuffer();
    fgets(tituloBuscado, 60, stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")] = '\0';

    for(int i = 0; i < validosContenidos; i++){
        if(strcmpi(contenidos[i].titulo, tituloBuscado) == 0 &&
           contenidos[i].activo == ACTIVO){
            mostrarContenido(contenidos[i]);
            return;
        }
    }

    printf("\n Contenido no encontrado. ");

}
void listarPeliculas(stContenido contenidos[], int validosContenidos){

    for(int i = 0; i < validosContenidos; i++){
        if(contenidos[i].activo == ACTIVO && strcmpi(contenidos[i].tipo, "pelicula") == 0){
            mostrarContenido(contenidos[i]);
        }
    }
}
void listarSeries(stContenido contenidos[], int validosContenidos){

    for(int i = 0; i < validosContenidos; i++){
        if(contenidos[i].activo == ACTIVO && strcmpi(contenidos[i].tipo, "serie") == 0){
            mostrarContenido(contenidos[i]);
        }
    }
}
void listarPorGenero(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros){

    int idGenero = 0;

    idGenero = seleccionarGenero(generos, validosGeneros);

    for(int i = 0; i < validosContenidos; i++){
        if(contenidos[i].activo == ACTIVO && contenidos[i].idGenero == idGenero){
            mostrarContenido(contenidos[i]);
        }
    }
}
void consultarContenidoPorID(stContenido contenidos[], int validosContenidos){

    int idContenidoBuscado = 0;

    printf("\n Ingrese el ID: ");
    scanf("%d", &idContenidoBuscado);

    for(int i = 0; i < validosContenidos; i++){
        if(contenidos[i].idContenido == idContenidoBuscado && contenidos[i].activo == ACTIVO){
            mostrarContenido(contenidos[i]);
            return;
        }
    }

    printf("\n No se ha encontrado el contenido. ");

}
void listarContenidoActivo(stContenido contenidos[], int validosContenidos){

    for(int i = 0; i < validosContenidos; i++){
        if(contenidos[i].activo == ACTIVO){
            mostrarContenido(contenidos[i]);
            printf("\n-----------------------------\n");
        }
    }
}

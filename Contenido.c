#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "Contenido.h"

void limpiarBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Alta de contenidos(solo admis).
int obtenerProximoIDContenido(char archivo[]){

    FILE *archi;
    stContenido aux;
    int mayorID = 0;

    archi = fopen(archivo, "rb");
    if(archi == NULL){

        return 1;
    }

    while(fread(&aux, sizeof(stContenido), 1, archi) > 0){

        if(aux.idContenido > mayorID){

            mayorID = aux.idContenido;
        }

    }

    fclose(archi);

    return mayorID +1;
}
int existenciaDeTitulo(char archivo[], char titulo[]){

    FILE * archi;
    stContenido aux;

    archi = fopen(archivo, "rb");
    if(archi == NULL){
        printf("\n El archivo no se ha podido abrir. \n");
        return 0;
    }

    while(fread(&aux, sizeof(stContenido), 1, archi) > 0){

        if(strcmpi(aux.titulo, titulo) == 0){
            fclose(archi);
            return 1;
        }
    }

    fclose(archi);
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
void mostrarGeneros(char archivoGenero[]){

    FILE *archi;
    stGenero aux;

    archi = fopen(archivoGenero, "rb");
    if(archi == NULL){
        printf("\n El archivo no se ha podido abrir. ");
        return;
    }
    while(fread(&aux, sizeof(stGenero), 1, archi) > 0){

        if(aux.activo == 1){

            printf("\nID: %d ", aux.idGenero);
            printf("\nNombre: %s", aux.nombre);
            printf("\nDescripcion: %s", aux.descripcion);
            printf("\n----------------------------------\n");
        }

    }

    fclose(archi);

}
int existenciaDeGenero(char archivoGeneros[], int idGenero){

    FILE *archi;

    stGenero aux;

    archi = fopen(archivoGeneros, "rb");
    if(archi == NULL){

        printf("\n El archivo no se ha podido abrir. ");
        return -1;

    }

    while(fread(&aux, sizeof(stGenero), 1, archi) > 0){

        if(aux.idGenero == idGenero && aux.activo == 1){
            fclose(archi);
            return 1;
        }

    }

    fclose(archi);
    return 0;


}
int seleccionarGenero(char archivoGenero[]){

    int opcion = 0;
    int existencia = 0;


    do{
    mostrarGeneros(archivoGenero);
    printf("\n Ingrese el ID del genero. ");
    scanf("%d", &opcion);
    existencia = existenciaDeGenero(archivoGenero, opcion);
    if(existencia == 0){

        printf("\n Genero invalido. ");
    }
    }while(existencia == 0);

    return opcion;

}
void guardarUnContenido(char archivoContenido[], stContenido nuevoContenido){

    FILE *archi;

    archi = fopen(archivoContenido, "ab");
    if(archi == NULL){

        printf("\n El archivo no se ha podido abrir. ");
        return;
    }

    fwrite(&nuevoContenido, sizeof(stContenido), 1, archi);

    fclose(archi);

}
stContenido cargarUnContenido(char archivoGenero[], char archivoContenido[]){

    stContenido nuevoContenido;
    int existencia;
    int opcion = 0;



    nuevoContenido.idContenido = obtenerProximoIDContenido(archivoContenido);

    do{

    printf("\n Ingrese el titulo. \n");
    limpiarBuffer();
    fgets(nuevoContenido.titulo, 60, stdin);
    nuevoContenido.titulo[strcspn(nuevoContenido.titulo, "\n")] = '\0';

    existencia = existenciaDeTitulo(archivoContenido, nuevoContenido.titulo);

    if(existencia == 1){

        printf("\n\t\t\t Titulo ya existente. ");
        }

    }while(existencia == 1);

    system("cls");

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

    printf("\n Escriba la sinopsis. \n");
    limpiarBuffer();
    fgets(nuevoContenido.sinopsis, 300, stdin);
    nuevoContenido.sinopsis[strcspn(nuevoContenido.sinopsis, "\n")] = '\0';

    nuevoContenido.idGenero = seleccionarGenero(archivoGenero);

    nuevoContenido.activo = 1;

    return nuevoContenido;

}
// Baja de contenido.
void mostrarContenido(stContenido contenido){


    printf("\n ID: %d ", contenido.idContenido);
    printf("\n Titulo: %s", contenido.titulo);
    printf("\n Tipo: %s", contenido.tipo);
    printf("\n Anio: %d", contenido.anio);
    printf("\n id genero: %d", contenido.idGenero);
    if(strcmp(contenido.tipo, "pelicula")== 0){

        printf("\n Duracion: %d minutos", contenido.duracion);

    }else{

        if(contenido.estado == 1){
            printf("\n Estado: En emision. ");

        }else{

            printf("\n Estado: Finalizada. ");

        }


    }
        if(contenido.activo == 1){
            printf("\n Contenido activo. ");
        }else{
            printf("\n Contenido inactivo. ");

        }

}
int verificarVisualizaciones(char archivoVisualizaciones[], int idContenido){

    FILE *archi;
    stVisualizacion aux;

    archi = fopen(archivoVisualizaciones, "rb");
    if(archi == NULL){

        printf("\n El archivo no se ha podido abrir. ");
        return -1;
    }
    while(fread(&aux, sizeof(stVisualizacion), 1, archi)>0){

        if(aux.idContenido == idContenido && aux.activo == 1){
            fclose(archi);
            return 1;
        }

    }

    fclose(archi);
    return 0;
}
int buscarPosicionContenido(char archivoContenidos[], int idContenidos){

    FILE *archi;
    stContenido aux;
    int pos = 0;

    archi = fopen(archivoContenidos, "rb");
    if(archi == NULL){

        printf("\n El archivo no se ha podido abrir. ");
        return -1;

    }
    while(fread(&aux, sizeof(stContenido), 1, archi) > 0){

            if(aux.idContenido == idContenidos && aux.activo == 1){

                fclose(archi);
                return pos;
            }

            pos++;

        }

    fclose(archi);

    return -1;

}
void bajaDeContenido(char archivoContenidos[], char archivoVisualizacion[]){

    FILE *archi;
    stContenido aux;
    int idContenido;
    int pos;

    archi = fopen(archivoContenidos, "r+b");
    if(archi == NULL){

        printf("\n Error. El archivo no se ha podido abrir. ");
        return;
    }

    do{
    listarContenidoActivo(archivoContenidos);
    printf("\n Ingrese el ID del contenido que desea dar de baja. ");
    scanf("%d", &idContenido);
    pos = buscarPosicionContenido(archivoContenidos, idContenido);

    if(pos == -1){

        printf("\n El contenido no existe. ");
        }

    }while(pos == -1);

    fseek(archi, pos * sizeof(stContenido), SEEK_SET);
    fread(&aux, sizeof(stContenido), 1, archi);
    if(verificarVisualizaciones(archivoVisualizacion, idContenido) == 1){

        printf("\n Error! El contenido tiene visualizaciones activas. ");
        fclose(archi);
        return;
    }
    aux.activo = 0;
    fseek(archi, pos * sizeof(stContenido), SEEK_SET);
    fwrite(&aux, sizeof(stContenido), 1, archi);

    printf("\n Contenido dado de baja correctamente. ");

    fclose(archi);

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
void modificarDatosDeContenidos(stContenido *contenido, char archivoContenidos[], char archivoGenero[]){

        int opcion = 0;
        int existencia;

        do{
            menuDeModificaciones();
            scanf("%d", &opcion);

            switch(opcion){


            case 1:


                do{
                    printf("\n Ingrese el nuevo titulo. ");
                    limpiarBuffer();
                    fgets(contenido->titulo, 60, stdin);
                    contenido->titulo[strcspn(contenido->titulo, "\n")] = '\0';
                    existencia = existenciaDeTitulo(archivoContenidos, contenido->titulo);
                    if(existencia == 1){
                        printf("\n El titulo ya existe. ");
                    }

                }while(existencia == 1);
                break;

            case 2:

                printf("\n Ingrese el nuevo anio. ");
                contenido->anio = cargarAnio();
                break;

            case 3:

                contenido->idGenero = seleccionarGenero(archivoGenero);
                break;

            case 4:

                printf("\n Ingrese la nueva sinopsis. ");
                limpiarBuffer();
                fgets(contenido->sinopsis, 300, stdin);
                contenido->sinopsis[strcspn(contenido->sinopsis, "\n")] = '\0';
                break;

            case 5:

                if(strcmp(contenido->tipo, "pelicula")== 0){

                    contenido->duracion = cargarDuracionPelicula();


                }else{

                    contenido->estado = cargarEstadoDeSerie();

                }
                break;
            }

        }while(opcion != 0);

}
void modificarContenido(char archivoContenido[], char archivoGenero[]){

    FILE *archi;
    int pos = 0;
    int idContenido;
    stContenido aux;

    archi = fopen(archivoContenido, "r+b");
    if(archi == NULL){

        printf("\n Error al abrir el archivo.");
        return;
    }

    do{
    listarContenidoActivo(archivoContenido);

    printf("\n Ingrese el ID. ");
    scanf("%d", &idContenido);
    pos = buscarPosicionContenido(archivoContenido, idContenido);
    if(pos == -1){
        printf("\n Contenido inexistente.");
    }
    }while(pos == -1);

    fseek(archi, pos * sizeof(stContenido), SEEK_SET);
    fread(&aux, sizeof(stContenido), 1, archi);

    printf("\n Datos actuales: ");
    mostrarContenido(aux);
    modificarDatosDeContenidos(&aux, archivoContenido, archivoGenero);

    fseek(archi, pos * sizeof(stContenido), SEEK_SET);
    fwrite(&aux, sizeof(stContenido), 1, archi);

    fclose(archi);


}
// Consulta y listado.
void consultarContenidoPorTitulo(char archivoContenido[]){

    FILE *archi;
    stContenido aux;
    char tituloBuscado[60];

    archi = fopen(archivoContenido, "rb");
    if(archi == NULL){

        printf("\n Error al abrir el archivo. ");
        return;

    }

    printf("\n\t\t\t Buscar titulo. ");
    printf("\n Ingrese el titulo buscado. ");
    limpiarBuffer();
    fgets(tituloBuscado, 60, stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")] = '\0';


    while(fread(&aux, sizeof(stContenido), 1, archi)>0){

        if(strcmpi(aux.titulo, tituloBuscado)==0 && aux.activo == 1){

            mostrarContenido(aux);
            fclose(archi);
            return;

        }

    }

    printf("\n Contenido no encontrado. ");

    fclose(archi);
}
void listarPeliculas(char archivoContenido[]){

    FILE *archi;
    stContenido aux;

    archi = fopen(archivoContenido, "rb");
    if(archi == NULL){

        printf("\n Error al abrir el archivo. ");
        return;
    }

    while(fread(&aux, sizeof(stContenido), 1, archi)> 0){

        if(aux.activo == 1 && strcmpi(aux.tipo, "pelicula") == 0){

            mostrarContenido(aux);

        }

    }

    fclose(archi);

}
void listarSeries(char archivoContenido[]){

    FILE *archi;
    stContenido aux;

    archi = fopen(archivoContenido, "rb");
    if(archi == NULL){

        printf("\n Error al abrir el archivo. ");
        return;

    }

    while(fread(&aux, sizeof(stContenido), 1, archi)>0){

        if(aux.activo == 1 && strcmpi(aux.tipo, "serie") == 0){

            mostrarContenido(aux);

        }

    }
    fclose(archi);

}
void listarPorGenero(char archivoContenido[], char archivoGeneros[]){

    FILE *archi;
    stContenido aux;
    int idGenero = 0;


    mostrarGeneros(archivoGeneros);
    idGenero = seleccionarGenero(archivoGeneros);

    archi = fopen(archivoContenido, "rb");
    if(archi == NULL){

        printf("\n Error al abrir el archivo. ");
        return;

    }

    while(fread(&aux, sizeof(stContenido), 1, archi)>0){

            if(idGenero == aux.idGenero && aux.activo == 1){

                mostrarContenido(aux);
            }

    }
    fclose(archi);
}
void consultarContenidoPorID(char archivoContenido[]){

    FILE *archi;
    int idContenidoBuscado = 0;
    stContenido aux;

    archi = fopen(archivoContenido, "rb");
    if(archi == NULL){

        printf("\n Error al abrir el archivo. ");
        return;

    }

    printf("\n Ingrese el ID. ");
    scanf("%d", &idContenidoBuscado);

    while(fread(&aux, sizeof(stContenido), 1, archi)>0){

        if(aux.idContenido == idContenidoBuscado && aux.activo == 1){

            mostrarContenido(aux);
            fclose(archi);
            return;
        }

    }

    printf("\n No se ha encontrado el contenido. ");
    fclose(archi);
}
void listarContenidoActivo(char archivoContenidos[]){

    FILE *archi;
    stContenido aux;

    archi = fopen(archivoContenidos, "rb");
    if(archi == NULL){

        printf("\n El archivo no se ha podido abrir. ");
        return;
    }

    while(fread(&aux, sizeof(stContenido), 1, archi)>0){

        if(aux.activo == 1){
            mostrarContenido(aux);
            printf("\n --------------------------- \n");
        }
    }

    fclose(archi);

}

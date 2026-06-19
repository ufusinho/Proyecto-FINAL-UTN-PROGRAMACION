#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Contenido.h"

int esVacioOEspacios(char texto[]) {
    if (strlen(texto) == 0) return 1;
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != ' ' && texto[i] != '\n' && texto[i] != '\t') {
            return 0; // Encontro texto real
        }
    }
    return 1; // Solo habia espacios
}

// Menu de contenidos.
void menuContenido(stContenido contenidos[], int *validosContenidos, stGenero generos[], int validosGeneros, stVisualizacion visualizaciones[], int validosVisualizaciones, int esAdmin){

    int opcion = 0;
    char buffer[10];

    do{
        system("cls");

        printf("\n========== MENU CONTENIDOS ==========");
        if(esAdmin){
            printf("\n1- Alta de contenido");
            printf("\n2- Baja de contenido");
            printf("\n3- Modificar contenido");
            printf("\n4- Consultar contenido por titulo");
            printf("\n5- Consultar contenido por ID");
            printf("\n6- Listar peliculas");
            printf("\n7- Listar series");
            printf("\n8- Listar por genero");
            printf("\n9- Listar contenidos activos");
        } else {
            printf("\n1- Consultar contenido por titulo");
            printf("\n2- Consultar contenido por ID");
            printf("\n3- Listar peliculas");
            printf("\n4- Listar series");
            printf("\n5- Listar por genero");
        }
        printf("\n0- Volver");
        printf("\n=====================================");
        printf("\nIngrese una opcion: ");

        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        opcion = atoi(buffer);

        system("cls");

        // --- LOGICA DEL ADMINISTRADOR ---
        if(esAdmin){
            switch(opcion){
            case 1: altaContenido(contenidos, validosContenidos, MAX_CONTENIDOS, generos, validosGeneros); break;
            case 2: bajaDeContenido(contenidos, *validosContenidos, visualizaciones, validosVisualizaciones); break;
            case 3: modificarContenido(contenidos, *validosContenidos, generos, validosGeneros); break;
            case 4: consultarContenidoPorTitulo(contenidos, *validosContenidos); break;
            case 5: consultarContenidoPorID(contenidos, *validosContenidos); break;
            case 6: listarPeliculas(contenidos, *validosContenidos); break;
            case 7: listarSeries(contenidos, *validosContenidos); break;
            case 8: listarPorGenero(contenidos, *validosContenidos, generos, validosGeneros); break;
            case 9: listarContenidoActivo(contenidos, *validosContenidos); break;
            case 0: printf("\nVolviendo al menu anterior..."); break;
            default: if(buffer[0] != '0') printf("\nOpcion invalida."); break;
            }
        }
        // --- LOGICA DEL USUARIO COMUN ---
        else {
            switch(opcion){
            case 1: consultarContenidoPorTitulo(contenidos, *validosContenidos); break;
            case 2: consultarContenidoPorID(contenidos, *validosContenidos); break;
            case 3: listarPeliculas(contenidos, *validosContenidos); break;
            case 4: listarSeries(contenidos, *validosContenidos); break;
            case 5: listarPorGenero(contenidos, *validosContenidos, generos, validosGeneros); break;
            case 0: printf("\nVolviendo al menu anterior..."); break;
            default: if(buffer[0] != '0') printf("\nOpcion invalida."); break;
            }
        }

        if(opcion != 0){
            printf("\n\n");
            system("pause");
        }

    }while(opcion != 0 || buffer[0] != '0');
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
        if(strcasecmp(contenidos[i].titulo, titulo)== 0 && contenidos[i].activo == ACTIVO){
            return 1;
        }
    }
    return 0;
}

int seleccionDeTipoContenido(){
    int opcion = 0;
    char buffer[10];

    do{
        printf("\n\t\t\t Seleccione el tipo: \n");
        printf("\n1- Pelicula.");
        printf("\n2- Serie.");
        printf("\nOpcion: ");

        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        opcion = atoi(buffer);

        if(opcion < 1 || opcion > 2){
            printf("\n Opcion invalida. ");
            Sleep(300);
        }
    }while(opcion < 1 || opcion > 2);

    return opcion;
}

int cargarDuracionPelicula(){
    int duracion = 0;
    char buffer[10];

    do{
        printf("\n Ingrese la duracion de la pelicula (Entre 40 y 300 minutos): ");
        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        duracion = atoi(buffer);

        if(duracion < 40 || duracion > 300){
            printf("\n Duracion invalida. Entre 40 y 300 minutos. ");
        }
    }while(duracion < 40 || duracion > 300);

    return duracion;
}

int cargarEstadoDeSerie(){
    int estado = 0;
    int opcion = 0;
    char buffer[10];

    do{
        printf("\n Ingrese en que estado se encuentra la serie. ");
        printf("\n1- En emision. ");
        printf("\n2- Finalizada. ");
        printf("\nOpcion: ");

        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        opcion = atoi(buffer);

        if(opcion < 1 || opcion > 2){
            printf("\n Opcion invalida. Intente de nuevo. \n");
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
    char buffer[10];

    do{
        printf("\n Ingrese el anio: ");
        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        anio = atoi(buffer);

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
    char buffer[10];

    do{
        mostrarGeneros(generos, validosGeneros);

        printf("\n Ingrese el ID del genero: ");
        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        opcion = atoi(buffer);

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
        fgets(nuevoContenido.titulo, 60, stdin);
        nuevoContenido.titulo[strcspn(nuevoContenido.titulo, "\n")] = '\0';

        if(esVacioOEspacios(nuevoContenido.titulo)) {
            continue;
        }

        existencia = existenciaDeTitulo(contenidos, validosContenidos, nuevoContenido.titulo);

        if(existencia == 1){
            printf("\n [ERROR] Titulo ya existente en el sistema. \n");
        }

    }while(existencia == 1 || esVacioOEspacios(nuevoContenido.titulo));

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

    do {
        printf("\n Escriba la sinopsis: ");
        fgets(nuevoContenido.sinopsis, 300, stdin);
        nuevoContenido.sinopsis[strcspn(nuevoContenido.sinopsis, "\n")] = '\0';
    } while (esVacioOEspacios(nuevoContenido.sinopsis));

    nuevoContenido.idGenero = seleccionarGenero(generos, validosGeneros);
    nuevoContenido.activo = ACTIVO;

    return nuevoContenido;
}

void altaContenido(stContenido contenidos[], int *validosContenidos, int dimensionContenidos, stGenero generos[], int validosGeneros){

    if(validosGeneros == 0){
        printf("\n [ERROR] No hay generos creados en el sistema.");
        printf("\n Vaya al Menu de Generos (Opcion 200) y cree al menos uno primero.\n");
        return;
    }

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

void mostrarContenido(stContenido contenido){

    printf("\n ID: %d ", contenido.idContenido);
    printf("\n Titulo: %s", contenido.titulo);
    printf("\n Tipo: %s", contenido.tipo);
    printf("\n Anio: %d", contenido.anio);
    printf("\n id genero: %d", contenido.idGenero);

    if(strcasecmp(contenido.tipo, "pelicula")== 0){
        printf("\n Duracion: %d minutos", contenido.duracion);
    }else{
        if(contenido.estado == 1){
            printf("\n Estado: En emision. ");
        }else{
            printf("\n Estado: Finalizada. ");
        }
    }

    if(contenido.activo == ACTIVO){
        printf("\n Contenido activo.\n\n ");
    }else{
        printf("\n Contenido inactivo.\n\n ");
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
    int pos = -1;
    char buffer[10];

    do{
        listarContenidoActivo(contenidos, validosContenidos);

        printf("\n Ingrese el ID del contenido que desea dar de baja: ");
        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        idContenido = atoi(buffer);

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
    printf("\n0- Guardar todo. \n");
    printf("\nSeleccione una opcion: ");
}

int existenciaDeTituloExceptoID(stContenido contenidos[], int validos, char titulo[], int idContenido){
    for(int i = 0; i < validos; i++){
        if(strcasecmp(contenidos[i].titulo, titulo) == 0 && contenidos[i].idContenido != idContenido && contenidos[i].activo == ACTIVO){
            return 1;
        }
    }
    return 0;
}

void modificarDatosDeContenidos(stContenido *contenidoActual, stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros){

    int opcion = 0;
    int existencia = 0;
    char buffer[10];

    do{
        menuDeModificaciones();
        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        opcion = atoi(buffer);

        system("cls");

        switch(opcion){

        case 1:
            do{
                printf("\n Ingrese el nuevo titulo: ");
                fgets(contenidoActual->titulo, 60, stdin);
                contenidoActual->titulo[strcspn(contenidoActual->titulo, "\n")] = '\0';

                if(esVacioOEspacios(contenidoActual->titulo)) continue;

                existencia = existenciaDeTituloExceptoID(contenidos, validosContenidos, contenidoActual->titulo, contenidoActual->idContenido);
                if(existencia == 1){
                    printf("\n El titulo ya existe. ");
                }

            }while(existencia == 1 || esVacioOEspacios(contenidoActual->titulo));
            break;

        case 2:
            contenidoActual->anio = cargarAnio();
            break;

        case 3:
            contenidoActual->idGenero = seleccionarGenero(generos, validosGeneros);
            break;

        case 4:
            do {
                printf("\n Ingrese la nueva sinopsis: ");
                fgets(contenidoActual->sinopsis, 300, stdin);
                contenidoActual->sinopsis[strcspn(contenidoActual->sinopsis, "\n")] = '\0';
            } while (esVacioOEspacios(contenidoActual->sinopsis));
            break;

        case 5:
            if(strcasecmp(contenidoActual->tipo, "pelicula") == 0){
                contenidoActual->duracion = cargarDuracionPelicula();
            }else{
                contenidoActual->estado = cargarEstadoDeSerie();
            }
            break;

        default:
            if(opcion != 0) {
                printf("\n Opcion invalida. ");
                Sleep(500);
            }
            break;
        }

    }while(opcion != 0 || buffer[0] != '0');

}

void modificarContenido(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros){

    int idContenido = 0;
    int pos = -1;
    char buffer[10];

    do{
        listarContenidoActivo(contenidos, validosContenidos);

        printf("\n Ingrese el ID del contenido a modificar: ");
        do {
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
        } while(esVacioOEspacios(buffer));
        idContenido = atoi(buffer);

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
    do {
        fgets(tituloBuscado, 60, stdin);
        tituloBuscado[strcspn(tituloBuscado, "\n")] = '\0';
    } while (esVacioOEspacios(tituloBuscado));

    for(int i = 0; i < validosContenidos; i++){
        if(strcasecmp(contenidos[i].titulo, tituloBuscado) == 0 &&
           contenidos[i].activo == ACTIVO){
            mostrarContenido(contenidos[i]);
            return;
        }
    }

    printf("\n Contenido no encontrado. ");
}

void listarPeliculas(stContenido contenidos[], int validosContenidos){
    for(int i = 0; i < validosContenidos; i++){
        if(contenidos[i].activo == ACTIVO && strcasecmp(contenidos[i].tipo, "pelicula") == 0){
            mostrarContenido(contenidos[i]);
        }
    }
}

void listarSeries(stContenido contenidos[], int validosContenidos){
    for(int i = 0; i < validosContenidos; i++){
        if(contenidos[i].activo == ACTIVO && strcasecmp(contenidos[i].tipo, "serie") == 0){
            mostrarContenido(contenidos[i]);
        }
    }
}

void listarPorGenero(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros){

    if(validosGeneros == 0){
        printf("\n [ERROR] No hay generos creados en el sistema.\n");
        return;
    }

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
    char buffer[10];

    printf("\n Ingrese el ID: ");
    do {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
    } while(esVacioOEspacios(buffer));
    idContenidoBuscado = atoi(buffer);

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

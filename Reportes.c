#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "Reportes.h"

void limpiarBufferRep(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void menuReportes(stVisualizacion lista[], int cantidad,int *idsUsuarios, char nombresUsuarios[][40], int totalUsuarios,int *idsContenidos, char titulos[][60], int totalContenidos,int idUsuarioLogueado, int esAdmin)
{
    int opcion;
    do{
        puts("\n===== MENU REPORTES =====");

        if(esAdmin){
            printf("\n 1. Buscar contenido visto por usuario");
            printf("\n 2. Promedio de calificaciones por contenido");
            printf("\n 3. Top 5 contenidos mejor calificados");
            printf("\n 4. Usuario con mas visualizaciones");
            printf("\n 5. Contenidos sin visualizaciones");
            printf("\n 0. Volver");
        }else{
            printf("\n 1. Mis visualizaciones");
            printf("\n 2. Mi promedio de calificaciones");
            printf("\n 0. Volver");
        }
        printf("\n\n Opcion: ");
        scanf("%d", &opcion);
        limpiarBufferRep();
        if(esAdmin){
            switch(opcion){
                case 1:
                    buscarContenidoVistoPorUsuario(lista, cantidad,idsUsuarios, nombresUsuarios, totalUsuarios,idsContenidos, titulos, totalContenidos);
                    break;

                case 2:
                    reportePromedioCalificaciones(lista, cantidad,idsContenidos, titulos, totalContenidos);
                    break;

                case 3:
                    reporteTop5Contenidos(lista, cantidad,idsContenidos, titulos, totalContenidos);
                    break;

                case 4:
                    reporteUsuarioMasVisualizaciones(lista, cantidad,idsUsuarios, nombresUsuarios, totalUsuarios);
                    break;

                case 5:
                    reporteContenidosSinVisualizaciones(lista, cantidad,idsContenidos, titulos, totalContenidos);
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
                    reporteVisualizacionesUsuario(lista, cantidad,idUsuarioLogueado,idsContenidos, titulos, totalContenidos);
                    break;
                case 2:
                    reportePromedioUsuario(lista, cantidad,idUsuarioLogueado);
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
    limpiarBufferRep();

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
///REPORTES PARA ADMINISTRADOR///
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

    printf("\n =====================================================");
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

    printf("\n ==============================================");
}
void reporteUsuarioMasVisualizaciones(stVisualizacion lista[], int cantidad,int *idsUsuarios, char nombresUsuarios[][40],int totalUsuarios)
{

    int maxCant = 0;
    int maxIdx  = -1;

    // Para cada usuario, contar sus visualizaciones activas y quedarse con el mayor
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

    printf("\n ============================================");
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

    printf("\n ==========================================");
}
///REPORTES PARA USUARIO COMUN///
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

    printf("\n =========================================");
}

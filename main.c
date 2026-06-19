#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "Persistencia.h"
#include "Contenido.h"
#include "Generos.h"
#include "USUARIOS.h"
#include "Visualizaciones.h"

// Funcion rustica para ver si mandan puros espacios en blanco
int verificarEspacios(char texto[]) {
    int i = 0;
    if (strlen(texto) == 0) return 1;
    while (texto[i] != '\0') {
        if (texto[i] != ' ' && texto[i] != '\n') return 0; // Tiene letras o numeros
        i++;
    }
    return 1; // Eran puros espacios
}

int main() {
    // Arreglos y contadores normales
    stContenido arreglocontenidos[MAX_CONTENIDOS];
    int cantContenidos = 0;

    stGenero arreglogeneros[MAX_GENEROS];
    int cantGeneros = 0;

    stUsuario arreglousuarios[MAX_USUARIOS];
    int cantUsuarios = 0;

    stVisualizacion arreglovistas[MAX_VISUALIZACIONES];
    int cantVistas = 0;

    // Variables en español
    char correo[50];
    char contra[30];
    int intentos = 0;
    int ingresoExitoso = 0;
    stUsuario usuarioLogueado;
    int esAdministrador = 0;

    // Variables para la brujula
    int opcionBrujula = -1;
    char bufferMenu[10];
    int idsGenerosActivos[MAX_CONTENIDOS];
    int idsContenidosActivos[MAX_CONTENIDOS];
    int totalActivos = 0;

    cargarTodo(arreglocontenidos, &cantContenidos, arreglogeneros, &cantGeneros, arreglousuarios, &cantUsuarios, arreglovistas, &cantVistas);

    if (cantUsuarios == 0) {
        printf("\n No se encontraron usuarios. Registrando el primer administrador...\n");
        cantUsuarios = altaUsuario(arreglousuarios, cantUsuarios, MAX_USUARIOS);
        guardarUsuarios(arreglousuarios, cantUsuarios);
        system("pause");
    }

    // --- LOGIN ---
    do {
        system("cls");
        printf("-------------------------------------------\n");
        printf("          PLATAFORMA DE PELICULAS          \n");
        printf("-------------------------------------------\n");
        printf(" Intentos: %d/3\n\n", intentos);

        printf(" Ingrese su correo: ");
        // Truco antifallos: Leer hasta que haya texto real (ignora enters fantasmas)
        do {
            fgets(correo, sizeof(correo), stdin);
            correo[strcspn(correo, "\n")] = '\0';
        } while (strlen(correo) == 0);

        printf(" Ingrese su contrasenia: ");
        do {
            fgets(contra, sizeof(contra), stdin);
            contra[strcspn(contra, "\n")] = '\0';
        } while (strlen(contra) == 0);

        if (verificarEspacios(correo) == 1 || verificarEspacios(contra) == 1) {
            printf("\n Error: No se puede dejar campos vacios.\n");
            intentos++;
            system("pause");
            continue;
        }

        // Busqueda secuencial del usuario
        for (int i = 0; i < cantUsuarios; i++) {
            if (strcasecmp(arreglousuarios[i].email, correo) == 0 && strcmp(arreglousuarios[i].contrasenia, contra) == 0 && arreglousuarios[i].activo == 1) {
                ingresoExitoso = 1;
                usuarioLogueado = arreglousuarios[i];

                if (strcasecmp(usuarioLogueado.rol, "administrador") == 0) {
                    esAdministrador = 1;
                }
                break;
            }
        }

        if (ingresoExitoso == 0) {
            printf("\n Correo o clave incorrectos.\n");
            intentos++;
            system("pause");
        }

    } while (ingresoExitoso == 0 && intentos < 3);

    if (ingresoExitoso == 0) {
        printf("\n Maximo de intentos superado. Saliendo del sistema.\n");
        return 0;
    }

    // --- MENU PRINCIPAL ---
    do {
        system("cls");
        printf("-------------------------------------------\n");
        printf(" USUARIO: %s | ROL: %s\n", usuarioLogueado.nombre, usuarioLogueado.rol);
        printf("-------------------------------------------\n");
        printf(" 100 - Menu de Contenidos\n");
        printf(" 200 - Menu de Generos\n");
        printf(" 300 - Menu de Usuarios\n");
        printf(" 400 - Menu de Visualizaciones\n");
        printf(" 0   - Guardar todo y salir\n");
        printf("-------------------------------------------\n");
        printf(" Elija un destino: ");

        // Leemos el menú con fgets para no usar scanf y evitar que se trabe
        do {
            fgets(bufferMenu, sizeof(bufferMenu), stdin);
            bufferMenu[strcspn(bufferMenu, "\n")] = '\0';
        } while (strlen(bufferMenu) == 0);

        opcionBrujula = atoi(bufferMenu); // Convierte el texto a número
        if (opcionBrujula == 0 && bufferMenu[0] != '0') {
            opcionBrujula = -1; // Si tipearon letras, forzamos el error
        }

        switch (opcionBrujula) {
           case 100:
                menuContenido(arreglocontenidos, &cantContenidos, arreglogeneros, cantGeneros, arreglovistas, cantVistas, esAdministrador);
                break;

            case 200:
                for(int i = 0; i < cantContenidos; i++) {
                    idsGenerosActivos[i] = arreglocontenidos[i].idGenero;
                }
                menuGeneros(arreglogeneros, &cantGeneros, cantContenidos, idsGenerosActivos, esAdministrador);
                break;

            case 300:
                if (esAdministrador == 1) {
                    menuDeUsuarios(arreglousuarios, &cantUsuarios);
                } else {
                    printf("\n Usted no es administrador. No tiene permiso.\n");
                    system("pause");
                }
                break;

            case 400:
                totalActivos = 0;
                for(int i = 0; i < cantContenidos; i++) {
                    if(arreglocontenidos[i].activo == 1) {
                        idsContenidosActivos[totalActivos] = arreglocontenidos[i].idContenido;
                        totalActivos++;
                    }
                }
                menuVisualizaciones(arreglovistas, &cantVistas, usuarioLogueado.idUsuario, esAdministrador, idsContenidosActivos, totalActivos);
                break;

            case 0:
                printf("\n Guardando los archivos...\n");
                guardarTodo(arreglocontenidos, cantContenidos, arreglogeneros, cantGeneros, arreglousuarios, cantUsuarios, arreglovistas, cantVistas);
                printf(" Archivos guardados. Fin del programa.\n");
                system("pause");
                break;

            default:
                printf("\n Opcion no reconocida. Use las que aparecen en pantalla.\n");
                system("pause");
                break;
        }

    } while (opcionBrujula != 0);

    return 0;
}

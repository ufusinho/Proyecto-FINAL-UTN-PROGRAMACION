#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "USUARIOS.h"
#define MAX_USUARIOS 50


// MENU DE USUARIOS
void menuDeUsuarios(stUsuario usuarios[], int *validos) {
    int opc = 0;
    char auxBusqueda[40];
    char bufferOpc[10];

    do {
        system("cls");
        printf("\n ---// MENU GESTION DE USUARIOS //---\n");
        printf(" 1. Alta de Usuario\n");
        printf(" 2. Baja de Usuario\n");
        printf(" 3. Modificar Usuario\n");
        printf(" 4. Mostrar Lista de Usuarios\n");
        printf(" 0. Volver al Menu Principal\n");
        printf(" --------------------------------\n");
        printf("\n\n");
        printf(" Opcion: ");

        fgets(bufferOpc, sizeof(bufferOpc), stdin);
        opc = atoi(bufferOpc); 

        switch (opc) {
            case 1:
                *validos = altaUsuario(usuarios, *validos, MAX_USUARIOS);
                system("pause");
                break;
            case 2:
                printf("\n Ingrese el nombre del usuario a dar de baja: ");
                do {
                    fgets(auxBusqueda, sizeof(auxBusqueda), stdin);
                    auxBusqueda[strcspn(auxBusqueda, "\n")] = '\0';
                } while(strlen(auxBusqueda) == 0);

                bajaUsuario(usuarios, *validos, auxBusqueda);
                system("pause");
                break;
            case 3:
                printf("\n Ingrese el nombre del usuario a modificar: ");
                do {
                    fgets(auxBusqueda, sizeof(auxBusqueda), stdin);
                    auxBusqueda[strcspn(auxBusqueda, "\n")] = '\0';
                } while(strlen(auxBusqueda) == 0); 

                modificarUsuario(usuarios, *validos, auxBusqueda);
                system("pause");
                break;
            case 4:
                mostrarListaUsuarios(usuarios, *validos);
                system("pause");
                break;
            case 0:
                // no hace nada, sale del dowhile y vuelve al main
                break;
            default:
                if (bufferOpc[0] != '0') {
                    printf("\n Opcion incorrecta.\n");
                    system("pause");
                }
                break;
        }
    } while (opc != 0 || bufferOpc[0] != '0');
}


int buscarUsuarioPorNombreRecursivo(stUsuario usuarios[], int validos, char nombre[], int indice){
    for(int i = indice; i < validos; i++){
        if(strcasecmp(usuarios[i].nombre, nombre) == 0){
            return i;
        }
    }
    return -1;
}

int buscarMaximoIdUsuario(stUsuario usuarios[], int validos){
    int maxId = 0;
    for(int i = 0; i < validos; i++ ){
        if(usuarios[i].idUsuario > maxId) {
            maxId = usuarios[i].idUsuario;
        }
    }
    return maxId;
}

int verificarEmailUnico(stUsuario usuarios[], int validos, char email[]){
    int unico = 1;
    for(int i = 0; i < validos; i++ ){
        if(strcasecmp(usuarios[i].email, email) == 0){
            unico = 0;
        }
    }
    return unico;
}

int validarContrasenia(char contrasenia[]){
    int valida = 0;
    if(strlen(contrasenia) >= 6){
        valida = 1;
    }
    return valida;
}

int contarAdministradoresActivos(stUsuario usuarios[], int validos){
    int contador = 0;
    for(int i = 0; i < validos; i++){
        if(strcmp(usuarios[i].rol, "administrador") == 0 && usuarios[i].activo == 1){
            contador++;
        }
    }
    return contador;
}

int altaUsuario(stUsuario usuarios[], int validos, int dimension){
    if (validos >= dimension) {
        printf("Error, no hay espacio en memoria para mas usuarios.,..\n");
        return validos;
    }
    stUsuario nuevo;
    char auxEmail[50];
    char auxContrasenia[30];
    char bufferRol[10];
    int opcionRol = 0;

    printf("\n------- ALTA DE NUEVO USUARIO -----");

    nuevo.idUsuario = buscarMaximoIdUsuario(usuarios, validos) + 1;

    do {
        printf("\nIngrese el nombre: ");
        fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
        nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
    } while(strlen(nuevo.nombre) == 0); 

    do {
        do {
            printf("Ingrese el email: ");
            fgets(auxEmail, sizeof(auxEmail), stdin);
            auxEmail[strcspn(auxEmail, "\n")] = '\0';
        } while(strlen(auxEmail) == 0); 
        if(!verificarEmailUnico(usuarios, validos, auxEmail)){
            printf("\nError. El email se encuentra registrado. Intenta con otro...\n");
        }
    } while(!verificarEmailUnico(usuarios, validos, auxEmail));
    strcpy(nuevo.email, auxEmail);

    do {
        do {
            printf("Ingrese la contrasenia (minimo 6 caracteres): ");
            fgets(auxContrasenia, sizeof(auxContrasenia), stdin);
            auxContrasenia[strcspn(auxContrasenia, "\n")] = '\0';
        } while(strlen(auxContrasenia) == 0); 

        if(!validarContrasenia(auxContrasenia)){
            printf("\nLa contrasenia es demasiado corta\n");
        }
    } while (!validarContrasenia(auxContrasenia));
    strcpy(nuevo.contrasenia, auxContrasenia);

    do {
        printf("Seleccione Rol (1: administrador / 2: comun): ");
        fgets(bufferRol, sizeof(bufferRol), stdin);
        opcionRol = atoi(bufferRol);

        if (opcionRol == 1) {
            strcpy(nuevo.rol, "administrador");
        } else if (opcionRol == 2) {
            strcpy(nuevo.rol, "comun");
        } else {
            printf("Opcion invalida\n");
        }
    } while (opcionRol != 1 && opcionRol != 2);

    nuevo.activo = 1;
    usuarios[validos] = nuevo;
    printf("\nUsuario creado con exito. ID asignado: %d\n", nuevo.idUsuario);
    return validos + 1;
}

int bajaUsuario(stUsuario usuarios[], int validos, char nombreBuscar[]) {
    int eliminado = 0;
    int indice = buscarUsuarioPorNombreRecursivo(usuarios, validos, nombreBuscar, 0);
    if(indice != -1) {
        if(usuarios[indice].activo == 0) {
            printf("\nEl usuario ya esta dado de baja.\n");
            eliminado = -1;
        } else if (strcmp(usuarios[indice].rol, "administrador") == 0 && contarAdministradoresActivos(usuarios, validos) <= 1){
            printf("\nNo se puede eliminar al unico administrador activo..");
            eliminado = -1;
        } else {
            usuarios[indice].activo = 0;
            printf("\nUsuario %s dado de baja correctamente.\n", nombreBuscar);
            eliminado = 1;
        }
    } else {
        printf("\nUsuario no encontrado.\n");
    }
    return eliminado;
}

void modificarUsuario(stUsuario usuarios[], int validos, char nombreBuscar[]) {
    int indice = buscarUsuarioPorNombreRecursivo(usuarios, validos, nombreBuscar, 0);

    if (indice == -1) {
        printf("\nUsuario no encontrado.\n");
        return;
    }

    if (usuarios[indice].activo == 0) {
        printf("\nNo se puede modificar un usuario inactivo.\n");
        return;
    }

    char entrada[50];
    char bufferRol[10];
    int opcionRol = 0;

    printf("\n--- MODIFICANDO USUARIO: %s (Deje vacio y presione Enter para no cambiar) ---\n", usuarios[indice].nombre);

    printf("Nombre actual: %s\nNuevo nombre: ", usuarios[indice].nombre);
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';
    if (strlen(entrada) > 0) {
        strcpy(usuarios[indice].nombre, entrada);
    }

    do {
        printf("Email actual: %s\nNuevo email: ", usuarios[indice].email);
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strlen(entrada) > 0 && strcasecmp(usuarios[indice].email, entrada) != 0) {
            if (!verificarEmailUnico(usuarios, validos, entrada)) {
                printf("Error: Ese email ya pertenece a otro usuario!!!\n");
            } else {
                strcpy(usuarios[indice].email, entrada);
                break;
            }
        } else {
            break;
        }
    } while (1);

    do {
        printf("Contrasenia actual  : %s\nNueva contrasenia: ", usuarios[indice].contrasenia);
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strlen(entrada) > 0) {
            if (validarContrasenia(entrada)) {
                strcpy(usuarios[indice].contrasenia, entrada);
                break;
            } else {
                printf("Error: Contrasenia invalida (minimo 6 caracteres)\n");
            }
        } else {
            break;
        }
    } while (1);

    if (strcmp(usuarios[indice].rol, "administrador") == 0 && contarAdministradoresActivos(usuarios, validos) <= 1) {
        printf("Rol actual: %s (Protegido por ser el unico administrador activo!!!)\n", usuarios[indice].rol);
    } else {
        do {
            printf("    Rol actual: %s\n    Nuevo Rol   (1: administrador / 2: comun / 0: No cambiar): ", usuarios[indice].rol);
            fgets(bufferRol, sizeof(bufferRol), stdin);
            bufferRol[strcspn(bufferRol, "\n")] = '\0';

            if(strlen(bufferRol) == 0 || bufferRol[0] == '0') {
                break; 
            }

            opcionRol = atoi(bufferRol);

            if (opcionRol == 1) {
                strcpy(usuarios[indice].rol, "administrador");
                break;
            } else if (opcionRol == 2) {
                strcpy(usuarios[indice].rol, "comun");
                break;
            } else {
                printf("Opcion invalida.\n");
            }
        } while (1);
    }

    printf("\n    Proceso de modificacion finalizado\n");
}

// ORDENAR USUARIOS POR NOMBRE
void ordenarUsuariosPorNombre(stUsuario usuarios[], int validos) {
    int i, j;
    stUsuario aux;
    for(i = 0; i < validos - 1; i++){
        for(j = 0; j < validos - i - 1; j++){
            if(strcasecmp(usuarios[j].nombre, usuarios[j + 1].nombre) > 0){
                aux = usuarios[j];
                usuarios[j] = usuarios[j + 1];
                usuarios[j + 1] = aux;
         }
     }
  }
}

// MOSTRAR LISTA DE USUARIOS
void mostrarListaUsuarios(stUsuario usuarios[], int validos) {
    ordenarUsuariosPorNombre(usuarios, validos);
    printf("\nID / Nombre / Email / Rol\n");
    for (int i = 0; i < validos; i++) {
        if (usuarios[i].activo == 1) {
            printf("%d / %s / %s / %s\n",
                usuarios[i].idUsuario,
               usuarios[i].nombre,
               usuarios[i].email,
               usuarios[i].rol);
        }
    }
}


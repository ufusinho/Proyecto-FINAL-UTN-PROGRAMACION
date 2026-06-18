#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "USUARIOS.h"

int buscarUsuarioPorNombreRecursivo(stUsuario usuarios[], int validos, char nombre[], int indice){ // se elimino llamada recursiva para evitar consumo innecesario.
    for(int i = indice; i < validos; i++){
        if(strcasecmp(usuarios[i].nombre, nombre) == 0){
          return i;
       }
    }
    return -1;
}
  return buscarUsuarioPorNombreRecursivo(usuarios, validos, nombre, indice + 1);
 } 

int buscarMaximoIdUsuario(stUsuario usuarios[], int validos){
int maxId = 0;
     for(int i = 0; i < validos; i++ ){
         if(usuarios[i].idUsuario > maxId) {
            maxId = usuarios[i].idUsuario;
        } // recorre hasta reemplazar maxid con el nuievo maximo.
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
    printf("Error, no hay espacio en memoria para mas usuarios...\n");
    return validos;
 }
  stUsuario nuevo;
  char auxEmail[50];
  char auxContrasenia[30];
  int opcionRol = 0;

  printf("\n------- ALTA DE NUEVO USUARIO ---");

  nuevo.idUsuario = buscarMaximoIdUsuario(usuarios, validos) + 1;
  ///------------NOMBRE
  printf("\nIngrese el nombre ");
  fflush(stdin);
  fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
  nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
  ///----------EMAIL-------
    
  do {
    printf("\nIngrese el email : ");
    fflush(stdin);
    fgets(auxEmail, sizeof(auxEmail), stdin);
    auxEmail[strcspn(auxEmail, "\n")] = '\0';

    if(!verificarEmailUnico(usuarios, validos, auxEmail)){
      printf("\nError. El email se encuentra registrado. Intenta con otro...\n");
    }
  } while(!verificarEmailUnico(usuarios, validos, auxEmail));
          strcpy(nuevo.email, auxEmail);

  do {
      printf("Ingrese la contrasenia (mininmo 6 caracteres): ");
      fflush(stdin);
      fgets(auxContrasenia, sizeof(auxContrasenia), stdin);
      auxContrasenia[strcspn(auxContrasenia, "\n")] = '\0';

    if(!validarContrasenia(auxContrasenia)){
        printf("\nLa contraseña es demasiado corta.\n");
     }

  } while (!validarContrasenia(auxContrasenia));
          strcpy(nuevo.contrasenia, auxContrasenia);
 do {
        printf("Seleccione Rol (1: administrador / 2: comun): ");
        fflush(stdin);
        scanf("%d", &opcionRol);
        if (opcionRol == 1) {
            strcpy(nuevo.rol, "administrador");
        } else if (opcionRol == 2) {
            strcpy(nuevo.rol, "comun");
        } else {
            printf("Opcion invalida.\n");
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
    }     else if (strcmp(usuarios[indice].rol, "administrador") == 0 && contarAdministradoresActivos(usuarios, validos)<= 1){
                   printf("\nNo se puede eliminar al unico administrador activo..");
                   eliminado = -1;
        } else {
          usuarios[indice].activo = 0;
            printf("\nUsuario %s dado de baja correctamente.\n", nombreBuscar);
           eliminado = 1;
      }
   }   else {
          printf("\nUsuario no encontrado.\n");
    }
          return eliminado;
}

void modificarUsuario(stUsuario usuarios[], int validos, char nombreBuscar[]){ // a terminar..
}

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

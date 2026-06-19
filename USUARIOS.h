#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

typedef struct {
    int idUsuario;
    char nombre[40];
    char email[50];
    char contrasenia[30];
    char rol[15];
    int activo;
} stUsuario;

int buscarUsuarioPorNombreRecursivo(stUsuario usuarios[], int validos, char nombre[], int indice);
int buscarMaximoIdUsuario(stUsuario usuarios[], int validos);
int verificarEmailUnico(stUsuario usuarios[], int validos, char email[]);
int validarContrasenia(char contrasenia[]);
int contarAdministradoresActivos(stUsuario usuarios[], int validos);
int altaUsuario(stUsuario usuarios[], int validos, int dimension);
int bajaUsuario(stUsuario usuarios[], int validos, char nombreBuscar[]);
void modificarUsuario(stUsuario usuarios[], int validos, char nombreBuscar[]);
void ordenarUsuariosPorNombre(stUsuario usuarios[], int validos);
void mostrarListaUsuarios(stUsuario usuarios[], int validos);
void menuDeUsuarios(stUsuario usuarios[], int *validos);

#endif

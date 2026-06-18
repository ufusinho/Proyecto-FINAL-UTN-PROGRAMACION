#ifndef PERSISTENCIA_H_INCLUDED
#define PERSISTENCIA_H_INCLUDED

#include "Contenido.h"
#include "Generos.h"
#include "USUARIOS.h"
#include "Visualizaciones.h"

/// Contenidos
int cargarContenido(stContenido contenidos[], int *validosContenidos);
int guardarContenidos(stContenido contenidos[], int validosContenidos);

/// Generos
int cargarGeneros(stGenero lista[], int *cantidad);
int guardarGeneros(stGenero lista[], int cantidad);
/// Usuarios
int cargarUsuarios(stUsuario usuarios[], int *validosUsuarios);
int guardarUsuarios(stUsuario usuarios[], int validosUsuarios);

/// Visualizaciones
int cargarVisualizaciones(stVisualizacion lista[], int *cantidad);
int guardarVisualizaciones(stVisualizacion lista[], int cantidad);

/// General
void cargarTodo(stContenido contenidos[], int *validosContenidos, stGenero generos[], int *validosGeneros, stUsuario usuarios[], int *validosUsuarios, stVisualizacion visualizaciones[], int *validosVisualizaciones);
void guardarTodo(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros, stUsuario usuarios[], int validosUsuarios, stVisualizacion visualizaciones[], int validosVisualizaciones);

#endif // PERSISTENCIA_H_INCLUDED

#ifndef CONTENIDO_H_INCLUDED
#define CONTENIDO_H_INCLUDED

#include "Generos.h"
#include "Visualizaciones.h"

/// Estructuras.

typedef struct {
    int  idContenido;
    char titulo[60];
    char tipo[10];
    int  anio;
    int  idGenero;
    char sinopsis[300];
    int  duracion;
    int  estado;
    int  activo;
} stContenido;


/// Prototipados.

// Alta de contenido.
int obtenerProximoIDContenido(stContenido contenidos[], int validos);
int existenciaDeTitulo(stContenido contenidos[], int validos, char titulo[]);
int seleccionDeTipoContenido(void);
int cargarDuracionPelicula(void);
int cargarEstadoDeSerie(void);
int cargarAnio(void);
void mostrarGeneros(stGenero generos[], int validosGeneros);
int existenciaDeGenero(stGenero generos[], int validosGeneros, int idGenero);
int seleccionarGenero(stGenero generos[], int validosGeneros);
stContenido cargarUnContenido(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros);
stContenido *altaContenido(stContenido contenidos[], int *validosContenidos, stGenero generos[], int validosGeneros);

// Baja de contenido.
void mostrarContenido(stContenido contenido);
int verificarVisualizaciones(stVisualizacion visualizaciones[], int validosVisualizaciones, int idContenido);
int buscarPosicionContenido(stContenido contenidos[], int validos, int idContenido);
void bajaDeContenido(stContenido contenidos[], int validosContenidos, stVisualizacion visualizaciones[], int validosVisualizaciones);

// Modificaciones.
void menuDeModificaciones(void);
int existenciaDeTituloExceptoID(stContenido contenidos[], int validos, char titulo[], int idContenido);
void modificarDatosDeContenidos(stContenido *contenidoActual, stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros);
void modificarContenido(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros);

// Consulta y listado.
void consultarContenidoPorTitulo(stContenido contenidos[], int validosContenidos);
void consultarContenidoPorID(stContenido contenidos[], int validosContenidos);
void listarPeliculas(stContenido contenidos[], int validosContenidos);
void listarSeries(stContenido contenidos[], int validosContenidos);
void listarPorGenero(stContenido contenidos[], int validosContenidos, stGenero generos[], int validosGeneros);
void listarContenidoActivo(stContenido contenidos[], int validosContenidos);

#endif // CONTENIDO_H_INCLUDED

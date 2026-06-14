#ifndef CONTENIDO_H_INCLUDED
#define CONTENIDO_H_INCLUDED

/// Estructuras.
// Estructura contenidos:
typedef struct {
    int  idContenido;
    char titulo[60];     // unico
    char tipo[10];       // "pelicula" o "serie"
    int  anio;
    int  idGenero;       // referencia a stGenero.idGenero
    char sinopsis[300];
    int  duracion;       // minutos (solo para peliculas, entre 40 y 300)
    int  estado;         // 0=finalizada, 1=en emision (solo para series)
    int  activo;
} stContenido;

/// Prototipados.
// Alta de contenido.
int obtenerProximoIDContenido(char archivo[]);
stContenido cargarUnContenido(char archivoGenero[], char archivoContenido[]);
int existenciaDeTitulo(char archivo[], char titulo[]);
int seleccionDeTipoContenido();
int cargarDuracionPelicula();
int cargarEstadoDeSerie();
int cargarAnio();
void mostrarGeneros(char archivoGeneros[]);
int existenciaDeGenero(char archivoGeneros[], int idGenero);
int seleccionarGenero(char archivoGeneros[]);
void guardarUnContenido(char archivoContenido[], stContenido nuevoContenido);
// Baja de contenido.
void mostrarContenido(stContenido contenido);
int verificarVisualizaciones(char archivoVisualizaciones[], int idContenido);
int buscarPosicionContenido(char archivoContenidos[], int idContenidos);
void bajaDeContenido(char archivoContenidos[], char archivoVisualizacion[]);
// Modificaciones.
void menuDeModificaciones();
void modificarDatosDeContenidos(stContenido *contenido, char archivoContenidos[], char archivoGenero[]);
void modificarContenido(char archivoContenido[], char archivoGenero[]);
// Consulta y listado.
void consultarContenidoPorTitulo(char archivoContenido[]);
void listarPeliculas(char archivoContenido[]);
void listarSeries(char archivoContenido[]);
void listarPorGenero(char archivoContenido[], char archivoGeneros[]);
void consultarContenidoPorID(char archivoContenido[]);
void listarContenidoActivo(char archivoContenidos[]);

#endif // CONTENIDO_H_INCLUDED

#ifndef VISUALIZACIONES_H_INCLUDED
#define VISUALIZACIONES_H_INCLUDED

#define ARCHIVO_VISUALIZACIONES "visualizaciones.dat"
#define MAX_VISUALIZACIONES     500

typedef struct {
    int idVisualizacion;
    int idUsuario;      // referencia a stUsuario.idUsuario
    int idContenido;    // referencia a stContenido.idContenido
    int fechaDia;
    int fechaMes;
    int fechaAnio;
    int calificacion;   // 1 a 10
    int activo;
} stVisualizacion;

// Cargar y guardar
int  cargarVisualizaciones(stVisualizacion lista[], int *cantidad);
int  guardarVisualizaciones(stVisualizacion lista[], int cantidad);
// Auxiliares
int  generarIDVisualizacion(stVisualizacion lista[], int cantidad);
int  buscarVisualizacionDuplicada(stVisualizacion lista[], int cantidad,int idUsuario, int idContenido,int dia, int mes, int anio);
int  validarFecha(int dia, int mes, int anio);
int  cargarCalificacion(void);
void cargarFecha(int *dia, int *mes, int *anio);
// ABM
void altaVisualizacion(stVisualizacion lista[], int *cantidad,int idUsuarioLogueado,int *idsContenidosActivos, int totalActivos);
void bajaVisualizacion(stVisualizacion lista[], int cantidad,int idUsuarioLogueado, int esAdmin);
// Consulta y listado
void listarVisualizaciones(stVisualizacion lista[], int cantidad,int idUsuarioLogueado, int esAdmin);
#endif

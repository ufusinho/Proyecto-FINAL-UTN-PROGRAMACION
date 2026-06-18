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
// Reportes
void reportePromedioCalificaciones(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos);
void reporteTop5Contenidos(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos);
void reporteUsuarioMasVisualizaciones(stVisualizacion lista[], int cantidad,int *idsUsuarios, char nombresUsuarios[][40],int totalUsuarios);
void reporteContenidosSinVisualizaciones(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos);
void reporteVisualizacionesUsuario(stVisualizacion lista[], int cantidad,int idUsuario,int *idsContenidos, char titulos[][60],int totalContenidos);
void reportePromedioUsuario(stVisualizacion lista[], int cantidad, int idUsuario);
//Busqueda para admin
void buscarContenidoVistoPorUsuario(stVisualizacion lista[], int cantidad,int *idsUsuarios, char nombresUsuarios[][40],int totalUsuarios,int *idsContenidos, char titulos[][60],int totalContenidos);
#endif

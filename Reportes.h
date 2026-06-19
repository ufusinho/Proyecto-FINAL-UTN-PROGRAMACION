#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED
#include "Visualizaciones.h"

void buscarContenidoVistoPorUsuario(stVisualizacion lista[], int cantidad,int *idsUsuarios,char nombresUsuarios[][40],int totalUsuarios,int *idsContenidos, char titulos[][60],int totalContenidos);
// Reportes para administrador
void reportePromedioCalificaciones(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos);
void reporteTop5Contenidos(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos);
void reporteUsuarioMasVisualizaciones(stVisualizacion lista[], int cantidad,int *idsUsuarios, char nombresUsuarios[][40],int totalUsuarios);
void reporteContenidosSinVisualizaciones(stVisualizacion lista[], int cantidad,int *idsContenidos, char titulos[][60],int totalContenidos);
// Reportes para usuario comun
void reporteVisualizacionesUsuario(stVisualizacion lista[], int cantidad,int idUsuario,int *idsContenidos, char titulos[][60],int totalContenidos);
void reportePromedioUsuario(stVisualizacion lista[], int cantidad, int idUsuario);

#endif //

PROYECTO FINAL UTN PROGRAMACION
Emiliano Ramirez - Tomas Aguer
# Sistema de Gestion de Plataforma Audiovisual

Trabajo Practico Final para la asignatura Programacion I de la Tecnicatura Universitaria en Programacion (UTN FRMDP).

Este proyecto consiste en un sistema de consola desarrollado en lenguaje C que simula las operaciones principales de una plataforma de streaming. Permite la administracion de usuarios, catalogos de contenido (peliculas y series), y el registro de visualizaciones mediante persistencia en archivos binarios.

## Caracteristicas Principales

### Gestion de Usuarios y Autenticacion
* Control de acceso basado en roles: Administrador y Usuario Comun.
* Sistema de login con control de intentos y manejo de sesion activa.
* Modulo ABM de usuarios con validaciones de unicidad de email y longitud de contraseñas.
* Proteccion del sistema ante la baja del ultimo administrador activo.
* Archivos.
-- Gestion de Catalogo de Contenido
* Administracion de generos independientes con validacion de integridad referencial.
* Alta y modificacion de peliculas y series con controles especificos (duracion por minutos para peliculas y estado de emision para series).
* Control de bajas logicas para evitar la perdida de consistencia en el historico de datos.

-- Registro de Visualizaciones y Reportes
* Registro detallado de contenidos vistos por fecha, asociando usuario, pelicula/serie y calificacion.
* Control de duplicados que actualiza la calificacion existente si se registra el mismo contenido en la misma fecha.
* Busquedas avanzadas y listados ordenados alfabeticamente en memoria.
* Generacion de reportes estadisticos: calculo de promedios de calificaciones, listado de contenidos no vistos y deteccion del top 5 de contenidos mejor puntuados.

-- Tecnicas de Programacion Aplicadas

* Estructuras de datos personalizadas (struct) y arreglos de estructuras.
* Modulo de busqueda implementado mediante algoritmos recursivos.
* Persistencia completa de datos en disco utilizando archivos binarios (.dat).
* Modularizacion estricta separando los prototipos e implementaciones en archivos .h y .c independientes por responsabilidad.
* Manejo seguro de flujos de entrada de texto mediante fgets y limpieza automatica de buffers.

-- Organizacion del Codigo

El proyecto mantiene la siguiente estructura de directorios recomendada:

proyecto/
├── main.c
├── usuarios/
│   ├── usuarios.h
│   └── usuarios.c
├── generos/
│   ├── generos.h
│   └── generos.c
├── contenido/
│   ├── contenido.h
│   └── contenido.c
├── visualizaciones/
│   ├── visualizaciones.h
│   └── visualizaciones.c
├── reportes/
│   ├── reportes.h
│   └── reportes.c
├── autenticacion/
│   ├── autenticacion.h
│   └── autenticacion.c
├── persistencia/
│   ├── persistencia.h
│   └── persistencia.c
└── utils/
    ├── utils.h
    └── utils.c

### Prerrequisitos
* Entorno de desarrollo compatible con C (se recomienda Code::Blocks).
* Compilador GCC instalado.

### Compilacion y Ejecucion
1. Clonar el repositorio en tu espacio local.
2. Abrir el archivo de proyecto (.cbp) en Code::Blocks.
3. Asegurarse de que todos los archivos .c de las subcarpetas esten incluidos en los targets de compilacion (Debug y Release).
4. Compilar y ejecutar el proyecto (Build and Run).

Al iniciar por primera vez, el sistema creara automaticamente los archivos binarios vacios si estos no existen en el directorio de ejecucion.

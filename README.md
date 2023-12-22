# Proyecto final semestre

Bienvenidos al proyecto de final de semestre de Programación 1, este consiste en desarrollar un videojuego que cumpla los parametros requiridos por el profesorados.

El juego esta desarrollado en el lenguaje **C** usando la libreria gráfica **TIGR**. Es compatible con plataformas **MacOs** y **Linux**.

## Estructura del proyecto

Este proyecto parte de la idea del uso del sistema VCS (Software de Control de Versiones, en ingles) **Git** y el uso de varias librerias estadísticas, es decir, la compartimentación del código en varios archivos `.c` o `.h`.

El proyecto cuenta con la siguiente estructura de archivos:

- Final_Semestre:
    - **bin**:
        - ejecutable del juego.
    - **src**:
        - archivos `.c` y `.h` del codigo fuente, además de archivo **makefile** para poder configurar, compilar y correr el proyecto.
    - **wiki**: archivos con información sobre la libreria **TIGR**.
    - archivos varios como **.gitignore** o el `README.md` que sirven de información para el proyecto.

## Información relevante

Para poder correr y compilar y el juego es necesario entender de forma muy básica el archivo makefile dentro de la carpeta src.
El archivo makefile sirve para simplificar el proceso a la hora de compilar cualquier proyecto de tal forma que no haya que escribir enormes comandos en la terminal.

Si se invoca el comando `make help` se mostrara todos los comandos disponibles pero en este caso solo nos importara el comando `make all` y el `make run`, los cuales compilaran el proyecto y lo correran.

Por tanto las instrucciones para correr el proyecto son:

1. Entrar en la carpeta `src`.
2. Invocar el comando `make all`.
3. Invocar el comando `make run`. 


## Extra

Para encontrar más información sobre la base de codigo ver este [archivo](wiki/TIGR.md)

Para ver la explicación del ejemplo básico ver este [archivo](wiki/example.md)

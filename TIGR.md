# Documentación de la biblioteca TIGR
===================================

## Funciones de ventana
--------------------

-   `Tigr *tigrWindow(int w, int h, const char *title, int flags)`: Crea una ventana respaldada por un mapa de bits con el ancho `w`, la altura `h` y el título `title`. Los `flags` pueden ser 0 para una ventana normal o `TIGR_FIXED` para una ventana de tamaño fijo.

-   `void tigrFree(Tigr *bmp)`: Libera los recursos asociados con un mapa de bits o una ventana.

-   `int tigrClosed(Tigr *bmp)`: Devuelve 1 si el usuario ha cerrado la ventana, 0 en caso contrario.

-   `void tigrUpdate(Tigr *bmp)`: Actualiza la ventana con los contenidos del mapa de bits.

## Funciones de dibujo
-------------------

-   `void tigrClear(Tigr *bmp, TPixel color)`: Llena el mapa de bits con un color.

-   `void tigrPlot(Tigr *bmp, int x, int y, TPixel color)`: Dibuja un píxel en el mapa de bits.

-   `void tigrLine(Tigr *bmp, int x0, int y0, int x1, int y1, TPixel color)`: Dibuja una línea en el mapa de bits.

-   `void tigrRect(Tigr *bmp, int x, int y, int w, int h, TPixel color)`: Dibuja un rectángulo en el mapa de bits.

-   `void tigrFill(Tigr *bmp, int x, int y, int w, int h, TPixel color)`: Rellena un rectángulo en el mapa de bits.

-   `void tigrBlit(Tigr *dst, Tigr *src, int dx, int dy, int sx, int sy, int w, int h)`: Copia un rectángulo de un mapa de bits a otro.

-   `void tigrPrint(Tigr *bmp, TigrFont *font, int x, int y, TPixel color, const char *text, ...)`: Dibuja texto en el mapa de bits.

## Funciones de entrada
--------------------

-   `int tigrKeyDown(Tigr *bmp, int key)`: Devuelve 1 si la tecla está presionada, 0 en caso contrario.

-   `int tigrKeyHeld(Tigr *bmp, int key)`: Devuelve 1 si la tecla se mantiene presionada, 0 en caso contrario.

-   `int tigrMouse(Tigr *bmp, int *x, int *y)`: Devuelve el estado de los botones del ratón y llena `x` e `y` con la posición del ratón.

## Funciones de carga y guardado
-----------------------------

-   `Tigr *tigrLoad(const char *fileName)`: Carga un mapa de bits desde un archivo PNG.

-   `void tigrSave(Tigr *bmp, const char *fileName)`: Guarda un mapa de bits en un archivo PNG.

Por favor, ten en cuenta que esta es solo una descripción básica de las funciones. Te recomendaría que consultes la documentación oficial de TIGR para obtener información más detallada y actualizada.

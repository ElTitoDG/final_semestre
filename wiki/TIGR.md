# Biblioteca TIGR - Descripción General

## Tipos de Datos

1. **TPixel:**
   - Estructura que representa un píxel con componentes de color (rojo, verde, azul y alfa).

2. **Tigr:**
   - Estructura que representa un mapa de bits (bitmap) con las siguientes propiedades:
      - `int w, h`: Ancho y alto del mapa de bits (sin escalar).
      - `int cx, cy, cw, ch`: Rectángulo de recorte.
      - `TPixel *pix`: Datos de píxeles.
      - `void *handle`: Identificador de ventana del sistema operativo (NULL para mapas de bits fuera de pantalla).
      - `int blitMode`: Modo de copia del mapa de bits.

3. **TigrGlyph:**
   - Estructura que representa información sobre un glifo en una fuente, incluyendo:
      - `int code`: Código del carácter.
      - `int x, y, w, h`: Posición y dimensiones del glifo.

4. **TigrFont:**
   - Estructura que representa una fuente, compuesta por:
      - `Tigr *bitmap`: Mapa de bits de la fuente.
      - `int numGlyphs`: Número de glifos.
      - `TigrGlyph *glyphs`: Lista de glifos.

5. **TigrTouchPoint:**
   - Estructura que representa un punto de contacto en una pantalla táctil, con propiedades `int x` e `int y`.

## Funciones Principales

### Ventana y Bitmap

- `Tigr* tigrWindow(int w, int h, const char *title, int flags)`: Crea una nueva ventana con un tamaño de mapa de bits dado y devuelve un puntero a ella.
- `Tigr* tigrBitmap(int w, int h)`: Crea un mapa de bits fuera de pantalla y devuelve un puntero a él.
- `void tigrFree(Tigr *bmp)`: Libera la memoria asociada con una ventana o mapa de bits.

### Dibujo

- `void tigrPlot(Tigr *bmp, int x, int y, TPixel pix)`: Dibuja un píxel en un mapa de bits.
- `void tigrClear(Tigr *bmp, TPixel color)`: Limpia un mapa de bits con un color específico.
- `void tigrFill(Tigr *bmp, int x, int y, int w, int h, TPixel color)`: Rellena un área rectangular con un color dado.
- `void tigrLine(Tigr *bmp, int x0, int y0, int x1, int y1, TPixel color)`: Dibuja una línea desde un punto a otro.
- `void tigrRect(Tigr *bmp, int x, int y, int w, int h, TPixel color)`: Dibuja un rectángulo sin relleno.
- `void tigrFillRect(Tigr *bmp, int x, int y, int w, int h, TPixel color)`: Rellena un rectángulo con un color dado.
- `void tigrCircle(Tigr *bmp, int x, int y, int r, TPixel color)`: Dibuja un círculo sin relleno.
- `void tigrFillCircle(Tigr *bmp, int x, int y, int r, TPixel color)`: Rellena un círculo con un color dado.
- `void tigrBlit(Tigr *dest, Tigr *src, int dx, int dy, int sx, int sy, int w, int h)`: Copia datos de mapa de bits de origen a destino.

### Texto y Fuente

- `TigrFont* tigrLoadFont(Tigr *bitmap, int codepage)`: Carga una fuente en memoria y devuelve un puntero a ella.
- `void tigrFreeFont(TigrFont *font)`: Libera la memoria asociada con una fuente.
- `void tigrPrint(Tigr *dest, TigrFont *font, int x, int y, TPixel color, const char *text, ...)`: Imprime texto en un mapa de bits usando una fuente.

### Entrada del Usuario

- `void tigrMouse(Tigr *bmp, int *x, int *y, int *buttons)`: Obtiene la entrada del mouse para una ventana.
- `int tigrTouch(Tigr *bmp, TigrTouchPoint* points, int maxPoints)`: Lee la entrada táctil para una ventana y devuelve el número de puntos leídos.
- `int tigrKeyDown(Tigr *bmp, int key)`: Retorna no-cero si una tecla está presionada.
- `int tigrKeyHeld(Tigr *bmp, int key)`: Retorna no-cero si una tecla está sostenida.
- `int tigrReadChar(Tigr *bmp)`: Obtiene el valor Unicode de la última tecla presionada.

### Tiempo y Manejo de Errores

- `float tigrTime()`: Devuelve el tiempo transcurrido desde la última llamada.
- `void tigrError(Tigr *bmp, const char *message, ...)`: Muestra un mensaje de error y finaliza la aplicación.

### Archivo

- `void* tigrReadFile(const char *fileName, int *length)`: Lee un archivo completo en memoria y devuelve un puntero a los datos.
- `int tigrInflate(void *out, unsigned outlen, const void *in, unsigned inlen)`: Descomprime datos DEFLATE comprimidos.

### UTF-8

- `const char* tigrDecodeUTF8(const char *text, int *cp)`: Decodifica un punto de código UTF-8 y devuelve el puntero a la siguiente posición.
- `char* tigrEncodeUTF8(char *text, int cp)`: Codifica un punto de código UTF-8 y devuelve el puntero a la siguiente posición.

## Constantes y Macros Adicionales

- Varias constantes, como modos de ventana, modos de mezcla y códigos de teclas en la enumeración `TKey`.
- Macros para configuración específica del compilador y definición de funciones en línea.

Esta biblioteca proporciona un conjunto básico de funciones para la manipulación de gráficos, entrada del usuario y manipulación de fuentes. Es adecuada para proyectos pequeños y prototipos donde se requiera una interfaz gráfica simple.

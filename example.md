# Análisis del Código de ejemplo en C

### Variables Globales:
- `float playerx, playery`: Coordenadas del jugador en los ejes x e y.
- `float playerxs, playerys`: Velocidades del jugador en las direcciones x e y.
- `int standing`: Indica si el jugador está de pie en el suelo (1 si está de pie, 0 si no).
- `float remaining`: Tiempo restante para alguna acción (sin contexto específico).
- `Tigr *backdrop, *screen`: Punteros a estructuras de datos TIGR para la imagen de fondo y la pantalla.

### Función `update`:
- Actualiza posición y velocidad del jugador según teclas presionadas y tiempo.
- Cálculos de física para movimiento, gravedad y colisiones con suelo y bordes de ventana.
- Suavizado exponencial para reducir velocidades gradualmente.
- Verifica colisión con suelo y ajusta posición y velocidad.
- Actualiza coordenadas del jugador.

### Función `main`:
- Carga "squinkle.png" como personaje y "greeting.txt" como mensaje de bienvenida.
- Crea ventana gráfica TIGR con propiedades visuales.
- Inicializa imagen de fondo (`backdrop`) con cielo azul, suelo verde y línea blanca.
- Bucle principal para lógica del juego y representación gráfica.
- Lee entrada del mouse para dibujar líneas en la imagen de fondo.
- Dibuja fondo, jugador y mensajes en ventana.
- Actualiza ventana con `tigrUpdate`.

### Bucle Principal:
- Ejecuta hasta cierre de ventana o presión de tecla de escape.
- Llama a `update` para lógica del juego.
- Dibuja fondo, jugador y mensajes en ventana.
- Actualiza ventana con `tigrUpdate`.

### Liberación de Recursos:
- Libera memoria utilizada por imágenes y ventana antes de salir del programa.

En resumen, el código crea una ventana gráfica simple donde el jugador puede moverse, saltar y dibujar líneas con el mouse. Proporciona un marco para un juego más complejo.


## Función UPDATE

La función **update** es responsable de manejar la lógica del juego y actualizar las posiciones y velocidades del jugador en función de las entradas del usuario y la física simulada. Aquí hay una explicación detallada de cómo funciona esta función:

```
void update(float dt) {
    if (remaining > 0)
        remaining -= dt;

    // Control de salto
    if (standing && tigrKeyDown(screen, TK_SPACE))
        playerys -= 500;

    // Control de movimiento lateral
    if (tigrKeyHeld(screen, TK_LEFT) || tigrKeyHeld(screen, 'A'))
        playerxs -= 10;
    if (tigrKeyHeld(screen, TK_RIGHT) || tigrKeyHeld(screen, 'D'))
        playerxs += 10;

    // Algoritmo de suavizado exponencial para reducir velocidades gradualmente
    playerxs *= exp(-10.0f * dt);
    playerys *= exp(-2.0f * dt);
    playerys += dt * 200.0f;

    // Actualización de posiciones
    float oldx = playerx, oldy = playery;
    playerx += dt * playerxs;
    playery += dt * playerys;

    // Restricciones de los bordes de la ventana
    if (playerx < 8) {
        playerx = 8;
        playerxs = 0;
    }

    if (playerx > screen->w - 8) {
        playerx = screen->w - 8.0f;
        playerxs = 0;
    }

    // Verificación de colisiones con el suelo y ajuste de posiciones y velocidades
    float dx = (playerx - oldx) / 10;
    float dy = (playery - oldy) / 10;
    standing = 0;

    for (int n = 0; n < 10; n++) {
        TPixel p = tigrGet(backdrop, (int)oldx, (int)oldy - 1);
        if (p.r == 0 && p.g == 0 && p.b == 0)
            oldy -= 1;
        p = tigrGet(backdrop, (int)oldx, (int)oldy);
        if (p.r == 0 && p.g == 0 && p.b == 0 && playerys > 0) {
            playerys = 0;
            dy = 0;
            standing = 1;
        }
        oldx += dx;
        oldy += dy;
    }

    // Actualización final de posiciones
    playerx = oldx;
    playery = oldy;
}
```

### Explicación detallada:

1. Manejo del Tiempo:
    - La variable dt representa el tiempo transcurrido desde la última actualización. Se utiliza para realizar cálculos basados en el tiempo.

2. Control de Salto:
    - Si el jugador está en el suelo (standing es verdadero) y se presiona la tecla de espacio, se aplica una velocidad negativa en la dirección y (playerys -= 500) para simular un salto.

3. Control de Movimiento Lateral:
    - Si se mantienen presionadas las teclas de flecha izquierda (TK_LEFT) o 'A', se aplica una velocidad negativa en la dirección x (playerxs -= 10).
    - Si se mantienen presionadas las teclas de flecha derecha (TK_RIGHT) o 'D', se aplica una velocidad positiva en la dirección x (playerxs += 10).

4. Suavizado Exponencial:
    - Las velocidades en las direcciones x e y se suavizan exponencialmente para reducir gradualmente su magnitud.

5. Actualización de Posiciones:
    - Las posiciones del jugador se actualizan en función de las velocidades y el tiempo transcurrido.

6. Restricciones de los Bordes de la Ventana:
    - Se verifica y ajusta la posición del jugador para asegurarse de que no se salga de los bordes de la ventana.

7. Verificación de Colisiones con el Suelo:
    - Se realiza una simulación de colisiones con el suelo (representado por píxeles negros en la imagen de fondo).
        Se ajusta la posición y la velocidad del jugador en consecuencia, y se establece standing en 1 si el jugador está en el suelo.

8. Actualización Final de Posiciones:
    - Se actualizan las posiciones finales del jugador después de las colisiones y restricciones.

En resumen, la función update maneja la lógica del juego, actualiza las posiciones del jugador en función de la entrada del usuario y simula colisiones y física básica.

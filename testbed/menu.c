#include "tigr.h"

//Prototipos



//Main
int main() {
    Tigr *screen = tigrWindow(800, 600, "Salvar a españa de los rojos", 0);

    // Verifica si la ventana se ha creado correctamente
    if (!screen) {
        return -1;  // Sal del programa si hay un error
    }

    // Código para la pantalla de inicio

    while (!tigrClosed(screen)) {
        // Código del bucle principal

        tigrUpdate(screen);  // Actualiza la ventana
    }

    tigrFree(screen);  // Libera la memoria de la ventana
    return 0;
}

//Funciones

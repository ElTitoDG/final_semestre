#include "tigr.h"

int main() {

Tigr *screen = tigrWindow(800, 600, "Liberar a españa de los rojos", 0);

// Verificamos si la ventana se ha creado correctamente.
if (!screen) {
	return -1; //Salimos si hay un error.
}

//Codigo para la patalla de inicio.
while (!tigrClosed(screen)){

	//Codigo del bucle princpal.
	tigrUpdate(screen);

}

tigrFree(screen);
return 0;
}
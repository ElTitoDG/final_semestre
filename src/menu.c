#include<stdio.h>
#include "tigr.h"
#include "core.h"

//Prototipos
void Ventana(Tigr *menu, int x_ventana, int y_ventana);
void Ventana_2(Tigr *instrucciones, int x_instrucciones, int y_instrucciones);

//Main
int main() {

    // Declaración de variables de la ventana
    int x_ventana = 440, y_ventana = 320, x_instrucciones = 200, y_instrucciones = 200;

    Tigr *menu = tigrWindow(x_ventana, y_ventana, "Álvaro eres un mamón", 0);
    
    // Llamada a la función de el menú
    while(!tigrClosed(menu)) {

    Ventana(menu, x_ventana, y_ventana);

    }

// Libera la memoria de la ventana
tigrFree(menu);
    
    return 0;
}

//Funciones
void Ventana(Tigr *menu, int x_ventana, int y_ventana) {

    // Fondo del menú
    tigrFill(menu, 0, 0, x_ventana, y_ventana, tigrRGB(51,161,222));
    tigrFill(menu, 5, 5, 430, 310, tigrRGB(91,88,88));
    // Marco del título
    tigrFill(menu, x_ventana/2-85, 25, 170, 65, tigrRGB(51,161,222));
    tigrFill(menu, x_ventana/2-80, 30, 160, 55, tigrRGB(106,27,154));
    // Marco de dificultad
    tigrFill(menu, x_ventana/2-85, 230, 170, 65, tigrRGB(51,161,222));
    tigrFill(menu, x_ventana/2-80, 235, 160, 55, tigrRGB(106,27,154));
    // Marco de Jugar
    tigrFill(menu, x_ventana/2-85, 145, 170, 65, tigrRGB(51,161,222));
    tigrFill(menu, x_ventana/2-80, 150, 160, 55, tigrRGB(106,27,154));
    tigrPrintScaled(menu, tfont, (x_ventana/2-70), (y_ventana-280),4,4, tigrRGB(255, 234, 0), "BANGO");
    // Texto de dificultad
    tigrPrintScaled(menu, tfont, (x_ventana/2-65), (y_ventana-155),2,3, tigrRGB(255, 234, 0), "CONTROLES");
    // Texto de Jugar
    tigrPrintScaled(menu, tfont, (x_ventana/2-70), (y_ventana-75),4,4, tigrRGB(255, 234, 0), "JUGAR");
    // Actualizar menu
    tigrUpdate(menu);

    if(tigrKeyDown(menu, TK_COMMA)){

        Tigr *menu = tigrWindow(x_ventana, y_ventana, "Álvaro eres un mamón", 0);
        tigrClosed(menu);

        }   

}

void Ventana_2(Tigr *instrucciones, int x_instrucciones, int y_instrucciones) {

//Fondo de las instrucciones
    tigrFill(instrucciones, 0, 0, x_instrucciones, y_instrucciones, tigrRGB(51,161,222));

}
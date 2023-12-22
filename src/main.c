#include "core.h"
#include "shoot.h"
#include "tigr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//HOLAAAA

//Macros necesarias
#define SCREEN_WIDTH 440
#define SCREEN_HEIGHT 320
#define PLAYER_WIDTH 23
#define PLAYER_HEIGHT 22
#define PLAYER_SPEED 5.0f
#define PROJECTILE_SIZE 5
#define PROJECTILE_SPEED 5.0f

// Tipo de datos que definen al jugador
typedef struct {
  float x, y, speed;
} TPlayer;

// Tipo de dato que define al proyectil
typedef struct {
  float x, y, speed;
  int active;
} TProjectile;



// void update(float *dt, float *remaining, Tigr *screen, float *playerx,
//             float *playery, float *playerxs, float *playerys);

// Modulos externos
int menu();
void updatePlayer(TPlayer *player, Tigr *screen);
void drawPlayer(TPlayer *player, Tigr *screen);
void updateProjectiles(TProjectile projectiles[], Tigr *screen);
void drawProjectiles(TProjectile projectiles[], Tigr *screen);
void shoot(TProjectile projectiles[], TPlayer player, Tigr *screen);
void drawEnemy(TPlayer *enemy, Tigr *screen);
void updateEnemy(TPlayer *enemy, Tigr *screen, float enemy_speed);
void updateAndDrawEnemies(TPlayer enemies[], int num_enemies, Tigr *screen, float enemy_speed);
void shootUpdate(TPlayer enemies[], int num_enemies, TProjectile projectiles[], Tigr *screen, float enemy_speed);


int main(int argc, char *argv[]) 
{

  // Variables básicas
  float playerxs = 0, playerys = 0;
  int dif;
  Tigr *screen, *background; //*player


  do {

      //Llamada a la función menú
      dif = menu();

      switch (dif)
      {
      case 1: // Fácil.

        TPlayer enemies[4];

        break;
      
      case 2: // Normal

        TPlayer enemies[6];

        break;
      
      case 3: // Difiícil

        TPlayer enemies[8];

        break;

      }

  } while (dif != 0);
  
  // Crea ventana
  screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bango Game Alpha Test", TIGR_2X);
  background = tigrBitmap(screen->w, screen->h);

  // Inicialización de las structuras con 
  // sus tipos de datos correspondientes
  TPlayer player = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - PLAYER_HEIGHT - 10, 5.0f };

  TPlayer enemies[4] = {
    { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT/2, 5.0f },
    { SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT/3, 4.0f },
    { SCREEN_WIDTH * 3/4.0f, SCREEN_HEIGHT/4, 3.0f },
    { SCREEN_WIDTH * 2/1.0f, SCREEN_HEIGHT/3, 3.0f },
};

  TProjectile projectiles[PROJECTILE_SIZE];

  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    projectiles[i].active = 0;
  }

  // Main background
  tigrClear(background, tigrRGB(30, 132, 73));

  // Green grass
  /* tigrFill(background, 0, player.y - 80, SCREEN_WIDTH, 2, tigrRGB(0, 0, 0)); */

  // White line
  // tigrLine(background, 0, 201, 320, 201, tigrRGB(255, 255, 255));



  // Bucle principal de juego
  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) 
  {
    
    // compose the background
    tigrBlit(screen, background, 0, 0, 0, 0, background->w, background->h);

    updatePlayer(&player, screen);
    updateProjectiles(projectiles, screen);


    shoot(projectiles, player, screen);


    updateAndDrawEnemies(enemies, 4, screen, 0.5);

    shootUpdate(enemies, 4, projectiles, screen, 0.5);

    drawPlayer(&player, screen);
    drawProjectiles(projectiles, screen);
    
   
    // Update screen input
    tigrUpdate(screen);
  }

  float dt = tigrTime();
  printf("Time %f\n", dt);

  system("uname -s");

  tigrFree(screen);
  tigrFree(background);
  return 0;
}

int menu() {
// Creación de la varible dificultad
int dificultad;
do {
printf("************Vienvenido a Bango************\n");
printf("------------------------------------------\n");
printf("Elige una de las siguentes dificultades:\n");
printf("1. Fácil\n");
printf("2. Normal\n");
printf("3. Difícil\n");
pritnf("Elija la dificultad: ");
scanf("%d", &dificultad);

} while (dificultad < 0 || dificultad > 2);

return dificultad;
}
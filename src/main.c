#include "core.h"
#include "shoot.h"
#include "tigr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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



int main(int argc, char *argv[]) 
{

  // Variables básicas
  float playerxs = 0, playerys = 0;
  Tigr *screen, *background;
  
  // Crea ventana
  screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bongo Alpha Test", TIGR_2X);
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


  // Bucle principal de juego
  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) 
  {
    
    updatePlayer(&player, screen);
    updateProjectiles(projectiles, screen);


    shoot(projectiles, player, screen);

    // compose the background
    tigrBlit(screen, background, 0, 0, 0, 0, background->w, background->h);

    updateAndDrawEnemies(enemies, 4, screen, 0.5);

    //shootUpdate(enemies, 4, projectiles, screen, 0.5);

    drawPlayer(&player, screen);

    drawProjectiles(projectiles, screen);

   
    // Actualiza la pantalla
    tigrUpdate(screen);
  }

  float dt = tigrTime();
  printf("Time %f\n", dt);

  system("uname -s");

  tigrFree(screen);
  tigrFree(background);
  return 0;
}

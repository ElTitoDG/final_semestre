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


// void update(float *dt, float *remaining, Tigr *screen, float *playerx,
//             float *playery, float *playerxs, float *playerys);

// Modulos externos
void updatePlayer(TPlayer *player, Tigr *screen);
void drawPlayer(TPlayer *player, Tigr *screen);
void updateProjectiles(TProjectile projectiles[], Tigr *screen);
void drawProjectiles(TProjectile projectiles[], Tigr *screen);
void shoot(TProjectile projectiles[], TPlayer player, Tigr *screen);
void drawEnemy(TPlayer *enemy, Tigr *screen);
void updateEnemy(TPlayer *enemy, Tigr *screen, float enemy_speed);



int main(int argc, char *argv[]) {

  // Variables básicas
  float playerx = 320.0 / 2, playery = 240.0 / 2;
  float remaining, dt;
  float playerxs = 0, playerys = 0;
  Tigr *screen, *background; //*player

  // Crea ventana
  screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game 1", 0);
  background = tigrBitmap(screen->w, screen->h);

  char *text = (char *)tigrReadFile("res/info.txt", 0);
  if (!text)
    tigrError(0, "Cannot load info.txt");

  // Inicialización de las structuras con 
  // sus tipos de datos correspondientes
  TPlayer player = 
  { 
    SCREEN_WIDTH / 2.0f, 
    SCREEN_HEIGHT - PLAYER_HEIGHT - 10, 
    5.0f
  };

  TPlayer enemy = 
  {
    SCREEN_HEIGHT/2, 
    SCREEN_WIDTH/2, 
    5.0f
  };

  TProjectile projectiles[PROJECTILE_SIZE];

  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    projectiles[i].active = 0;
  }

  // Main background
  tigrClear(background, tigrRGB(80, 180, 255));

  // Green grass
  tigrFill(background, 0, player.y - 80, SCREEN_WIDTH, 2, tigrRGB(0, 0, 0));

  // White line
  // tigrLine(background, 0, 201, 320, 201, tigrRGB(255, 255, 255));


  // Bucle principal de juego
  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

    dt = tigrTime();
    
    updatePlayer(&player, screen);
    updateEnemy(&enemy, screen, 0.5);
    updateProjectiles(projectiles, screen);


    shoot(projectiles, player, screen);

    // compose the background
    tigrBlit(screen, background, 0, 0, 0, 0, background->w, background->h);

    drawPlayer(&player, screen);
    drawEnemy(&enemy, screen);
    drawProjectiles(projectiles, screen);
    tigrPrint(screen, tfont, 2, 3, tigrRGBA(0xc0, 0xd0, 0xff, 0xc0),
              text);
   
    // Update screen input
    tigrUpdate(screen);
  }

  dt = tigrTime();
  printf("Time %f\n", dt);

  system("uname -s");

  tigrFree(screen);
  tigrFree(background);
  return 0;
}
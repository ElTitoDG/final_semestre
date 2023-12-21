#include "core.h"
#include "shoot.h"
#include "tigr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Macros necesarias
#define SCREEN_WIDTH 440
#define SCREEN_HEIGHT 320
#define PLAYER_WIDTH 23
#define PLAYER_HEIGHT 22
#define PLAYER_SPEED 2.5f
#define PROJECTILE_SIZE 5
#define PROJECTILE_SPEED 5.0f
#define PI 3.1415


// Tipo de dato que define al jugador
typedef struct Tplayer 
{
  float x, y, speed;
} TPlayer;

// Función encargada de gestionar el movimiento y colisiones del personajes
void updatePlayer(TPlayer *player, Tigr *screen) 
{
  if (tigrKeyHeld(screen, 'A')) {
    player->x -= player->speed = PLAYER_SPEED;
  }
  if (tigrKeyHeld(screen, 'D')) {
    player->x += player->speed = PLAYER_SPEED;
  }
  if (tigrKeyHeld(screen, 'W')) {
    player->y -= player->speed = PLAYER_SPEED;
  }
  if (tigrKeyHeld(screen, 'S')) {
    player->y += player->speed = PLAYER_SPEED;
  }

  // Esto permite que cuando el personaje se pase del limite de la
  // pantalla reaparezca en el lado
  player->x = ((int)player->x + screen->w) % screen->w;
  player->y = ((int)player->y + screen->h) % screen->h;
}

// Función encargada de cargar la imagen del personaje
void drawPlayer(TPlayer *player, Tigr *screen) 
{

  Tigr *player_image;

  player_image = tigrLoadImage("res/player.png");
  if (!player_image) 
  {
    tigrError(0, "No se puede cargar player.png");
  }

  // Debug collision box
  if (tigrKeyHeld(screen, 'F'))
   tigrRect(screen, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT,
           tigrRGB(255, 255, 255));
  else
    tigrRect(screen, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT,
            tigrRGB(80, 180, 255));

  tigrBlitAlpha(screen, player_image, player->x, player->y, 0, (float)1.9,
                (float)PLAYER_WIDTH, (float)PLAYER_HEIGHT, 1.0f);
}

void updateEnemy(TPlayer *enemy, Tigr *screen, float enemy_speed) 
{

  enemy->speed = enemy_speed;

  srand(time(NULL));
  float enemyAngle= rand();
  if (enemy->x - 10 < 0) 
  {
    enemy->x = 10;
    enemyAngle = PI - enemyAngle;
  }
  else if (enemy->x + 10 > 430) 
  {
    enemy->x = 420;
    enemyAngle = PI - enemyAngle;
  }

  if (enemy->y < 0) 
  {
    enemy->y = 0;
    enemyAngle = 2*PI - enemyAngle;
  }
  else if (enemy->y > 310) 
  {
    enemy->y = 310;
    enemyAngle = 2*PI - enemyAngle;
  }

  enemy->x += sin(enemyAngle) * enemy->speed;
  enemy->y += cos(enemyAngle) * enemy->speed;
}



void drawEnemy(TPlayer *enemy, Tigr *screen)
{
  Tigr *enemy_image;

  enemy_image = tigrLoadImage("res/enemy.png");
  if (!enemy_image) {
    tigrError(0, "No se puede cargar enemy.png");
  } 

  // Debug collision box
  if (tigrKeyHeld(screen, 'F'))
   tigrRect(screen, enemy->x, enemy->y, PLAYER_WIDTH, PLAYER_HEIGHT,
           tigrRGB(255, 255, 255));
  else
    tigrRect(screen, enemy->x, enemy->y, PLAYER_WIDTH, PLAYER_HEIGHT,
            tigrRGB(80, 180, 255));

  tigrBlitAlpha(screen, enemy_image, enemy->x, enemy->y, 0, (float)1.9,
                (float)PLAYER_WIDTH, (float)PLAYER_HEIGHT, 1.0f);
}
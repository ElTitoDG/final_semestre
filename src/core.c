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
#define TRUE 1
#define FALSE 0


// Tipo de dato que define al jugador
typedef struct Tplayer 
{
  float x, y, speed;
  int active;
} TPlayer;

typedef struct {
  float x, y, speed;
  int active;
} TProjectile;


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
  /* if (tigrKeyHeld(screen, 'F'))
   tigrRect(screen, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT,
           tigrRGB(255, 255, 255));
  else
    tigrRect(screen, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT,
            tigrRGB(80, 180, 255)); */

  tigrBlitAlpha(screen, player_image, player->x, player->y, 0, (float)1.9,
                (float)PLAYER_WIDTH, (float)PLAYER_HEIGHT, 1.0f);
}

void updateEnemy(TPlayer *enemy, Tigr *screen, float enemy_speed) 
{

  enemy->speed = enemy_speed;

  float enemyAngle= rand();
  float randomOffset = rand() / (RAND_MAX + 1.0) * 3 * PI;
  float newAngle = enemyAngle + randomOffset;

  srand(time(NULL));
  if (enemy->x - 10 < 0) 
  {
    enemy->x = 10;
    newAngle = PI - newAngle;
  }
  else if (enemy->x + 10 > 430) 
  {
    enemy->x = 420;
    newAngle = PI - newAngle;
  }

  if (enemy->y < 0) 
  {
    enemy->y = 0;
    newAngle = 2*PI - newAngle;
  }
  else if (enemy->y > 310) 
  {
    enemy->y = 310;
    newAngle = 2*PI - newAngle;
  }

  enemy->x += sin(newAngle) * enemy->speed;
  enemy->y += cos(newAngle) * enemy->speed;
}


void drawEnemy(TPlayer *enemy, Tigr *screen)
{
  Tigr *enemy_image;

  enemy_image = tigrLoadImage("res/enemy.png");
  if (!enemy_image) {
    tigrError(0, "No se puede cargar enemy.png");
  } 

  // Debug collision box
  /* if (tigrKeyHeld(screen, 'F'))
   tigrRect(screen, enemy->x, enemy->y, PLAYER_WIDTH, PLAYER_HEIGHT,
           tigrRGB(255, 255, 255));
  else
    tigrRect(screen, enemy->x, enemy->y, PLAYER_WIDTH, PLAYER_HEIGHT,
            tigrRGB(80, 180, 255)); */

  tigrBlitAlpha(screen, enemy_image, enemy->x, enemy->y, 0, (float)1.9,
                (float)PLAYER_WIDTH, (float)PLAYER_HEIGHT, 1.0f);
}

// Update and draw multiple enemies
void updateAndDrawEnemies(TPlayer enemies[], int num_enemies, Tigr *screen, float enemy_speed) {
    for (int i = 0; i < num_enemies; ++i) {
        updateEnemy(&enemies[i], screen, enemy_speed);
        drawEnemy(&enemies[i], screen);
    }
}


void shootUpdate(TPlayer enemies[], int num_enemies, TProjectile projectiles[], Tigr *screen, float enemy_speed) 
{
    for (int i = 0; i < num_enemies; ++i) {
        // Comprobar si algún proyectil activo ha golpeado a este enemigo
        for (int j = 0; j < PROJECTILE_SIZE; ++j) {
            if (projectiles[j].active) {
                if (enemies[i].x < projectiles[j].x + PROJECTILE_SIZE &&
                    enemies[i].x + PLAYER_WIDTH > projectiles[j].x &&
                    enemies[i].y < projectiles[j].y + PROJECTILE_SIZE &&
                    enemies[i].y + PLAYER_HEIGHT > projectiles[j].y) {
                    // Si hay una colisión, desactivar el enemigo y el proyectil
                    enemies[i].active = 0;
                    projectiles[j].active = 0;
                    break;  // No necesitamos comprobar otros proyectiles una vez que el enemigo ha sido golpeado
                }
            }
        }

        // Si el enemigo sigue activo después de comprobar las colisiones, actualizar y dibujar
        if (enemies[i].active) {
            updateEnemy(&enemies[i], screen, enemy_speed);
            drawEnemy(&enemies[i], screen);
        }
    }
}
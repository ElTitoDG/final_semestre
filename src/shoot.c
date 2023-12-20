#include "tigr.h"
#include "shoot.h"

// Macros necesarias
#define SCREEN_WIDTH 440
#define SCREEN_HEIGHT 320
#define PLAYER_WIDTH 23
#define PLAYER_HEIGHT 22
#define PROJECTILE_SIZE 5

// Tipo de dato que define al proyectil
typedef struct {
  float x, y, speed;
  int active;
} TProjectile;

// Función encargada de la lógica de los proyectiles
void updateProjectiles(TProjectile projectiles[], Tigr *screen) {
  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    if (projectiles[i].active) {
      
      projectiles[i].y -= projectiles[i].speed;
      if (projectiles[i].y < 0)
        projectiles[i].active = 0;
    }
  }
}

// Función encargada que los proyectiles
void drawProjectiles(TProjectile projectiles[], Tigr *screen) {
  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    if (projectiles[i].active) {
      tigrRect(screen, projectiles[i].x, projectiles[i].y, PROJECTILE_SIZE,
               PROJECTILE_SIZE, tigrRGB(255, 0, 0));
    }
  }
}
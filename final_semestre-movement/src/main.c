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
#define PI 3.1415




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

void drawEnemy(Tigr *screen, TPlayer *enemy, int cx, int cy, int radio, TPixel color) {
  int x, y;
	for (y = -radio + 1; y < radio; y++){
		for (x = -radio + 1; x < radio; x++){
			if (x*x + y*y <= radio*radio)
				tigrPlot(screen, cx + x, cy + y, color);
    }
  }
}

int main(int argc, char *argv[]) {

  // Variables básicas
  float playerx = 320.0 / 2, playery = 240.0 / 2;
  float remaining, dt;
  float playerxs = 0, playerys = 0;
  float enemyAngle=1.0472;
  int enemySpeed = 3, enemyX = 10, enemyY = 10;
  Tigr *screen, *background; //*player

  // Crea ventana
  screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game 1", 0);
  background = tigrBitmap(screen->w, screen->h);

  // Inicialización de las structuras con 
  // sus tipos de datos correspondientes
  TPlayer player = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - PLAYER_HEIGHT - 10,
                    5.0f};
  TPlayer enemy = {enemyX , enemyY, 5.0f
  };

  TProjectile projectiles[PROJECTILE_SIZE];

  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    projectiles[i].active = 0;
  }

  // Main background
  tigrClear(background, tigrRGB(80, 180, 255));


  // Bucle principal de juego
  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

    dt = tigrTime();
    
    updatePlayer(&player, screen);
    updateProjectiles(projectiles, screen);


    shoot(projectiles, player, screen);
    
    
    //Choque enemigo con los bordes
    if (enemyX  < 0 || enemyX > 440) {
			enemyAngle = -enemyAngle;
		}

	  if (enemyY < 0) {
			enemyAngle = PI - enemyAngle;
		}

    if (enemyY > 320) {

      enemyAngle = PI - enemyAngle;

			
	  enemyAngle += ((float)(rand() - (RAND_MAX / 2)) / (float)RAND_MAX) / 20;
    }
    //Movimiento del enemigo
    enemyX += sin(enemyAngle) * enemySpeed;
    enemyY += cos(enemyAngle) * enemySpeed;
    

    // compose the background
    tigrBlit(screen, background, 0, 0, 0, 0, background->w, background->h);

    drawPlayer(&player, screen);
    drawProjectiles(projectiles, screen);
    drawEnemy(screen, &enemy, enemyX, enemyY, 10, tigrRGB(0,0,0));
    // Update screen input
    tigrUpdate(screen);
  }


  dt = tigrTime();
  printf("Time %f\n", dt);

  printf("System: %i\n", system("uname -s"));
  /* system("uname -s");
  if (system("uname -s") == "Darwin")
    printf("Mac Os "); */


  tigrFree(screen);
  return 0;
}

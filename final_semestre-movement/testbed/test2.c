
#include "../src/tigr.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PLAYER_WIDTH 23
#define PLAYER_HEIGHT 22
#define PROJECTILE_SIZE 5
#define PI 3.1415

typedef struct {
  float x, y;
  float speed;
} Player;

typedef struct {
  float x, y;
  float speed;
  int active;
} Projectile;

void updatePlayer(Player *player, Tigr *screen) {
  if (tigrKeyHeld(screen, 'A'))
    player->x -= player->speed;
  if (tigrKeyHeld(screen, 'D'))
    player->x += player->speed;
  if (tigrKeyHeld(screen, 'W'))
    player->y -= player->speed;
  if (tigrKeyHeld(screen, 'S'))
    player->y += player->speed;
}

void updateEnemy(Player *enemy, Tigr *screen)
{

  srand(time(NULL));
  float enemyAngle= 1.0472;

  // int enemySpeed = 4, enemyX = 320, enemyY = 240;

  if (enemy->x - 10 < 0 || enemy->x + 10 > 640) {
		enemyAngle = -enemyAngle;
	}

	if (enemy->y < -6) {
			enemyAngle = PI - enemyAngle;
	}

  if (enemy->y > 354) {
    enemyAngle = PI - enemyAngle;	
		enemyAngle += ((float)(rand() - (RAND_MAX / 2)) / (float)RAND_MAX) / 20;
  }

    enemy->x += sin(enemyAngle) * enemy->speed;
    enemy->y += cos(enemyAngle) * enemy->speed;
  

}



void updateProjectiles(Projectile projectiles[], Tigr *screen) {
  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    if (projectiles[i].active) {
      
      projectiles[i].y -= projectiles[i].speed;
      if (projectiles[i].y < 0)
        projectiles[i].active = 0;
    }
  }
}

void drawPlayer(Player *player, Tigr *screen) {

  tigrRect(screen, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT,
           tigrRGB(255, 0, 0));
}

void drawEnemy(Tigr *screen, Player *enemy, int cx, int cy, TPixel color) {
	int x, y;
	
  tigrRect(screen, cx, cy, PLAYER_WIDTH, PLAYER_HEIGHT,
           tigrRGB(0, 0, 0));         
	tigrPlot(screen, cx + x, cy + y, color);

  Tigr *enemy_image;

  enemy_image = tigrLoadImage("enemy.png");
  if (!enemy_image) {
    tigrError(0, "No se puede cargar enemy.png");
  }

  tigrBlitAlpha(screen, enemy_image, enemy->x - (float)PLAYER_WIDTH / 2,
                enemy->y - (float)PLAYER_HEIGHT, 0, 0, (float)PLAYER_WIDTH,
                (float)PLAYER_HEIGHT, 1.0f);

}

void drawProjectiles(Projectile projectiles[], Tigr *screen) {
  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    if (projectiles[i].active) {
      tigrRect(screen, projectiles[i].x, projectiles[i].y, PROJECTILE_SIZE,
               PROJECTILE_SIZE, tigrRGB(0, 0, 0));
    }
  }
}

int main() {
  
  srand(time(NULL));
  float enemyAngle= 1.0472;

  int enemySpeed = 4, enemyX = 320, enemyY = 240;

  
  Tigr *screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Game", 0);

  Player player = {
    SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - PLAYER_HEIGHT - 10, 5.0f
    };
  Projectile projectiles[PROJECTILE_SIZE];

  Player enemy = {
    enemyX , enemyY, 5.0f
  };



  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    projectiles[i].active = 0;
  }

  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
    tigrClear(screen, tigrRGB(213, 255, 213));

    updatePlayer(&player, screen);
    updateProjectiles(projectiles, screen);
    updateEnemy(&enemy, screen);

    if (tigrKeyHeld(screen, 'Z')) {
      for (int i = 0; i < PROJECTILE_SIZE; ++i) {
        if (!projectiles[i].active) {
          projectiles[i].x =
              player.x + PLAYER_WIDTH / 2.0f - PROJECTILE_SIZE / 2.0f;
          projectiles[i].y = player.y;
          projectiles[i].speed = 8.0f;
          projectiles[i].active = 1;
          break;
        }
      }
    }
// Void update enemy
  /* if (enemyX - 10 < 0 || enemyX + 10 > 640) {
		enemyAngle = -enemyAngle;
	}

	if (enemyY < -6) {
			enemyAngle = PI - enemyAngle;
	}

  if (enemyY > 354) {

      enemyAngle = PI - enemyAngle;

			
			enemyAngle += ((float)(rand() - (RAND_MAX / 2)) / (float)RAND_MAX) / 20;
    }

    enemyX += sin(enemyAngle) * enemySpeed;
    enemyY += cos(enemyAngle) * enemySpeed;
 */

    drawPlayer(&player, screen);
    drawProjectiles(projectiles, screen);
    drawEnemy(screen, &enemy, enemyX, enemyY, tigrRGB(0, 0, 0));

    tigrUpdate(screen);
  }

  tigrFree(screen);

  return 0;
}

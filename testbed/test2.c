
#include "../src/tigr.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PLAYER_WIDTH 23
#define PLAYER_HEIGHT 22
#define PROJECTILE_SIZE 5

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
  else if (tigrKeyHeld(screen, 'D'))
    player->x += player->speed;
  else if (tigrKeyHeld(screen, 'W'))
    player->y -= player->speed;
  else if (tigrKeyHeld(screen, 'S'))
    player->y += player->speed;
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

  Tigr *player_image;

  player_image = tigrLoadImage("player.png");
  if (!player) {
    tigrError(0, "No se puede cargar player.png");
  }

  tigrRect(screen, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT,
           tigrRGB(255, 255, 255));

  tigrBlitAlpha(screen, player_image, player->x - (float)PLAYER_WIDTH / 2,
                player->y - (float)PLAYER_HEIGHT, 0, 0, (float)PLAYER_WIDTH,
                (float)PLAYER_HEIGHT, 1.0f);
}

void drawProjectiles(Projectile projectiles[], Tigr *screen) {
  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    if (projectiles[i].active) {
      tigrRect(screen, projectiles[i].x, projectiles[i].y, PROJECTILE_SIZE,
               PROJECTILE_SIZE, tigrRGB(255, 0, 0));
    }
  }
}

int main() {
  Tigr *screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Game", 0);
  Tigr *background;

  Player player = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - PLAYER_HEIGHT - 10,
                   5.0f};
  Projectile projectiles[PROJECTILE_SIZE];

  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    projectiles[i].active = 0;
  }

  tigrClear(background, tigrRGB(80, 180, 255));

  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
    tigrClear(screen, tigrRGB(0, 0, 0));

    updatePlayer(&player, screen);
    updateProjectiles(projectiles, screen);

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

/*     tigrBlit(screen, background, 0, 0, 0, 0, background->w, background->h);
 */    

    drawPlayer(&player, screen);
    drawProjectiles(projectiles, screen);

    tigrUpdate(screen);
  }

  tigrFree(screen);

  return 0;
}
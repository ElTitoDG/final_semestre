#include "core.h"
#include "tigr.h"

#define SCREEN_WIDTH 440
#define SCREEN_HEIGHT 320
#define PLAYER_WIDTH 23
#define PLAYER_HEIGHT 22

typedef struct Tplayer {
  float x, y, speed;
} TPlayer;

typedef struct TProjectile {
  float x, y, speed;
  int active;
} TProjectile;

void updatePlayer(TPlayer *player, Tigr *screen) {
  if (tigrKeyHeld(screen, 'A')) {
    player->x -= player->speed;
  }
  if (tigrKeyHeld(screen, 'D')) {
    player->x += player->speed;
  }
  if (tigrKeyHeld(screen, 'W')) {
    player->y -= player->speed;
  }
  if (tigrKeyHeld(screen, 'S')) {
    player->y += player->speed;
  }

  player->x = ((int)player->x + screen->w) % screen->w;
  player->y = ((int)player->y + screen->h) % screen->h;
}

void drawPlayer(TPlayer *player, Tigr *screen) {

  Tigr *player_image;

  player_image = tigrLoadImage("res/player.png");
  if (!player) {
    tigrError(0, "No se puede cargar player.png");
  }

  tigrRect(screen, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT,
           tigrRGB(255, 255, 255));

  tigrBlitAlpha(screen, player_image, player->x, player->y, 0, (float)1.9,
                (float)PLAYER_WIDTH, (float)PLAYER_HEIGHT, 1.0f);
}

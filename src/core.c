#include "core.h"
#include "tigr.h"

#define PLAYER_WIDTH 23
#define PLAYER_HEIGTH 22

typedef struct {
  float x, y, speed;
} TPlayer;

typedef struct {
  float x, y, speed;
  int active;
} TProjectile;

void updatePlayer(TPlayer *player, Tigr *screen) {
  if (tigrKeyHeld(screen, 'A'))
    player->x -= player->speed;
  if (tigrKeyHeld(screen, 'D'))
    player->x += player->speed;
  if (tigrKeyHeld(screen, 'W'))
    player->y -= player->speed;
  if (tigrKeyHeld(screen, 'S'))
    player->y += player->speed;

  // Restricciones de los bordes de la ventana
  if (player->x < 8) {
    player->x = 8;
    player->speed = 0;
  }

  if (player->x > screen->w - 8) {
    player->x = screen->w - 8.0f;
    player->speed = 0;
  }

  if (player->y < 23) {
    player->y = 23;
    player->speed = 0;
  }

  if (player->y > screen->h - 1) {
    player->y = screen->h - 1.0f;
    player->speed = 0;
  }
}

void drawPlayer(TPlayer *player, Tigr *screen) {

  Tigr *player_image;

  player_image = tigrLoadImage("res/player.png");
  if (!player) {
    tigrError(0, "No se puede cargar player.png");
  }

  // tigrRect(screen, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGTH,
  //          tigrRGB(255, 255, 255));

  tigrBlitAlpha(screen, player_image, player->x - (float)PLAYER_WIDTH / 2,
                player->y - (float)PLAYER_HEIGTH, 0, 0, (float)PLAYER_WIDTH,
                (float)PLAYER_HEIGTH, 1.0f);
}

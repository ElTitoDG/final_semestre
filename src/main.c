#include "core.h"
#include "tigr.h"
#include <stdio.h>

#define SCREEN_WIDTH 440
#define SCREEN_HEIGHT 320
#define PLAYER_WIDTH 23
#define PLAYER_HEIGHT 22
#define PROJECTILE_SIZE 5

typedef struct {
  float x, y, speed;
} TPlayer;

typedef struct {
  float x, y, speed;
  int active;
} TProjectile;

// void update(float *dt, float *remaining, Tigr *screen, float *playerx,
//             float *playery, float *playerxs, float *playerys);

void updatePlayer(TPlayer *player, Tigr *screen);
void drawPlayer(TPlayer *player, Tigr *screen);
void updateProjectiles(TProjectile projectiles[], Tigr *screen);

void drawProjectiles(TProjectile projectiles[], Tigr *screen);

int main(int argc, char *argv[]) {

  // Variables básicas
  float playerx = 320.0 / 2, playery = 240.0 / 2;
  float remaining, dt;
  float playerxs = 0, playerys = 0;
  Tigr *screen, *background; //*player

  // Carga el sprite del jugador
  // player = tigrLoadImage("res/player.png");
  // if (!player) {
  //   tigrError(0, "No se puede cargar player.png");
  // }

  // Crea ventana
  screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game 1", 0);
  background = tigrBitmap(screen->w, screen->h);

  TPlayer player = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - PLAYER_HEIGHT - 10,
                    5.0f};

  TProjectile projectiles[PROJECTILE_SIZE];

  for (int i = 0; i < PROJECTILE_SIZE; ++i) {
    projectiles[i].active = 0;
  }

  // Main background
  tigrClear(background, tigrRGB(80, 180, 255));
  // Green grass
  // tigrFill(background, 0, 200, 320, 40, tigrRGB(60, 120, 60));
  // // Black border
  // tigrFill(background, 0, 200, 320, 3, tigrRGB(0, 0, 0));
  // // White line
  // tigrLine(background, 0, 201, 320, 201, tigrRGB(255, 255, 255));

  // Main Loop
  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

    dt = tigrTime();
    // update(&dt, &remaining, screen, &playerx, &playery, &playerxs,
    // &playerys);
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

    // compose the background
    tigrBlit(screen, background, 0, 0, 0, 0, background->w, background->h);

    drawPlayer(&player, screen);
    drawProjectiles(projectiles, screen);
    // compose player to background
    // tigrBlitAlpha(screen, player, (int)playerx - player->w / 2,
    //               (int)playery - player->h, 0, 0, player->w,
    //               player->h, 1.0f);
    // Update screen input
    tigrUpdate(screen);
  }

  printf("Time %f\n", dt);
  tigrFree(screen);
  return 0;
}

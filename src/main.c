#include "core.h"
#include "tigr.h"
#include <stdio.h>

void update(float *dt, float *remaining, Tigr *screen, float *playerx,
            float *playery, float *playerxs, float *playerys);

int main(int argc, char *argv[]) {

  // Variables básicas
  float playerx = 320.0 / 2, playery = 240.0 / 2;
  float remaining, dt;
  float playerxs = 0, playerys = 0;
  Tigr *screen, *background, *player;

  // Carga el sprite del jugador
  player = tigrLoadImage("res/player.png");
  if (!player) {
    tigrError(0, "No se puede cargar player.png");
  }

  // Crea ventana
  screen = tigrWindow(320, 240, "Game 1", 0);
  background = tigrBitmap(screen->w, screen->h);

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
    update(&dt, &remaining, screen, &playerx, &playery, &playerxs, &playerys);

    // compose the background
    tigrBlit(screen, background, 0, 0, 0, 0, background->w, background->h);

    // compose player to background
    tigrBlitAlpha(screen, player, (int)playerx - player->w / 2,
                  (int)playery - player->h, 0, 0, player->w, player->h, 1.0f);
    // Update screen input
    tigrUpdate(screen);
  }

  printf("Time %f\n", dt);
  tigrFree(screen);
  return 0;
}

#include "tigr.h"
#include <math.h>

int main(int argc, char *argv[]) {

  float playerx = 160, playery = 200;

  Tigr *window, *background, *player;

  // Loads player image and checks
  player = tigrLoadImage("player.png");
  if (!player)
    tigrError(0, "Cannot load player");

  window = tigrWindow(320, 240, "Game type", TIGR_2X);
  background = tigrBitmap(window->w, window->h);

  tigrClear(background, tigrRGB(80, 180, 255));
  tigrFill(background, 0, 200, 320, 40, tigrRGB(60, 120, 60));
  tigrFill(background, 0, 200, 320, 3, tigrRGB(0, 0, 0));
  tigrLine(background, 0, 201, 320, 201, tigrRGB(255, 255, 255));

  tigrSetPostFX(window, 1, 1, 1, 2.0f);

  while (!tigrClosed(window) && !tigrKeyDown(window, TK_ESCAPE)) {
    tigrBlit(window, background, 0, 0, 0, 0, background->w, background->h);
    tigrBlitAlpha(window, player, (int)playerx - player->w / 2,
                  (int)playery - player->h, 0, 0, player->w, player->h, 1.0f);
    tigrUpdate(window);
  }

  tigrFree(player);
  tigrFree(background);
  tigrFree(window);

  return 0;
}

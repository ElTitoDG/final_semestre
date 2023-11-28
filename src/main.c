#include "tigr.h"

int main(int argc, char *argv[]) {

  // Base Variable

  Tigr *screen, *background, *player;

  screen = tigrWindow(320, 240, "Game 1", 0);
  background = tigrBitmap(screen->w, screen->h);

  // Main background
  tigrClear(background, tigrRGB(80, 180, 255));
  // Green grass
  tigrFill(background, 0, 200, 320, 40, tigrRGB(60, 120, 60));
  // Black border
  tigrFill(background, 0, 200, 320, 3, tigrRGB(0, 0, 0));
  // White line
  tigrLine(background, 0, 201, 320, 201, tigrRGB(255, 255, 255));

  // Main Loop
  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
    // compose the background
    tigrBlit(screen, background, 0, 0, 0, 0, background->w, background->h);
    // Update screen input
    tigrUpdate(screen);
  }
  tigrFree(screen);
  return 0;
}

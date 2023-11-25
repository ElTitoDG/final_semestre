#include "stb_image.h"
#include "tigr.h"
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION

int main(int argc, char *argv[]) {
  Tigr *screen = tigrWindow(320, 240, "Hello", 0);

  Tigr *image = tigrLoadImage("../resources/images.jpg");

  while (!tigrClosed(screen)) {
    tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
    tigrPrint(screen, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff),
              "Hello, world.");
    tigrUpdate(screen);
  }

  tigrFree(screen);
  return 0;
}

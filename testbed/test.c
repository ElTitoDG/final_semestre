#include "../src/tigr.h"
#include <math.h>

float playerx = 160, playery = 200;
float playerxs = 0, playerys = 0;
int standing = 1;
float remaining = 0;
Tigr *backdrop, *screen;

void update(float dt) {
  if (remaining > 0)
    remaining -= dt;

  if (standing && tigrKeyDown(screen, TK_SPACE))
    playerys -= 500;
  if (tigrKeyHeld(screen, TK_LEFT) || tigrKeyHeld(screen, 'A'))
    playerxs -= 10;
  if (tigrKeyHeld(screen, TK_RIGHT) || tigrKeyHeld(screen, 'D'))
    playerxs += 10;

  float oldx = playerx, oldy = playery;

  playerxs *= exp(-10.0f * dt);
  playerys *= exp(-2.0f * dt);
  playerys += dt * 200.0f;
  playerx += dt * playerxs;
  playery += dt * playerys;

  if (playerx < 8) {
    playerx = 8;
    playerxs = 0;
  }

  if (playerx > screen->w - 8) {
    playerx = screen->w - 8.0f;
    playerxs = 0;
  }

  float dx = (playerx - oldx) / 10;
  float dy = (playery - oldy) / 10;
  standing = 0;

  for (int n = 0; n < 10; n++) {
    TPixel p = tigrGet(backdrop, (int)oldx, (int)oldy - 1);
    if (p.r == 0 && p.g == 0 && p.b == 0)
      oldy -= 1;
    p = tigrGet(backdrop, (int)oldx, (int)oldy);
    if (p.r == 0 && p.g == 0 && p.b == 0 && playerys > 0) {
      playerys = 0;
      dy = 0;
      standing = 1;
    }
    oldx += dx;
    oldy += dy;
  }

  playerx = oldx;
  playery = oldy;
}

int main(int argc, char *argv[]) {
  Tigr *squinkle = tigrLoadImage("player.png");
  if (!squinkle)
    tigrError(0, "Cannot load squinkle.png");

  char *greeting = (char *)tigrReadFile("greeting.txt", 0);
  if (!greeting)
    tigrError(0, "Cannot load greeting.txt");

  screen = tigrWindow(320, 240, greeting, TIGR_2X);
  backdrop = tigrBitmap(screen->w, screen->h);

  tigrClear(backdrop, tigrRGB(80, 180, 255));
  tigrFill(backdrop, 0, 200, 320, 40, tigrRGB(60, 120, 60));
  tigrFill(backdrop, 0, 200, 320, 3, tigrRGB(0, 0, 0));
  tigrLine(backdrop, 0, 201, 320, 201, tigrRGB(255, 255, 255));

  tigrSetPostFX(screen, 1, 1, 1, 2.0f);

  int prevx = 0, prevy = 0, prev = 0;

  int chars[16];
  for (int n = 0; n < 16; n++)
    chars[n] = '_';

  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
    float dt = tigrTime();
    update(dt);

    int x, y, b;
    tigrMouse(screen, &x, &y, &b);
    if (b & 1) {
      if (prev)
        tigrLine(backdrop, prevx, prevy, x, y, tigrRGB(0, 0, 0));
      prevx = x;
      prevy = y;
      prev = 1;
    } else {
      prev = 0;
    }

    tigrBlit(screen, backdrop, 0, 0, 0, 0, backdrop->w, backdrop->h);
    tigrBlitAlpha(screen, squinkle, (int)playerx - squinkle->w / 2,
                  (int)playery - squinkle->h, 0, 0, squinkle->w, squinkle->h,
                  1.0f);

    tigrPrint(screen, tfont, 10, 10, tigrRGBA(0xc0, 0xd0, 0xff, 0xc0),
              greeting);
    tigrPrint(screen, tfont, 10, 222, tigrRGBA(0xff, 0xff, 0xff, 0xff),
              "A D + SPACE");

    for (;;) {
      int c = tigrReadChar(screen);
      if (c == 0)
        break;
      for (int n = 1; n < 16; n++)
        chars[n - 1] = chars[n];
      chars[15] = c;
    }

    char tmp[100], *p = tmp;
    for (int n = 0; n < 16; n++)
      p = tigrEncodeUTF8(p, chars[n]);
    *p = 0;
    tigrPrint(screen, tfont, 160, 222, tigrRGB(255, 255, 255), "Chars: %s",
              tmp);

    tigrUpdate(screen);
  }

  tigrFree(squinkle);
  tigrFree(backdrop);
  tigrFree(screen);
  return 0;
}

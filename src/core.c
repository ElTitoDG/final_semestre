#include "core.h"
#include "tigr.h"
#include <math.h>

void update(float *dt, float *remaining, Tigr *screen, float *playerx,
            float *playery, float *playerxs, float *playerys) {

  if (*remaining > 0)
    *remaining -= *dt;

  if (tigrKeyHeld(screen, TK_UP) && tigrKeyDown(screen, 'W'))
    playerys -= 10;

  if (tigrKeyHeld(screen, TK_LEFT) || tigrKeyHeld(screen, 'A'))
    *playerxs -= 10;

  if (tigrKeyHeld(screen, TK_LEFT) || tigrKeyHeld(screen, 'D'))
    *playerxs += 10;

  float oldx = *playerx, oldy = *playery;

  *playerxs *= exp(-5.0f * *dt);
  *playerys *= exp(-5.0f * *dt);
  *playerx += *dt * *playerxs;
  *playery += *dt * *playerys;

  if (*playerx < 8) {
    *playerx = 8;
    *playerxs = 0;
  }

  if (*playerx > screen->w - 8) {
    *playerx = screen->w - 8.0f;
    *playerxs = 0;
  }

  float dx = (*playerx - oldx) / 10;
  float dy = (*playery - oldy) / 10;
}

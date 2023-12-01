#include "core.h"
#include "tigr.h"
#include <math.h>

void update(float *dt, float *remaining, Tigr *screen, float *playerx,
            float *playery, float *playerxs, float *playerys) {

  if (*remaining > 0)
    *remaining -= *dt;

  // Movimiento Vertical
  if (tigrKeyHeld(screen, TK_UP) || tigrKeyHeld(screen, 'W'))
    *playerys -= 10;
  if (tigrKeyHeld(screen, TK_DOWN) || tigrKeyHeld(screen, 'S'))
    *playerys += 10;

  // Movimiento Lateral
  if (tigrKeyHeld(screen, TK_LEFT) || tigrKeyHeld(screen, 'A'))
    *playerxs -= 10;
  if (tigrKeyHeld(screen, TK_LEFT) || tigrKeyHeld(screen, 'D'))
    *playerxs += 10;

  float oldx = *playerx, oldy = *playery;
  *playerx += *dt * *playerxs;
  *playery += *dt * *playerys;

  *playerxs *= exp(-10.0f * *dt);
  *playerys *= exp(-10.0f * *dt);
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

  if (*playery < 8) {
    *playery = 8;
    *playerys = 0;
  }

  if (*playery > screen->h - 8) {
    *playery = screen->h - 8.0f;
    *playerys = 0;
  }
}

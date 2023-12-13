#include "tigr.h"
#ifdef __CORE_H__
#define __CORE_H__

// void update(float *dt, float *remaining, Tigr *screen, float *playerx,
//             float *playery, float *playerxs, float *playerys);

void updatePlayer(TPlayer *player, Tigr *screen);

void drawPlayer(TPlayer *player, Tigr *screen);
#endif // DEBUG

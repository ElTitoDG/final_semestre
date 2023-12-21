#ifdef CORE_H
#define CORE_H

typedef struct Tplayer {
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
void drawEnemy(Tigr *screen, TPlayer *enemy, int cx, int cy, int radio, TPixel color);
#endif // CORE_H

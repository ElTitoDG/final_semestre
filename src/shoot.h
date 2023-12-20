#ifdef SHOOT_H
#define SHOOT_H

typedef struct {
  float x, y, speed;
} TPlayer;

typedef struct {
  float x, y, speed;
  int active;
} TProjectile;

void updateProjectiles(TProjectile projectiles[], Tigr *screen);

void drawProjectiles(TProjectile projectiles[], Tigr *screen);

void shoot(TProjectile projectiles[], TPlayer player, Tigr *screen);

#endif // SHOOT_H
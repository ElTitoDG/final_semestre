#ifdef CORE_H
#define CORE_H

typedef struct Tplayer {
  float x, y, speed;
} TPlayer;

typedef struct {
  float x, y, speed;
  int active;
} TProjectile;


void updatePlayer(TPlayer *player, Tigr *screen);
void drawPlayer(TPlayer *player, Tigr *screen);
void drawEnemy(TPlayer *enemy, Tigr *screen);
void updateEnemy(TPlayer *enemy, Tigr *screen, float enemy_speed);
//void shootUpdate(TPlayer enemies[], int num_enemies, TProjectile projectiles[], Tigr *screen, float enemy_speed);

#endif // CORE_H
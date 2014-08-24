#pragma once
#include <estk.h>

void dude_init(void);
void dude_clear(void);
void dude_frame(float fr);
void dude_render(void);
void dude_setAim(float aimX, float aimY);
void dude_setFire(char on);
int dude_touching(esVec2f thing, float rad);
void dude_hurt(int hp);
void dude_readPos(float *x, float *y);


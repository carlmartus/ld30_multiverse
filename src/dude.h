#pragma once
#include <estk.h>

void dudeInit(void);
void dudeClear(void);
void dudeFrame(float fr);
void dudeRender(void);
void dudeSetAim(float aimX, float aimY);
void dudeSetFire(char on);
int dudeTouching(esVec2f thing, float rad);
void dudeHurt(int hp);
void dudeReadPos(float *x, float *y);


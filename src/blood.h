#pragma once

typedef enum {
	HIT_SMALL,
} HitType;

void bloodReset(void);
void bloodProced(float fr);
void bloodHit(HitType type, float x, float y);


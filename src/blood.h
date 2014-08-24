#pragma once

typedef enum {
	HIT_SMALL,
} HitType;

void blood_reset(void);
void blood_proced(float fr);
void blood_hit(HitType type, float x, float y);


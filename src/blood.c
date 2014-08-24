#include "blood.h"
#include "common.h"
#include <estk.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BLEED 20

#define FLAG_ON 1

typedef struct {
	int flags;
	esVec2f loc;
	float life, ttl, speed;
} Bleed;

static struct {
	float ttl, speed;
} const lifes[] = {
	[HIT_SMALL] = { 0.3f, 12.0f },
};

static Bleed bleeds[MAX_BLEED];
static int bleedId;

void bloodReset(void) {
	bleedId = 0;
	memset(bleeds, sizeof(bleeds), 0);
}

void bloodProced(float fr) {
	Bleed *itr, *end;
	itr = bleeds;
	end = itr + MAX_BLEED;

	while (itr < end) {
		if (itr->flags & FLAG_ON) {
			itr->life += fr;
			if (itr->life > itr->ttl) {
				itr->flags = 0;
			} else {
				Block splat = animate(BLOCK_SPLAT1, 4, itr->speed, itr->life);
				drawSprite(itr->loc.x, itr->loc.y, BLOOD_SCALE, 0.0f, splat, 0);
			}
		}
		itr++;
	}
}

static Bleed *getBleed(void) {
	Bleed *ret = bleeds + bleedId++;
	if (bleedId >= MAX_BLEED) bleedId = 0;
	return ret;
}

void bloodHit(HitType type, float x, float y) {
	Bleed *bl = getBleed();
	bl->flags = FLAG_ON;
	bl->ttl = lifes[type].ttl;
	bl->speed = lifes[type].speed;
	bl->life = 0.0f;

	int rx = (rand() & 7) - 3;
	int ry = (rand() & 7) - 3;

	bl->loc.x = x + 0.1f * (float) rx;
	bl->loc.y = y + 0.1f * (float) ry;
}


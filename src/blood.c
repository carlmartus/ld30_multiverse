#include "blood.h"
#include <estk.h>
#include <string.h>

#define MAX_BLEED 20

#define FLAG_ON 1

typedef struct {
	int flags;
	esVec2f loc;
	float ttl, speed;
} Bleed;

static struct {
	float ttl, speed;
} const lifes[] = {
	[HIT_SMALL] = { 0.3f, 3.0f },
};

static Bleed bleeds[MAX_BLEED];
static int bleedId;

void blood_reset(void) {
	bleedId = 0;
	memset(bleeds, sizeof(bleeds), 0);
}

void blood_proced(float fr) {
}

static Bleed *getBleed(void) {
	return bleeds + bleedId++;
}

void blood_hit(HitType type, float x, float y) {
	Bleed *bl = getBleed();
	bl->ttl = lifes[type].ttl;
	bl->speed = lifes[type].speed;
	bl->loc.x = x;
	bl->loc.y = y;
}


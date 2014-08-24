#pragma once
#include <estk.h>

#define SCALE_WORLD 0.5f
#define SCALE_DUDE 0.5f
#define SCALE_CROSSHAIR 0.4f
#define SCREEN_RADIUS 11.0f
#define SCREEN_REZ 600

#define GEN_BUSHES 200
#define SHAKE 6.0f
#define SHAKE_UP 0.04f

#define FIRE_SPEED 15.0f
#define FIRE_SCALE 1.5f

#define AIM_MAX (SCREEN_RADIUS*0.6f)

typedef enum {
	BLOCK_HEAD,
	BLOCK_BODY,
	BLOCK_FEET,
	BLOCK_GUN,
	BLOCK_CROSSHAIR1,
	BLOCK_CROSSHAIR2,
	BLOCK_FIRE1,
	BLOCK_FIRE2,

	BLOCK_GRASS,
	BLOCK_ROAD_H,
	BLOCK_ROAD_V,
	BLOCK_ROAD_X,
	BLOCK_BUSH,

	BLOCK_BAT1,
	BLOCK_BAT2,
	BLOCK_BAT_DEAD,
} Block;

typedef struct {
	int spriteX, spriteY;
} BlockSprite;

static const BlockSprite blockSprites[] = {
	[BLOCK_HEAD] = { 0, 0 },
	[BLOCK_BODY] = { 1, 0 },
	[BLOCK_FEET] = { 2, 0 },
	[BLOCK_GUN] = { 3, 0 },
	[BLOCK_CROSSHAIR1] = { 4, 0 },
	[BLOCK_CROSSHAIR2] = { 5, 0 },
	[BLOCK_FIRE1] = { 6, 0 },
	[BLOCK_FIRE2] = { 7, 0 },

	[BLOCK_GRASS] = { 0, 1 },
	[BLOCK_ROAD_H] = { 1, 1 },
	[BLOCK_ROAD_V] = { 2, 1 },
	[BLOCK_ROAD_X] = { 3, 1 },
	[BLOCK_BUSH] = { 4, 1 },

	[BLOCK_BAT1] = { 0, 4 },
	[BLOCK_BAT2] = { 1, 4 },
	[BLOCK_BAT_DEAD] = { 2, 4 },
};

void drawSprite(float x, float y, float scale,
		float rotation, Block block, int flags);
esVec2f normalize(esVec2f v);
esVec2f towards(esVec2f a, esVec2f b, float speed, float *distance);


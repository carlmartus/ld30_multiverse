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
#define FIRE_DELAY 0.2f
#define FIRE_DAMAGE 20

#define AIM_MAX (SCREEN_RADIUS*0.6f)

#define BLOOD_SCALE 0.5f

typedef enum {
	BLOCK_HEAD,
	BLOCK_BODY,
	BLOCK_FEET,
	BLOCK_GUN,
	BLOCK_CROSSHAIR1,
	BLOCK_CROSSHAIR2,
	BLOCK_FIRE1,
	BLOCK_FIRE2,
	BLOCK_DEAD,

	BLOCK_SPLAT1,
	BLOCK_SPLAT2,
	BLOCK_SPLAT3,
	BLOCK_SPLAT4,

	BLOCK_DIMENSION1,
	BLOCK_DIMENSION2,
	BLOCK_DIMENSION3,
	BLOCK_DIMENSION4,

	BLOCK_GRASS,
	BLOCK_ROAD_H,
	BLOCK_ROAD_V,
	BLOCK_ROAD_X,
	BLOCK_BUSH,
	BLOCK_FLOWERS,

	BLOCK_BAT1,
	BLOCK_BAT2,
	BLOCK_BAT_ATTACK,
	BLOCK_BAT_DEAD,

	BLOCK_NUM1,
	BLOCK_NUM2,
	BLOCK_NUM3,
	BLOCK_NUM4,
	BLOCK_NUM5,
	BLOCK_NUM6,
	BLOCK_NUM7,
	BLOCK_NUM8,
} Block;

typedef struct {
	int spriteX, spriteY;
} BlockSprite;

static const BlockSprite blockSprites[] = {
	[BLOCK_HEAD] =			{ 0, 0 },
	[BLOCK_BODY] =			{ 1, 0 },
	[BLOCK_FEET] =			{ 2, 0 },
	[BLOCK_GUN] =			{ 3, 0 },
	[BLOCK_DEAD] =			{ 0, 1 },
	[BLOCK_CROSSHAIR1] =	{ 4, 0 },
	[BLOCK_CROSSHAIR2] =	{ 5, 0 },
	[BLOCK_FIRE1] =			{ 6, 0 },
	[BLOCK_FIRE2] =			{ 7, 0 },

	[BLOCK_SPLAT1] =		{ 1, 1 },
	[BLOCK_SPLAT2] =		{ 2, 1 },
	[BLOCK_SPLAT3] =		{ 3, 1 },
	[BLOCK_SPLAT4] =		{ 4, 1 },

	[BLOCK_DIMENSION1] =	{ 0, 3 },
	[BLOCK_DIMENSION2] =	{ 1, 3 },
	[BLOCK_DIMENSION3] =	{ 2, 3 },
	[BLOCK_DIMENSION4] =	{ 3, 3 },

	[BLOCK_GRASS] =			{ 0, 2 },
	[BLOCK_ROAD_H] =		{ 1, 2 },
	[BLOCK_ROAD_V] =		{ 2, 2 },
	[BLOCK_ROAD_X] =		{ 3, 2 },
	[BLOCK_BUSH] =			{ 4, 2 },
	[BLOCK_FLOWERS] =		{ 5, 2 },

	[BLOCK_BAT1] =			{ 0, 4 },
	[BLOCK_BAT2] =			{ 1, 4 },
	[BLOCK_BAT_ATTACK] =	{ 2, 4 },
	[BLOCK_BAT_DEAD] =		{ 3, 4 },

	[BLOCK_NUM1] =			{ 0, 5 },
	[BLOCK_NUM2] =			{ 1, 5 },
	[BLOCK_NUM3] =			{ 2, 5 },
	[BLOCK_NUM4] =			{ 3, 5 },
	[BLOCK_NUM5] =			{ 4, 5 },
	[BLOCK_NUM6] =			{ 5, 5 },
	[BLOCK_NUM7] =			{ 6, 5 },
	[BLOCK_NUM8] =			{ 7, 5 },
};

void drawSprite(float x, float y, float scale,
		float rotation, Block block, int flags);
esVec2f normalize(esVec2f v);
esVec2f towards(esVec2f a, esVec2f b, float speed, float *distance);
int animate(int baseFrame, int frameCount, int speed, float elapse);


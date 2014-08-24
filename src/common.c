#include "common.h"
#include <math.h>

void drawSprite(float x, float y, float scale,
		float rotation, Block block, int flags) {
	BlockSprite bs = blockSprites[block];
	esSprites2d_put(x, y, scale, rotation, bs.spriteX, bs.spriteY, flags);
}

esVec2f normalize(esVec2f v) {
	float r = sqrtf(v.x*v.x + v.y*v.y);
	if (r > 0.0f) {
		float inv = 1.0f / r;
		v.x *= inv;
		v.y *= inv;
	}
	return v;
}

esVec2f towards(esVec2f a, esVec2f b, float speed, float *distance) {
	esVec2f dir = {
		b.x - a.x,
		b.y - a.y,
	};

	float r = sqrtf(dir.x*dir.x + dir.y*dir.y);

	if (distance != NULL) *distance = r;

	if (r < speed) {
		return b;
	} else {
		float inv = 1.0f / r;
		dir.x *= inv;
		dir.y *= inv;

		esVec2f mid = {
			a.x + dir.x*speed,
			a.y + dir.y*speed,
		};
		return mid;
	}
}

int animate(int baseFrame, int frameCount, int speed, float elapse) {
	return baseFrame + (int) (elapse*speed) % frameCount;
}


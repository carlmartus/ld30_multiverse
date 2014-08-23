#include "common.h"
#include <estk.h>

void drawSprite(float x, float y, float scale,
		float rotation, Block block, int flags) {
	BlockSprite bs = blockSprites[block];
	esSprites2d_put(x, y, scale, rotation, bs.spriteX, bs.spriteY, flags);
}


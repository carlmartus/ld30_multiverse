#include "map.h"
#include <estk.h>
#include "common.h"

#define RAD_BS 7
#define RAD (1<<RAD_BS)
#define RAD_BM (RAD-1)

typedef struct {
	Block type;
} MapBlock;

static MapBlock map[RAD*RAD];

static void fillGrass(void) {
	MapBlock *itr = map;

	int x, y;
	for (y=0; y<RAD; y++) {
		for (x=0; x<RAD; x++) {
			itr->type = BLOCK_GRASS;
			itr++;
		}
	}
}

static void spreadBushes(void) {
	int i;
	for (i=0; i<GEN_BUSHES; i++) {
		int x = rand() & RAD_BM;
		int y = rand() & RAD_BM;
		map[x+y*RAD].type = BLOCK_BUSH;
	}
}

static void makeRoad(void) {
	int x, y;
	int roadX = 0;
	int roadY = 0;
	for (x=0; x<RAD; x++) map[x+roadY*RAD].type = BLOCK_ROAD_H;
	for (y=0; y<RAD; y++) map[roadX+y*RAD].type = BLOCK_ROAD_V;
	map[roadX+roadY*RAD].type = BLOCK_ROAD_X;
}

void mapGenerate(int seed) {
	srand(seed);
	fillGrass();
	spreadBushes();
	makeRoad();
}

void mapRender(float centerX, float centerY, int blocks) {
	int x, y;

	int topx = (int) centerX - (blocks >> 1);
	int topy = (int) centerY - (blocks >> 1);

	for (y=0; y<blocks; y++) {
		for (x=0; x<blocks; x++) {
			int bx = (topx + x) & RAD_BM;
			int by = (topy + y) & RAD_BM;
			BlockSprite bs = blockSprites[map[bx + by*RAD].type];

			float fx = (float) (topx + x) + 0.5f;
			float fy = (float) (topy + y) + 0.5f;

			//esLog(ES_INFO, "F %f %f", fx, fy);
			esSprites2d_put(fx, fy, SCALE_WORLD, 0.0f,
					bs.spriteX, bs.spriteY, 0.0f);
		}
	}
}

void mapClear(void) {
}


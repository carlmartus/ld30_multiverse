#include "state.h"
#include <stdio.h>
#include "common.h"
#include "map.h"
#include "dude.h"
#include "robo.h"
#include "blood.h"
#include "sound.h"

#define DEAD_WAIT 2.0f
#define VICTORY_WAIT 2.0f

static float lastFr;
static int level = 1, webLevel=1;
static float deadCounter, victoryCounter;

// Web {{{

static void webOutputLevel(void) {
	fprintf(stderr, "[CLEAR]\n");

	if (dudeIsAlive()) {
		if (level <= 8) {
			fprintf(stderr, "<p>Level: %d / 8</p>\n", webLevel);
			fprintf(stderr, "<p>Health: %d %%</p>\n", dudeGetHp());
		}
	} else {
		fprintf(stderr, "<p>You died, respawning...</p>\n");
	}
}

static void webOutputFinish(void) {
	fprintf(stderr, "[CLEAR]\n");
	fprintf(stderr, "<p><b>You finished the game!</b></p>\n");
	fprintf(stderr, "<p>Now go give this game a 5 star rating</p>\n");
}

// }}}
// State {{{
static void shiftDimension(void) {
	bloodReset();
	mapGenerate(level);
	roboGenerate(level, level);

	soundPlay(SOUND_RELOAD);

	float dudeX, dudeY;
	dudeReadPos(&dudeX, &dudeY);
	bloodHit(HIT_DIMENSION, dudeX, dudeY);
	deadCounter = 0.0f;
	victoryCounter = 0.0f;

	webLevel = level;

	stateOutput();
	webOutputLevel();
	level++;
}

void stateInit(void) {
	lastFr = 0.0f;

	dudeInit();
	soundInit();

	shiftDimension();
}

void stateFrame(float fr) {
	dudeFrame(fr);
	roboFrame(fr);

	lastFr = fr;

	if (roboIsAllDead() && level <= 8) {
		victoryCounter += fr;
		if (victoryCounter > VICTORY_WAIT) {
			shiftDimension();
		}

		if (level == 8) {
			webOutputFinish();
			level++;
			webLevel = level;
		}
	} else if (!dudeIsAlive()) {
		deadCounter += fr;
		if (deadCounter > DEAD_WAIT) {
			level = 1;
			dudeRespawn();
			shiftDimension();
		}
	}
}

void stateRender(void) {
	float dudeX, dudeY;
	dudeReadPos(&dudeX, &dudeY);

	mapRender(dudeX, dudeY, SCREEN_RADIUS*2.2f);

	roboRender();
	dudeRender();
	bloodProced(lastFr);

	if (level > 0 && level <= 8) {
		Block plate = BLOCK_NUM1 + level - 2;
		drawSprite(
				dudeX + SCREEN_RADIUS - 2.0f,
				dudeY + SCREEN_RADIUS - 2.0f,
				1.0f, 0.0f, plate, 0);
	}
}

void stateClear(void) {
	mapClear();
	esSprites2d_clear();
}

void stateOutput(void) {
	if (webLevel <= 8) {
		webOutputLevel();
	} else {
		webOutputFinish();
	}
}

// }}}


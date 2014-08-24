#include "robo.h"
#include "common.h"
#include "dude.h"
#include "blood.h"
#include "sound.h"
#include <estk.h>
#include <math.h>
#include <stdlib.h>

#define MAX_MONSTERS 200

typedef enum {
	MONSTER_BAT,
} MonsterType;

#define FLAG_ALIVE 1

// Bat head {{{

enum { BAT_FLY, BAT_CHARGE, BAT_ATTACK, BAT_BACK };

typedef struct {
	esVec2f charge;
} StateBat;

// }}}

static struct {
	int hp;
	float size;
	int state;
} const monsterStats[] = {
	[MONSTER_BAT] = { 30, 0.5f, BAT_FLY },
};

typedef struct {
	esVec2f loc;
	float counter;
	int type, flags, state;
	int hp;
	int armor;

	union {
		StateBat bat;
	};
} Monster;

static Monster monsters[MAX_MONSTERS];
static int monsterCount;
static float elapse = 0.0f;
static esVec2f dudeLoc;

static Monster *spawn(int monsterType, int level) {

	Monster *mon = monsters + monsterCount++;
	mon->flags = FLAG_ALIVE;
	mon->type = monsterType;
	mon->hp = monsterStats[monsterType].hp;
	mon->state = monsterStats[monsterType].state;
	mon->armor = 0;

	float dudeX, dudeY;
	dudeReadPos(&dudeX, &dudeY);

	float v = (float) (rand() & 127) * 0.1f;
	float amp = 8.0f + level;
	mon->loc.x = dudeX + cosf(v)*amp;
	mon->loc.y = dudeY + sinf(v)*amp;
	return mon;
}

// Bat {{{

static void batSpawn(int level) {
	spawn(MONSTER_BAT, level)->armor = 2;
}

static void batFrame(Monster *bat, float fr) {

	if ((bat->flags & FLAG_ALIVE) == 0) {
		return;
	}

	float dist;
	esVec2f v0;

	switch (bat->state) {
		default :
		case BAT_FLY :
			bat->loc = towards(bat->loc, dudeLoc, 2.0f*fr, &dist);

			if (dist > 0.1f && dist < 5.0f) {
				bat->state = BAT_CHARGE;
				bat->counter = 0.5f;
				soundPlay(SOUND_FLAP);
			}
			break;

		case BAT_CHARGE :
			if (bat->counter < 0.0f) {
				v0.x = dudeLoc.x - bat->loc.x;
				v0.y = dudeLoc.y - bat->loc.y;
				bat->bat.charge = normalize(v0);
				bat->state = BAT_ATTACK;
				bat->counter = 0.8f;
				bat->armor = 0;
				soundPlay(SOUND_BAT1);
			}
			break;

		case BAT_ATTACK :
		case BAT_BACK :

			bat->loc.x += bat->bat.charge.x*8.5f*fr;
			bat->loc.y += bat->bat.charge.y*8.5f*fr;

			if (bat->state == BAT_ATTACK) {
				if (dudeTouching(bat->loc, 0.6f)) {
					dudeHurt(20);

					bat->bat.charge.x = -bat->bat.charge.x*0.5f;
					bat->bat.charge.y = -bat->bat.charge.y*0.5f;
					bat->state = BAT_BACK;
					bat->armor = 2;
					bat->counter = 0.4f;
				}
			}

			if (bat->counter < 0.0f) {
				bat->state = BAT_FLY;
				bat->armor = 2;
			}
			break;
	}
}

static void batRender(const Monster *bat) {
	if (bat->flags & FLAG_ALIVE) {
		if (bat->state == BAT_ATTACK) {
			drawSprite(bat->loc.x, bat->loc.y, 0.3f, 0.0f, BLOCK_BAT_ATTACK, 0);
		} else {
			float flapSpeed;
			switch (bat->state) {
				default :
				case BAT_FLY : flapSpeed = 5.0f; break;
				case BAT_CHARGE : flapSpeed = 1.0f; break;
				case BAT_ATTACK : flapSpeed = 25.0f; break;
			}
			drawSprite(bat->loc.x, bat->loc.y, 0.3f, 0.0f,
					animate(BLOCK_BAT1, 2, flapSpeed, elapse), 0);
		}
	} else {
		drawSprite(bat->loc.x, bat->loc.y, 0.4f, 0.0f, BLOCK_BAT_DEAD, 0);
	}
}

// }}}

// Classes
// =======

static struct {
	void (*spawn) (int level);
	void (*frame) (Monster*, float fr);
	void (*render) (const Monster*);
} monstersVt[] = {
	[MONSTER_BAT] = { batSpawn, batFrame, batRender },
};

void roboGenerate(int seed, int iteration) {
	monsterCount = 0;

	int i;
	for (i=0; i<iteration; i++) {
		batSpawn(iteration);
	}
}

void roboFrame(float fr) {
	dudeReadPos(&dudeLoc.x, &dudeLoc.y);

	Monster *itr, *end;
	itr = monsters;
	end = itr + monsterCount;

	while (itr < end) {

		if (itr->counter >= 0.0f) {
			itr->counter -= fr;
		}
		monstersVt[itr->type].frame(itr, fr);
		itr++;
	}

	elapse += fr;
}

void roboRender() {
	const Monster *itr, *end;
	itr = monsters;
	end = itr + monsterCount;

	while (itr < end) {
		monstersVt[itr->type].render(itr);
		itr++;
	}
}

static inline int isHit(Monster *mon, float x, float y) {
	float size = monsterStats[mon->type].size;

	return fabsf(x - mon->loc.x) < size && fabsf(y - mon->loc.y) < size;
}

void roboHit(float x, float y, int damage) {
	Monster *itr, *end;
	itr = monsters;
	end = itr + monsterCount;

	//esLog(ES_INFO, "HIT %f %f", x, y);

	while (itr < end) {
		if (isHit(itr, x, y)) {
			bloodHit(HIT_SMALL, x, y);
			itr->hp -= damage >> itr->armor;
			if (itr->hp <= 0) {
				itr->flags &= ~FLAG_ALIVE;
			}
		}
		itr++;
	}
}

int roboIsAllDead(void) {
	const Monster *itr, *end;
	itr = monsters;
	end = itr + monsterCount;

	while (itr < end) {
		if (itr->flags & FLAG_ALIVE) return 0;
		itr++;
	}
	return 1;
}


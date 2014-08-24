#include "robo.h"
#include "common.h"
#include "dude.h"
#include <estk.h>

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
	int hp, state;
} const monsterStats[] = {
	[MONSTER_BAT] = { 30, BAT_FLY },
};

typedef struct {
	esVec2f loc;
	float counter;
	int type, flags, state;
	int hp;

	union {
		StateBat bat;
	};
} Monster;

static Monster monsters[MAX_MONSTERS];
static int monsterCount;
static float elapse = 0.0f;
static esVec2f dudeLoc;

static Monster *spawn(int monsterType) {

	Monster *mon = monsters + monsterCount++;
	mon->loc.x = mon->loc.y = 10.0f;
	mon->flags = FLAG_ALIVE;
	mon->type = monsterType;
	mon->hp = monsterStats[monsterType].hp;
	mon->state = monsterStats[monsterType].state;
	return mon;
}

static inline int animate(int baseFrame, int frameCount, int speed) {
	return baseFrame + (int) (elapse*speed) % frameCount;
}

// Bat {{{

static void batSpawn(void) {
	spawn(MONSTER_BAT);
}

static void batFrame(Monster *bat, float fr) {
	float dist;
	esVec2f v0;

	switch (bat->state) {
		default :
		case BAT_FLY :
			bat->loc = towards(bat->loc, dudeLoc, 2.0f*fr, &dist);

			if (dist > 0.1f && dist < 5.0f) {
				bat->state = BAT_CHARGE;
				bat->counter = 0.5f;
			}
			break;

		case BAT_CHARGE :
			if (bat->counter < 0.0f) {
				v0.x = dudeLoc.x - bat->loc.x;
				v0.y = dudeLoc.y - bat->loc.y;
				bat->bat.charge = normalize(v0);
				bat->state = BAT_ATTACK;
				bat->counter = 0.8f;
			}
			break;

		case BAT_ATTACK :
		case BAT_BACK :

			bat->loc.x += bat->bat.charge.x*9.0f*fr;
			bat->loc.y += bat->bat.charge.y*9.0f*fr;

			if (bat->state == BAT_ATTACK) {
				if (dude_touching(bat->loc, 0.6f)) {
					dude_hurt(20);

					bat->bat.charge.x = -bat->bat.charge.x*0.5f;
					bat->bat.charge.y = -bat->bat.charge.y*0.5f;
					bat->state = BAT_BACK;
					bat->counter = 0.4f;
				}
			}

			if (bat->counter < 0.0f) {
				bat->state = BAT_FLY;
			}
			break;
	}
}

static void batRender(const Monster *bat) {
	if (bat->flags & FLAG_ALIVE) {
		float flapSpeed;
		switch (bat->state) {
			default :
			case BAT_FLY : flapSpeed = 5.0f; break;
			case BAT_CHARGE : flapSpeed = 1.0f; break;
			case BAT_ATTACK : flapSpeed = 25.0f; break;
		}
		drawSprite(bat->loc.x, bat->loc.y, 0.3f, 0.0f,
				animate(BLOCK_BAT1, 2, flapSpeed), 0);
	} else {
		drawSprite(bat->loc.x, bat->loc.y, 0.3f, 0.0f, BLOCK_BAT_DEAD, 0);
	}
}

// }}}

// Classes
// =======

static struct {
	void (*spawn) (void);
	void (*frame) (Monster*, float fr);
	void (*render) (const Monster*);
} monstersVt[] = {
	[MONSTER_BAT] = { batSpawn, batFrame, batRender },
};

void robo_generate(int seed, int iteration) {
	monsterCount = 0;
	batSpawn();
}

void robo_frame(float fr) {
	dude_readPos(&dudeLoc.x, &dudeLoc.y);

	Monster *itr, *end;
	itr = monsters;
	end = itr + monsterCount;

	while (itr < end) {

		if (itr->counter > 0.0f) {
			itr->counter -= fr;
		}
		monstersVt[itr->type].frame(itr, fr);
		itr++;
	}

	elapse += fr;
}

void robo_render() {
	const Monster *itr, *end;
	itr = monsters;
	end = itr + monsterCount;

	while (itr < end) {
		monstersVt[itr->type].render(itr);
		itr++;
	}
}


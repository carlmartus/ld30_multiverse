#include "dude.h"
#include <estk.h>
#include <SDL/SDL.h>
#include <math.h>
#include "common.h"

static float locX, locY;
static float aimX, aimY, lookX, lookY;
static char move_w, move_s, move_a, move_d;

static void event_w(int sdlkey, int down) { move_w = down; }
static void event_s(int sdlkey, int down) { move_s = down; }
static void event_a(int sdlkey, int down) { move_a = down; }
static void event_d(int sdlkey, int down) { move_d = down; }

void dude_init(void) {
	locX = 0.0f;
	locY = 0.0f;

	lookX = aimX = 0.0f;
	lookY = aimY = 0.0f;

	move_w = move_s = move_a = move_d = 0;

	esGame_registerKey(SDLK_UP,		event_w);
	esGame_registerKey(SDLK_DOWN,	event_s);
	esGame_registerKey(SDLK_LEFT,	event_a);
	esGame_registerKey(SDLK_RIGHT,	event_d);
}

void dude_clear(void) {
}

static void drawCanon(void) {
	float angle = atan2f(aimY, aimX);
	drawSprite(locX, locY, SCALE_DUDE, angle, BLOCK_GUN, 0);
}

static void drawBody(void) {
	drawSprite(locX, locY, SCALE_DUDE, 0.0f, BLOCK_HEAD, 0);
	drawSprite(locX, locY, SCALE_DUDE, 0.0f, BLOCK_BODY, 0);
	drawSprite(locX, locY, SCALE_DUDE, 0.0f, BLOCK_FEET, 0);
}

void dude_frame(float fr) {
	float moveX=0.0f, moveY=0.0f;
	if (move_a) moveX -= 1.0f;
	if (move_d) moveX += 1.0f;
	if (move_w) moveY += 1.0f;
	if (move_s) moveY -= 1.0f;

	locX += moveX*fr*3.0f;
	locY += moveY*fr*3.0f;
}

void dude_render(void) {
	drawSprite(locX+aimX, locY+aimY,	SCALE_CROSSHAIR, 0.0f, BLOCK_CROSSHAIR1, 0);
	drawSprite(locX+lookX, locY+lookY,	SCALE_CROSSHAIR, 0.0f, BLOCK_CROSSHAIR2, 0);

	if (aimY > 0.0f) {
		drawCanon();
		drawBody();
	} else {
		drawBody();
		drawCanon();
	}
}

void dude_setAim(float sAimX, float sAimY) {

	lookX = sAimX;
	lookY = sAimY;

	float r = sqrt(sAimX*sAimX + sAimY*sAimY);
	if (r > AIM_MAX) {
		float inv = 1.0f / r;
		aimX = AIM_MAX * sAimX * inv;
		aimY = AIM_MAX * sAimY * inv;
	} else {
		aimX = lookX;
		aimY = lookY;
	}
}

void dude_readPos(float *x, float *y) {
	*x = locX;
	*y = locY;
}


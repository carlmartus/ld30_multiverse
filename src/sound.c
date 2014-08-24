#include "sound.h"
#include <estk.h>

static esSound sounds[SOUND_COUNT];

void soundInit(void) {
	esSound_create(sounds + SOUND_SHOT, "media/shotx.wav");
	esSound_create(sounds + SOUND_RELOAD, "media/reload.wav");
	esSound_create(sounds + SOUND_FLAP, "media/flap.wav");
	esSound_create(sounds + SOUND_BAT1, "media/bat1.wav");

	esSound_create(sounds + SOUND_DUDEHURT1, "media/dude_hurt1.wav");
	esSound_create(sounds + SOUND_DUDEHURT2, "media/dude_hurt2.wav");
}

void soundClear(void) {
}

void soundPlay(SoundId id) {
	esSound_play(sounds + id);
}


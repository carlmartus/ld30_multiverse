#pragma once

typedef enum {
	SOUND_SHOT,
	SOUND_RELOAD,
	SOUND_FLAP,
	SOUND_BAT1,

	SOUND_DUDEHURT1,
	SOUND_DUDEHURT2,

	SOUND_COUNT,
} SoundId;

void soundInit(void);
void soundClear(void);
void soundPlay(SoundId id);


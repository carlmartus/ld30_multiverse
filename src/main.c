#include <estk.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include "common.h"
#include "map.h"
#include "dude.h"

enum {
	SHAD_TEXTURE,
	SHAD_MVP,
};

static esShader shad;
static esTexture sprites;

static void frame(float time) {
	if (time > 0.8f) {
		esLog(ES_INFO, "Lag %.3 s", time);
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	esShader_use(&shad);
	glUniform1i(esShader_uniformGl(&shad, SHAD_TEXTURE), 0);

	float dudeX, dudeY;
	dude_readPos(&dudeX, &dudeY);

	// View
	esMat4f mat;
	esProj_ortho(&mat,
			dudeX - SCREEN_RADIUS, dudeY - SCREEN_RADIUS,
			dudeX + SCREEN_RADIUS, dudeY + SCREEN_RADIUS);
	glUniformMatrix4fv(esShader_uniformGl(&shad, SHAD_MVP),
			1, 0, (const float*) &mat);

	// Map
	map_render(dudeX, dudeY, SCREEN_RADIUS*2.2f);

	// Entities
	dude_frame(time);
	dude_render();

	esSprites2d_prepear();

	esSprites2d_render();
	esGame_glSwap();
}

static void loop_exit(void) {
	dude_clear();
	map_clear();
	esSprites2d_clear();
	esTexture_free(&sprites);
	esShader_free(&shad);
}

static void callback_quit(int sdlkey, int down) {
	esGame_loopQuit();
}

static void mouseEvent(int button, int down, int x, int y) {
	float ax = (float) x / (float) SCREEN_REZ;
	float ay = (float) y / (float) SCREEN_REZ;

	ax = SCREEN_RADIUS * (2.0f * ax - 1.0f);
	ay = SCREEN_RADIUS * (2.0f * ay - 1.0f);
	dude_setAim(ax, -ay);
}

int main(int argc, char **argv) {
	esGame_init(SCREEN_REZ, SCREEN_REZ);
	esLogVersion();

	SDL_ShowCursor(SDL_DISABLE);

	// Sprite textures
	if (!esTexture_load(&sprites, "media/sprites.png", TEX_NONE, TEX_NONE)) {
		printf("Cannot load image");
		return 1;
	}

	// Sprite shaders
	if (!esShader_dual(&shad, "media/sprites.vert", "media/sprites.frag")) {
		esLog(ES_ERRO, "Cannot load shaders");
		return 1;
	}

	if (!(
				esShader_uniformRegister(&shad, SHAD_TEXTURE, "un_tex0") &&
				esShader_uniformRegister(&shad, SHAD_MVP, "un_mvp")))   {

		esLog(ES_ERRO, "Cannot get uniform constant");
		return 1;
	}

	glClearColor(0.3, 0.4, 0.5, 1.0);

	esSprites2d_init(8, 6000);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	map_generate(0);
	dude_init();

	esGame_registerMouse(mouseEvent);
	esGame_registerKey(SDLK_q, callback_quit);
	esGame_loop(frame, loop_exit, 0);
	return 0;
}


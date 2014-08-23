#include <estk.h>
#include <GL/glew.h>
#include <SDL/SDL.h>

static esTexture sprites;

static void frame(float time) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	esSprites2d_put(0.5f, 0.5f, 0.1f, 0.0f, 0, 1, ES_SPRITE_FLIPX);
	esSprites2d_prepear();
	esSprites2d_render();

	esGame_glSwap();
}

static void loop_exit(void) {
	esSprites2d_clear();
	esTexture_free(&sprites);
}

static void callback_quit(int sdlkey, int down) {
	esGame_loopQuit();
}

int main(int argc, char **argv) {
	esGame_init(400, 300);
	esLogVersion();


	if (!esTexture_load(&sprites, "media/sprites.png", TEX_LINEAR, TEX_LINEAR)) {
		printf("Cannot load image!\n");
		return 1;
	}

	glClearColor(0.3, 0.4, 0.5, 1.0);

	esSprites2d_init(4, 100);

	esGame_registerKey(SDLK_q, callback_quit);
	esGame_loop(frame, loop_exit, 0);
	return 0;
}


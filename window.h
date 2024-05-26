#pragma once
#include "resource.h"
class Window {
public:
	Window()=default;
	~Window()=default;
	void on_create() {
		//´°¿Ú
		window = SDL_CreateWindow(
			"Game",
			100, 100,
			WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
		);
		if (window == NULL) {
			SDL_Log("Cannot create window,%s", SDL_GetError());
			return;
		}
		//äÖÈ¾Æ÷
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (render == NULL) {
			SDL_Log("Cannot create renderer,%s", SDL_GetError());
			return;
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("Init failed, %s", SDL_GetError());
			return;
		}
		if (!IMG_Init(IMG_INIT_PNG)) {
			SDL_Log("Cannot init img,%s", SDL_GetError());
			return;
		}
		return;
	}
	void on_destroy() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);
		IMG_Quit();
		SDL_Quit();
		delete this;
	}
	SDL_Window* get_window() { return window; }
	SDL_Renderer* get_render() { return render; }
private:
	SDL_Window* window;
	SDL_Renderer* render;
};
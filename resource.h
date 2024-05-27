#pragma once
#include "constant.h"
#include "window.h"

SDL_Texture *img_player=nullptr;

void resource_load(Window* win) {
	if (!IMG_Init(IMG_INIT_PNG)) {
		SDL_Log("Cannot init img,%s", SDL_GetError());
		return;
	}
	//Íæ¼ÒÍ¼Ïñ
	img_player=IMG_LoadTexture(win->get_render(), "resource/blue.png");
	if (img_player == NULL) {SDL_Log("Cannot load img_player,%s", SDL_GetError());}
}

void resource_destroy() {
	SDL_DestroyTexture(img_player);
	IMG_Quit();
}
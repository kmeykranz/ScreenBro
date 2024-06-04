#pragma once
#include "constant.h"
#include "window.h"

SDL_Texture *img_player=nullptr;
SDL_Texture* img_enemy = nullptr;
TTF_Font* font = nullptr;

void resource_load(Window* win) {
	//×ÖÌå
	font = TTF_OpenFont("resource/pixel.TTF", 40);
	if (!font) { SDL_Log("font not loaded"); }
	//Íæ¼ÒÍ¼Ïñ
	img_player=IMG_LoadTexture(win->get_render(), "resource/blue.png");
	if (img_player == NULL) {SDL_Log("Cannot load img_player,%s", SDL_GetError());}
	img_enemy = IMG_LoadTexture(win->get_render(), "resource/red.png");
	if (img_player == NULL) { SDL_Log("Cannot load img_enemy,%s", SDL_GetError()); }
}

void resource_destroy() {
	TTF_CloseFont(font);
	SDL_DestroyTexture(img_player);
	SDL_DestroyTexture(img_enemy);
}
#pragma once
#include "constant.h"
#include "window.h"

SDL_Texture *img_player=nullptr;
SDL_Texture* img_menu = nullptr;
TTF_Font* font = nullptr;

void resource_load(Window* win) {
	//字体
	font = TTF_OpenFont("resource/pixel.TTF", 40);
	if (!font) { SDL_Log("font not loaded"); }
	//玩家图像
	img_player=IMG_LoadTexture(win->get_render(), "resource/blue.png");
	//开始页面
	img_menu= IMG_LoadTexture(win->get_render(), "resource/start_menu.png");
}

void resource_destroy() {
	TTF_CloseFont(font);
	SDL_DestroyTexture(img_player);
	SDL_DestroyTexture(img_menu);
}
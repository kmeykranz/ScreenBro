#pragma once
#include "constant.h"
#include "vector2.h"

class Platform {
public:
	Vector2 size = Vector2(0, 0);
	Vector2 position = Vector2(0, 0);
	SDL_Rect rect = { 0 };
public:
	Platform() {
		//获取屏幕大小
		SDL_DisplayMode displayMode;
		if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
			SDL_Log("SDL_GetCurrentDisplayMode Error: %s\n", SDL_GetError());
			return;
		}
		screenWidth = displayMode.w;
		screenHeight = displayMode.h;

		size = Vector2((float)screenWidth / 5, (float)screenHeight / 5);
	};

	~Platform() = default;

	void on_create() {
		//窗口
		window = SDL_CreateWindow(
			"Platfrom",
			position.x, position.y,
			size.x, size.y, SDL_WINDOW_SHOWN
		);
		if (window == NULL) {
			SDL_Log("Cannot create window,%s", SDL_GetError());
			return;
		}
		//渲染器
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (render == NULL) {
			SDL_Log("Cannot create renderer,%s", SDL_GetError());
			return;
		}

		//资源加载
		img_enemy = IMG_LoadTexture(render, "resource/red.png");
		img_player = IMG_LoadTexture(render, "resource/blue.png");
		if (img_player == nullptr) { SDL_Log("img_player is null"); };

		return;
	}

	void on_destroy() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);

		SDL_DestroyTexture(img_enemy);
		SDL_DestroyTexture(img_player);
		delete this;
	}
	
	void raise_window() {
		SDL_RaiseWindow(window);
	}

	void on_update() {
		SDL_SetWindowPosition(window, position.x, position.y);
		SDL_SetWindowSize(window, size.x, size.y);
	}

	void on_draw() {
		SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(render, 255, 255, 200, 255);
		SDL_RenderClear(render);
	}

	void set_position(float x, float y) {
		position.x += x;
		position.y += y;
	}

	void set_size(float x, float y) {
		size.x += x;
		size.y += y;

		rect = { (int)position.x,(int)position.y,(int)size.x,(int)size.y };
	}

	Vector2 get_position() {
		return position;
	}
	Vector2 get_size() {
		return size;
	}

	int get_screen_width() {
		return screenWidth;
	}

	int get_screen_height() {
		return screenHeight;
	}

	//获取边界
	int border_up() const{
		return position.y;
	}

	int border_down() const{
		return position.y + size.y;
	}

	int border_left() const{
		return position.x;
	}

	int border_right() const{
		return position.x + size.x;
	}

	SDL_Window* get_window() { return window; }
	SDL_Renderer* get_render() { return render; }

public:
	//资源指针
	SDL_Texture* img_enemy = nullptr;
	SDL_Texture* img_player = nullptr;
private:
	SDL_Window* window=nullptr;
	SDL_Renderer* render = nullptr;
	int screenWidth=0;
	int screenHeight=0;
};
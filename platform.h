#pragma once
#pragma once
#include "constant.h"
#include "vector2.h"

class Platform {
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

		//加载资源
		//玩家图像
		img_enemy = IMG_LoadTexture(render, "resource/red.png");

		return;
	}
	
	void raise_window() {
		SDL_RaiseWindow(window);
	}

	void on_update() {
		SDL_SetWindowPosition(window, position.x, position.y);
		SDL_SetWindowSize(window, size.x, size.y);
	}

	void on_destroy() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);

		SDL_DestroyTexture(img_enemy);
		delete this;
	}

	void set_position(float x, float y) {
		position.x += x;
		position.y += y;
	}

	void set_size(float x, float y) {
		size.x += x;
		size.y += y;
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
	int get_up_border() {
		return position.y;
	}

	int get_down_border() {
		return position.y + size.y;
	}

	int get_left_border() {
		return position.x;
	}

	int get_right_border() {
		return position.x + size.x;
	}

	SDL_Window* get_window() { return window; }
	SDL_Renderer* get_render() { return render; }

public:
	//资源指针
	SDL_Texture* img_enemy = nullptr;
private:
	SDL_Window* window=nullptr;
	SDL_Renderer* render = nullptr;
	Vector2 size = Vector2(0, 0);
	Vector2 position = Vector2(0, 0);
	int screenWidth=0;
	int screenHeight=0;
};
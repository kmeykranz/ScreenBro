#pragma once
#include "constant.h"
#include "vector2.h"

class Window {
public:
	Window()=default;
	~Window()=default;
	void on_create() {
		//SDL初始化
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("Init failed, %s", SDL_GetError());
			return;
		}

		//获取屏幕大小
		SDL_DisplayMode displayMode;
		if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
			SDL_Log("SDL_GetCurrentDisplayMode Error: %s\n", SDL_GetError());
			return;
		}
		int screenWidth = displayMode.w;
		int screenHeight = displayMode.h;

		size = Vector2((float)screenWidth/2, (float)screenHeight/2);

		//窗口
		window = SDL_CreateWindow(
			"WindowShooter",
			position.x, position.y,
			size.x, size.y, SDL_WINDOW_BORDERLESS |SDL_WINDOW_SHOWN
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
		return;
	}

	void on_update() {
		SDL_SetWindowPosition(window, position.x, position.y);
	}

	void on_destroy() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);
		SDL_Quit();
		delete this;
	}
	void on_move(float x,float y) {
		position.x += x;
		position.y += y;
	}
	
	Vector2 get_position() {
		return position;
	}
	Vector2 get_size(){
		return size;
	}

	SDL_Window* get_window() { return window; }
	SDL_Renderer* get_render() { return render; }
private:
	SDL_Window* window;
	SDL_Renderer* render;
	Vector2 size = Vector2(0, 0);
	Vector2 position = Vector2(0, 0);
	int screenWidth;
	int screenHeight;
};
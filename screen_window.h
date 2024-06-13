#pragma once
#pragma once
#include "constant.h"
#include "window.h"
#include "vector2.h"
#include "windows.h" //winapi
#include <SDL_syswm.h> //用于窗口透明
#include "SDL_ttf.h"

class ScreenWindow {
public:
	SDL_Texture* img_player = nullptr;
public:
	ScreenWindow() {
		//获取屏幕大小
		SDL_DisplayMode displayMode;
		if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
			SDL_Log("SDL_GetCurrentDisplayMode Error: %s\n", SDL_GetError());
			return;
		}
		screenWidth = displayMode.w;
		screenHeight = displayMode.h;

		size = Vector2((float)screenWidth, (float)screenHeight);

		//窗口
		window = SDL_CreateWindow(
			"WindowShooter",
			position.x, position.y,
			size.x, size.y, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN
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

		// 使窗口始终置顶
		SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);
		//设置透明
		SetTransparent(window, RGB(0, 0, 0));

		//资源加载
		img_player = IMG_LoadTexture(render, "resource/blue.png");
		if (img_player == nullptr) { SDL_Log("img_player is null"); }

		return;
	};

	~ScreenWindow() = default;

	void on_enter() {
		SDL_ShowWindow(window);
	}

	void on_exit() {
		SDL_HideWindow(window);
	}

	void on_update() {
		SDL_SetWindowPosition(window, position.x, position.y);
	}

	void on_destroy() {
		SDL_DestroyTexture(img_player);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);
		delete this;
	}
	void on_move(float x, float y) {
		position.x += x;
		position.y += y;
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

	void SetTransparent(SDL_Window* window, COLORREF colorKey) {
		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(window, &wmInfo);

		HWND hwnd = wmInfo.info.win.window;
		LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
		SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hwnd, colorKey, 0, LWA_COLORKEY);
	}


	SDL_Window* get_window() { return window; }
	SDL_Renderer* get_render() { return render; }
private:
	SDL_Window* window=nullptr;
	SDL_Renderer* render=nullptr;
	Vector2 size = Vector2(0, 0);
	Vector2 position = Vector2(0, 0);
	int screenWidth=0;
	int screenHeight=0;
};
#pragma once
#include "scene.h"
#include "scene_manager.h"

extern SceneManager scene_manager;

class MenuScene :public Scene {
public:
	MenuScene() {
		window = new Window();
		//资源加载
		img_menu = IMG_LoadTexture(window->get_render(), "resource/start_menu.png");
	};

	~MenuScene() = default;

	void on_enter() {
		SDL_Log("[Game Scene] -> Menu Scene");
		SDL_ShowWindow(window->get_window());
	};

	void on_exit() {
		SDL_HideWindow(window->get_window());
	}

	void on_update() {
	};

	void on_draw() {
		SDL_Rect rect{0,0,window->get_size().x,window->get_size().y};
		SDL_RenderCopy(window->get_render(), img_menu, 0, &rect);
		SDL_RenderPresent(window->get_render());//生效
	};

	void on_input() {
		//事件
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = 0;
					break;
				case SDLK_SPACE:
					scene_manager.switch_to(SceneManager::SceneType::Game);
					break;
				default:
					break;
				}
			}
		}
	};

	void on_destroy() {
		SDL_HideWindow(window->get_window());
		SDL_DestroyTexture(img_menu);
		delete this;
	}

private:
	Window* window = nullptr;
	SDL_Texture* img_menu;
};
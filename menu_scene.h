#pragma once
#include "scene.h"
#include "scene_manager.h"

extern SceneManager scene_manager;

class MenuScene :public Scene {
public:
	MenuScene(Window *win) { window = win; };
	~MenuScene() = default;

	void on_enter() {
		SDL_Log("Enter Menu Scene");
	};
	void on_update() {
	};
	void on_draw() {
		//背景色
		SDL_SetRenderDrawColor(window->get_render(), 255, 255, 255, 255);
		SDL_RenderClear(window->get_render());
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
	void on_exit() {
	};
private:
	Window* window = nullptr;
};
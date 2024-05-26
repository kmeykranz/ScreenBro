#pragma once
#include "scene.h"
#include "player.h"

extern SceneManager scene_manager;

class GameScene :public Scene {
public:
	GameScene(Window *win) { window = win; };
	~GameScene() = default;

	void on_enter() {
		SDL_Log("Enter Game Scene");

		//创建玩家
		player = new Player(window);
		player->on_create();
	};
	void on_update() {
		player->PhysicsProcess(60);
	};
	void on_draw() {
		//背景色
		SDL_SetRenderDrawColor(window->get_render(), 255, 255, 255, 255);
		SDL_RenderClear(window->get_render());
		player->on_update();
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
					scene_manager.switch_to(SceneManager::SceneType::Menu);
					break;
				default:
					break;
				}
				//移动（Y：+1是向下，X：+1是向右）
				keyboard_state_array = SDL_GetKeyboardState(NULL);
				if (keyboard_state_array[SDL_SCANCODE_UP]) {
					player->SetDirectionY(-1);
				}
				else if (keyboard_state_array[SDL_SCANCODE_DOWN]) {
					player->SetDirectionY(1);
				}
				if (keyboard_state_array[SDL_SCANCODE_LEFT]) {
					player->SetDirectionX(-1);
				}
				else if (keyboard_state_array[SDL_SCANCODE_RIGHT]) {
					player->SetDirectionX(1);
				}
				break;
			case SDL_KEYUP:
				keyboard_state_array = SDL_GetKeyboardState(NULL);
				if (!keyboard_state_array[SDL_SCANCODE_UP] && !keyboard_state_array[SDL_SCANCODE_DOWN]) {
					player->SetDirectionY(0);
				}
				if (!keyboard_state_array[SDL_SCANCODE_LEFT] && !keyboard_state_array[SDL_SCANCODE_RIGHT]) {
					player->SetDirectionX(0);
				}
				break;
			}
		}
		return;
	};
	void on_exit() {
		return;
	};

private:
	Window* window=nullptr;
	Player* player=nullptr;
	const Uint8* keyboard_state_array=nullptr;
};
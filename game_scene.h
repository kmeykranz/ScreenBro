#pragma once
#include "scene.h"
#include "player.h"
#include "bullet.h"
#include <algorithm>

extern SceneManager scene_manager;

class GameScene :public Scene {
public:
	GameScene(Window* win) :window(win) {}
	~GameScene() = default;

	void on_enter() {
		SDL_Log("Enter Game Scene");
		
		//创建玩家
		player = new Player(window);
		player->on_create();

		std::fill(bullet, bullet + 50, nullptr);
	};
	void on_update() {
		player->PhysicsProcess(60);
	};
	void on_draw() {
		//背景色
		SDL_SetRenderDrawColor(window->get_render(), 255, 255, 255, 255);
		SDL_RenderClear(window->get_render());
		//子弹
		for (int i = 0; i < 50; i++) {
			if (bullet[i] != nullptr) {
				if (bullet[i]->get_remove_state()) {
					bullet[i]->on_destroy();
					bullet[i] = nullptr;
					SDL_Log("[%d]bullet destroyed", i);
					continue;
				}
				bullet[i]->on_update();
			}
		}
		//玩家
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
				if (keyboard_state_array[SDL_SCANCODE_W]) {
					player->SetDirectionY(-1);
				}
				else if (keyboard_state_array[SDL_SCANCODE_S]) {
					player->SetDirectionY(1);
				}
				if (keyboard_state_array[SDL_SCANCODE_A]) {
					player->SetDirectionX(-1);
				}
				else if (keyboard_state_array[SDL_SCANCODE_D]) {
					player->SetDirectionX(1);
				}
				//射击
				if (keyboard_state_array[SDL_SCANCODE_J]) {
					for (int i = 0; i < 50;i++) {
						if (bullet[i] == nullptr) {
							bullet[i] = new Bullet(window);
							bullet[i]->set_position(player->get_position());
							bullet[i]->set_direction(player->get_direction());
							break;
						}
					}
				}
				break;
			case SDL_KEYUP:
				keyboard_state_array = SDL_GetKeyboardState(NULL);
				if (!keyboard_state_array[SDL_SCANCODE_W] && !keyboard_state_array[SDL_SCANCODE_S]) {
					player->SetDirectionY(0);
				}
				if (!keyboard_state_array[SDL_SCANCODE_A] && !keyboard_state_array[SDL_SCANCODE_D]) {
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
	void on_destroy() {
		player->on_destroy();
		for (int i = 0; i < 50;i++) {
			if (bullet[i] != nullptr) {
				SDL_Log("[%d]bullet destroyed",i);
				bullet[i]->on_destroy();
			}
		}
		delete this;
	}
private:
	Window* window=nullptr;
	Player* player=nullptr;
	const Uint8* keyboard_state_array=nullptr;
	Bullet* bullet[50] = { nullptr };
};
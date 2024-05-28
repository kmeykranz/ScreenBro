#pragma once
#include "scene.h"
#include "player.h"
#include "bullet.h"
#include <algorithm>
#include "timer.h"
#include "enemy.h"
#include <stdlib.h>	//生成随机数
#include <time.h>	//生成随机数

extern SceneManager scene_manager;

class GameScene :public Scene {
public:
	GameScene(Window* win) :window(win) {}
	~GameScene() = default;

	void on_enter() {
		SDL_Log("Enter Game Scene");
		
		//数组初始化
		std::fill(bullet, bullet + 50, nullptr);
		std::fill(enemy, enemy + 50, nullptr);

		//创建玩家
		player = new Player(window);
		player->on_create();

		//射击间隔计时器
		shoot_timer.set_wait_time(0.3);
		shoot_timer.set_callback([this]() {
			this->player->set_can_shoot(true);
		});

		//敌人生成计时器
		enemy_timer.set_wait_time(5);
		enemy_timer.set_callback([this](){
			this->can_create_enemy = true;
		});
	};

	void on_update() {
		player->PhysicsProcess(delta);
		shoot_timer.on_update(delta);
		enemy_timer.on_update(delta);

		//敌人生成
		if (can_create_enemy) {
			//随机数种子
			srand((unsigned int)time(NULL));
			//寻找存放敌人的位置
			for (int i = 0; i < 50; i++) {
				if (enemy[i] == nullptr) {
					SDL_Log("[%d]enemy created", i);
					enemy[i] = new Enemy(window);
					enemy[i]->on_create();
					enemy[i]->set_position(rand()% (int)(window->get_size().x * 2), rand() % (int)(window->get_size().y * 2));
					break;
				}
			}
			can_create_enemy = false;
		}

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
		//敌人
		for (int i = 0; i < 50; i++) {
			if (enemy[i] != nullptr) {
				//移动判断
				if (enemy[i]->get_position().x > player->get_position().x) { enemy[i]->SetDirectionX(-1); }
				else if (enemy[i]->get_position().x < player->get_position().x) { enemy[i]->SetDirectionX(1); }
				if (enemy[i]->get_position().y > player->get_position().y) { enemy[i]->SetDirectionY(-1); }
				else if (enemy[i]->get_position().y < player->get_position().y) { enemy[i]->SetDirectionY(1); }
				//敌人物理逻辑
				enemy[i]->PhysicsProcess(delta);
				//更新显示
				enemy[i]->on_update();
			}
		}
		//玩家
		player->on_update();
		SDL_RenderPresent(window->get_render());//生效
	};

	//输入
	void on_input() {
		//键盘获取
		keyboard_state_array = SDL_GetKeyboardState(NULL);
		//射击控制
		if (keyboard_state_array[SDL_SCANCODE_J]) {
			if (player->get_can_shoot()) {
				//寻找存放子弹的位置
				for (int i = 0; i < 50; i++) {
					if (bullet[i] == nullptr) {
						bullet[i] = new Bullet(window);
						bullet[i]->set_position(player->get_position());
						bullet[i]->set_direction(player->get_direction());
						break;
					}
				}
				player->set_can_shoot(false);
			}
		}
		//移动控制（Y：+1是向下，X：+1是向右）
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

		//松开按键
		if (!keyboard_state_array[SDL_SCANCODE_W] && !keyboard_state_array[SDL_SCANCODE_S]) {
			player->SetDirectionY(0);
		}
		if (!keyboard_state_array[SDL_SCANCODE_A] && !keyboard_state_array[SDL_SCANCODE_D]) {
			player->SetDirectionX(0);
		}

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
			default:
				break;
			}
		}
		return;
	};

	void on_exit() {
		return;
	};

	//释放函数
	void on_destroy() {
		player->on_destroy();
		for (int i = 0; i < 50;i++) {
			if (bullet[i] != nullptr) {
				SDL_Log("[%d]bullet destroyed",i);
				bullet[i]->on_destroy();
			}
			if (enemy[i] != nullptr) {
				SDL_Log("[%d]enemy destroyed", i);
				enemy[i]->on_destroy();
			}
		}
		delete this;
	}

private:
	Window* window=nullptr;						//窗口指针
	Player* player=nullptr;						//玩家指针
	const Uint8* keyboard_state_array=nullptr;	//键盘状态指针
	Bullet* bullet[50] = { nullptr };			//子弹指针数组
	Enemy* enemy[50] = { nullptr };
	Timer shoot_timer;
	Timer enemy_timer;
	float delta= 1 / FRAMERATE;
	bool can_create_enemy=false;				//是否可以生成敌人
};


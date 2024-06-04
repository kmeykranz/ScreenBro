#pragma once
#include "scene.h"
#include "player.h"
#include "bullet.h"
#include <algorithm>
#include "timer.h"
#include "enemy.h"
#include <stdlib.h>	//生成随机数
#include <time.h>	//生成随机数
#include "scene_manager.h"
#include <iostream>
#include <string>

extern SceneManager scene_manager;
extern TTF_Font *font;

class GameScene :public Scene {
public:
	GameScene(Window* win) :window(win) {}
	~GameScene() = default;

	//初始化
	void on_enter() {
		SDL_Log("Enter Game Scene");
		
		//数组初始化
		std::fill(bullet, bullet + BULLET_MAX, nullptr);
		std::fill(enemy, enemy + ENEMY_MAX, nullptr);

		//随机数种子
		srand((unsigned int)time(NULL));

		//创建玩家
		player = new Player(window);
		player->on_create();

		//时间计时器
		game_timer.set_wait_time(1);
		game_timer.set_callback([this]() {
			this->timer_number++;
			std::string str = std::to_string(this->timer_number);
			if (timer_number < 10) { str = '0'+str; }
			//创建文字
			SDL_Surface* time_surface = TTF_RenderUTF8_Solid(font, str.c_str(), {200,0,0,255});
			this->time_texture = SDL_CreateTextureFromSurface(window->get_render(), time_surface);
			SDL_FreeSurface(time_surface);
		});

		//射击间隔计时器
		shoot_timer.set_wait_time(0.3);
		shoot_timer.set_callback([this]() {
			this->player->set_can_shoot(true);
		});

		//敌人生成计时器
		enemy_timer.set_wait_time(0.8);
		enemy_timer.set_callback([this](){
			this->can_create_enemy = true;
		});
	};

	//更新循环
	void on_update() {
		player->PhysicsProcess(delta);
		game_timer.on_update(delta);
		shoot_timer.on_update(delta);
		enemy_timer.on_update(delta);

		//敌人生成
		CreateEnemy();
		//检查碰撞
		CheckCollision();
	};

	//绘制循环
	void on_draw() {
		//背景色
		SDL_SetRenderDrawBlendMode(window->get_render(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(window->get_render(), 0, 0, 0, SDL_ALPHA_TRANSPARENT);
		SDL_RenderClear(window->get_render());
		//子弹
		BulletUpdate();
		//敌人
		EnemyUpdate();
		//玩家
		player->on_update();
		//文字
		SDL_Rect time_rect = { 10,0,50,50 };
		SDL_RenderCopy(window->get_render(), time_texture, NULL, &time_rect);
		//生效
		SDL_RenderPresent(window->get_render());
	};

	//输入
	void on_input() {
		//键盘获取
		keyboard_state_array = SDL_GetKeyboardState(NULL);
		//射击控制
		if (keyboard_state_array[SDL_SCANCODE_J]) {
			PlayerShoot();
		}
		//移动控制（Y：+1是向下，X：+1是向右）
		if (keyboard_state_array[SDL_SCANCODE_W]|| keyboard_state_array[SDL_SCANCODE_UP]) {
			player->SetDirectionY(-1);
		}
		else if (keyboard_state_array[SDL_SCANCODE_S]||keyboard_state_array[SDL_SCANCODE_DOWN]) {
			player->SetDirectionY(1);
		}
		else {
			player->SetDirectionY(0);
		}
		if (keyboard_state_array[SDL_SCANCODE_A]||keyboard_state_array[SDL_SCANCODE_LEFT]) {
			player->SetDirectionX(-1);
		}
		else if (keyboard_state_array[SDL_SCANCODE_D]|| keyboard_state_array[SDL_SCANCODE_RIGHT]) {
			player->SetDirectionX(1);
		}
		else {
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

	//退出
	void on_exit() {
		return;
	};

	//释放函数
	void on_destroy() {
		player->on_destroy();
		SDL_DestroyTexture(time_texture);
		for (int i = 0; i < BULLET_MAX;i++) {
			if (bullet[i] != nullptr) {
				SDL_Log("[%d]Bullet Destroyed",i);
				bullet[i]->on_destroy();
			}
			if (enemy[i] != nullptr) {
				SDL_Log("[%d]Enemy Destroyed", i);
				enemy[i]->on_destroy();
			}
		}
		delete this;
	}

//---------游戏函数---------
public:
	//创建敌人
	void CreateEnemy() {
		if (can_create_enemy) {
			//寻找存放敌人的位置
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (enemy[i] == nullptr) {
					SDL_Log("[%d]Enemy Created", i);
					enemy[i] = new Enemy(window);
					enemy[i]->on_create();
					//enemy[i]->set_position(0, 0);
					//随机位置生成在地图边缘
					int edge = rand() % 4;
					switch (edge) {
					case 0:	//上边
						enemy[i]->set_position(rand () % window->get_screen_width(), 0);
						break;
					case 1: // 下边
						enemy[i]->set_position(rand() % window->get_screen_width(),window->get_screen_height());
						break;
					case 2: // 左边
						enemy[i]->set_position(0, (rand() % window->get_screen_height()));
						break;
					case 3: // 右边
						enemy[i]->set_position(window->get_screen_width(),window->get_screen_height());
						break;
					default:
						break;
					}
					break;
				}
			}
			can_create_enemy = false;
		}
	}

	//敌人更新
	void EnemyUpdate() {
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i] != nullptr) {
				//是否清除
				if (enemy[i]->get_remove_state()) {
					enemy[i]->on_destroy();
					enemy[i] = nullptr;
					SDL_Log("[%d]Enemy Destroyed", i);
					continue;
				}
				//移动判断
				if (enemy[i]->get_position().x > player->get_position().x + player->get_size().x/4) { enemy[i]->SetDirectionX(-1); }
				else if (enemy[i]->get_position().x + enemy[i]->get_size().x/4 < player->get_position().x) { enemy[i]->SetDirectionX(1); }
				else { enemy[i]->SetDirectionX(0); }
				if (enemy[i]->get_position().y > player->get_position().y + player->get_size().y/4) { enemy[i]->SetDirectionY(-1); }
				else if (enemy[i]->get_position().y + enemy[i]->get_size().y/4 < player->get_position().y) { enemy[i]->SetDirectionY(1); }
				else{ enemy[i]->SetDirectionY(0); }
				//敌人物理逻辑
				enemy[i]->PhysicsProcess(delta);
				//敌人和敌人
				for (int j = i + 1; j < ENEMY_MAX; j++) {
					if (enemy[j] != nullptr) {
						if (enemy[i]->check_collision(enemy[j]) == true) {
							enemy[i]->handle_collision(enemy[j]);
						}
					}
				}
				if (enemy[i]->check_collision(player) == true) {
					enemy[i]->handle_collision(player);
				}
				//更新显示
				enemy[i]->on_update();
			}
		}
	}

	//创建子弹（射击）
	void PlayerShoot() {
		if (player->get_can_shoot()) {
			//寻找存放子弹的位置
			for (int i = 0; i < BULLET_MAX; i++) {
				if (bullet[i] == nullptr) {
					bullet[i] = new Bullet(window,i);
					bullet[i]->set_position(player->get_position());
					bullet[i]->set_direction(player->get_direction());
					break;
				}
			}
			player->set_can_shoot(false);
		}
	}

	//子弹更新
	void BulletUpdate() {
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet[i] != nullptr) {
				if (bullet[i]->get_remove_state()) {
					bullet[i]->on_destroy();
					bullet[i] = nullptr;
					SDL_Log("[%d]Bullet Destroyed", i);
					continue;
				}
				bullet[i]->on_update();
			}
		}
	}

	//检查碰撞
	void CheckCollision() {
		//子弹和敌人
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet[i] != nullptr) {
				for (int j = 0; j < ENEMY_MAX; j++) {
					if (bullet[i]!=nullptr&&enemy[j] != nullptr) {
						if (check_hurt(bullet[i], enemy[j])) {
							break;
						}
					}
				}
			}
		}
	}

	//检查子弹是否打到敌人（在检查碰撞中使用）
	bool check_hurt(Bullet *bu,Enemy *en) {
		if (bu->get_position().x >= en->get_position().x &&
			bu->get_position().x <= en->get_position().x+en->get_size().x &&
			bu->get_position().y >= en->get_position().y &&
			bu->get_position().y <= en->get_position().y+en->get_size().y
			) {
			//子弹清除
			bu->on_remove();
			////敌人清除
			en->on_remove();
			return true;
			}
		return false;
	}

private:
	Window* window = nullptr;						//窗口指针
	Player* player = nullptr;						//玩家指针
	SDL_Texture* time_texture = nullptr;
	const Uint8* keyboard_state_array = nullptr;	//键盘状态指针
	Bullet* bullet[BULLET_MAX] = { nullptr };			//子弹指针数组
	Enemy* enemy[ENEMY_MAX] = { nullptr };
	Timer shoot_timer;
	Timer enemy_timer;
	Timer game_timer;
	int timer_number=0;
	float delta = 1 / FRAMERATE;
	bool can_create_enemy = false;				//是否可以生成敌人
};


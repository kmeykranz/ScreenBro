#pragma once
#include "vector2.h"
#include <functional>
#include "screen_window.h"
#include "constant.h"

class Bullet:public Object {
public:
	SDL_Rect rect = {0,0,0,0};
public:
	Bullet(Platform* plat,Vector2 pos,Vector2 dir) :platform(plat),position(pos),direction(dir)  {
		position = pos.operator+(15);
	}
	~Bullet() = default;

	void set_position(Vector2 pos) {
		
	}

	void set_direction(Vector2 dir) {
		direction = dir;
	}

	void on_update() {
		position.operator+=(direction.operator*(20));	//20是速度
		relative_position = position.operator-(platform->get_position());
		rect = { (int)position.x, (int)position.y, (int)size.x, (int)size.y };
		SDL_Rect draw_rect = { (int)relative_position.x, (int)relative_position.y, (int)size.x, (int)size.y };
		SDL_RenderCopy(platform->get_render(), platform->img_player, NULL, &draw_rect);

		if (position.x + size.x > platform->border_right() || position.x < platform->border_left())can_remove = 1;
		if (position.y + size.y > platform->border_down() || position.y < platform->border_up())can_remove=1;
	}


	void on_remove() {
		can_remove = true;
	}

	void on_destroy() {
		delete this;
	}

	bool get_remove_state() {
		return can_remove;
	}

	//获取玩家位置
	Vector2 get_position() {
		return position;
	}

private:
	Vector2 position = Vector2(200,200);		//子弹位置
	Vector2 relative_position= Vector2(0, 0);
	Vector2 direction = Vector2(0, 0);			//子弹方向
	Vector2 size = Vector2(20, 20);				//子弹大小
	int damage = 10;
	bool valid = true;
	bool can_remove = false;
	Platform* platform=nullptr;
};
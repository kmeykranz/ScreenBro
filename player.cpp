#include "player.h"

Player::Player(float x, float y, float w, float h):Object(x,y,w,h){
	dir_x = 0;
	dir_y = 0;
	m_x = 100; m_y = 100;
	v_x = 0; v_y = 0;
	x_expand = 0; y_expand = 0;
}

void Player::tick_physics(State state, float delta) {
	// 这里可以添加每个状态的物理逻辑处理
	switch (state) {
	case IDLE:
		Move(0);
		break;
	case WALK:
		Move(SPEED);
		Expand();
		break;
	}
}

State Player::get_next_state(State current) {
	// 这里可以添加获取下一个状态的逻辑
	switch (current) {
	case IDLE:
		if (dir_x != 0 || dir_y != 0) {
			SDL_Log("[PLAYER] IDLE -> WALK");
			return WALK;
		}
		break;
	case WALK:
		if (dir_x == 0 && dir_y == 0) {
			SDL_Log("[PLAYER] WALK -> IDLE");
			return IDLE;
		}
		break;
	}
	return current;
}

void Player::transition_state(State current, State next) {
	// 这里可以添加状态转换逻辑:角色动画变换
	switch (current) {
	case IDLE:
		break;
	case WALK:
		break;
	}
}

int Player::get_x_expand()
{
	return x_expand;
}

int Player::get_y_expand()
{
	return y_expand;
}

void Player::x_expanded()
{
	x_expand = 0;
	return;
}

void Player::y_expanded()
{
	y_expand = 0;
	return;
}

void Player::Expand()
{
	if (m_x >= 500) {
		m_x -= 400;
		x_expand = 1;
	}
	else if (m_x <= 50) {
		m_x += 400;
		x_expand = -1;
	}
	if (m_y >= 300) {
		m_y -= 200;
		y_expand = 1;
	}
	else if (m_y <= 50) {
		m_y += 200;
		y_expand = -1;
	}
}

SDL_Window* Player::CreateWindow()
{
	//创建窗口
	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Cannot init video,%s", SDL_GetError());
		//running = 0;
		return 0;
	}
	win = SDL_CreateWindow(
		"Game",
		m_x, m_y,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
	);
	if (win == NULL) {
		SDL_Log("Cannot create window,%s", SDL_GetError());
		//running = 0;
		return 0;
	}
	return win;
}

void Player::Move(float speed)
{
	if (speed==0) {
		v_x = 0;
		v_y = 0;
	}
	else{
		if (v_x < speed) {
			v_x += ACCELERATION/FRAMERATE;
		}
		if (v_y < speed) {
			v_y += ACCELERATION/FRAMERATE;
		}
	}
	if (dir_x && dir_y) {
		m_x += dir_x * v_x*0.707;
		m_y += dir_y * v_y*0.707;
	}
	else {
		m_x += dir_x * v_x;
		m_y += dir_y * v_y;
	}
}

void Player::SetDirectionY(float dir)
{
	dir_y = dir;
	//SDL_Log("direction y: %d", dir_y);
}

void Player::SetDirectionX(float dir)
{
	dir_x = dir;
	//SDL_Log("direction x: %d", dir_x);
}
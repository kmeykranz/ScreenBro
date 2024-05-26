#pragma once
#include "resource.h"
#include "object.h"

class Player : public Object
{
public:
	Player(Window* win) { window = win; };
	~Player()=default;

	void on_create(){
		SetCurrentState(State::IDLE);
		SDL_SetWindowPosition(window->get_window(), win_x, win_y);
		//玩家图像
		texture = IMG_LoadTexture(window->get_render(), "resource/blue.png");
		if (texture == NULL) {
			SDL_Log("Cannot load texture,%s", SDL_GetError());
		}
		m_width = 50, m_height = 50;
	}

	void on_exit()
	{
		SDL_DestroyTexture(texture);
	}

	void tick_physics(State state, float delta) {
		// 这里可以添加每个状态的物理逻辑处理
		switch (state) {
		case State::IDLE:
			on_move(0);
			break;
		case State::WALK:
			on_move(SPEED);
			on_update();
			break;
		}
	}

	State get_next_state(State current) {
		// 这里可以添加获取下一个状态的逻辑
		switch (current) {
		case State::IDLE:
			if (dir_x != 0 || dir_y != 0) {
				SDL_Log("[PLAYER] IDLE -> WALK");
				return State::WALK;
			}
			break;
		case State::WALK:
			if (dir_x == 0 && dir_y == 0) {
				SDL_Log("[PLAYER] WALK -> IDLE");
				return State::IDLE;
			}
			break;
		}
		return current;
	}

	void transition_state(State current, State next) {
		// 这里可以添加状态转换逻辑:角色动画变换
		switch (current) {
		case State::IDLE:
			break;
		case State::WALK:
			break;
		}
	}

	void on_update()
	{
		rect = { (int)m_x, (int)m_y, (int)m_width, (int)m_height };
		SDL_Point p{ 25,25 };
		SDL_RenderCopyEx(window->get_render(), texture, NULL, &rect, angle, &p, flip);

		//窗口移动判断
		if (m_x + m_width / 2 > WINDOW_WIDTH) {
			win_x += WINDOW_WIDTH;
			m_x -= WINDOW_WIDTH;
			SDL_SetWindowPosition(window->get_window(), win_x, win_y);
		}
		else if (m_x + m_width / 2 < 0) {
			win_x -= WINDOW_WIDTH;
			m_x += WINDOW_WIDTH;
			SDL_SetWindowPosition(window->get_window(), win_x, win_y);
		}
		if (m_y + m_height / 2 > WINDOW_HEIGHT) {
			win_y += WINDOW_HEIGHT;
			m_y -= WINDOW_HEIGHT;
			SDL_SetWindowPosition(window->get_window(), win_x, win_y);
		}
		else if (m_y + m_height / 2 < 0) {
			win_y -= WINDOW_HEIGHT;
			m_y += WINDOW_HEIGHT;
			SDL_SetWindowPosition(window->get_window(), win_x, win_y);
		}
	}

	void on_move(float speed)
	{
		//加速度
		if (speed == 0) {
			v_x = 0;
			v_y = 0;
		}
		else {
			if (v_x < speed) {
				v_x += ACCELERATION / FRAMERATE;
			}
			if (v_y < speed) {
				v_y += ACCELERATION / FRAMERATE;
			}
		}
		//移动
		float b_x = m_x, b_y = m_y;

		if (dir_y == 1) {
			flip = SDL_FLIP_VERTICAL;
		}
		else if (dir_y == -1) {
			flip = SDL_FLIP_NONE;
		}

		if (dir_x && dir_y) {
			m_x += dir_x * v_x * 0.707;
			m_y += dir_y * v_y * 0.707;
			if (dir_x == 1) angle = -45 * dir_y;
			else angle = 45 * dir_y;
		}
		else if (dir_x || dir_y) {
			angle = 0;
			if (dir_x == 1) { flip = SDL_FLIP_NONE; angle = 90; }
			else if (dir_x == -1) { flip = SDL_FLIP_NONE; angle = -90; }
			m_x += dir_x * v_x;
			m_y += dir_y * v_y;
		}

		//墙体碰撞
		if (m_x + win_x > 2 * WINDOW_WIDTH || m_x + win_x < 0)m_x = b_x;
		if (m_y + win_y > 2 * WINDOW_HEIGHT || m_y + win_y < 0)m_y = b_y;
	}

	void SetDirectionY(float dir)
	{
		dir_y = dir;
	}

	void SetDirectionX(float dir)
	{
		dir_x = dir;
	}

private:
    float v_x=0, v_y=0;
    float dir_x=0, dir_y=0;
    float angle=0;
    int win_x=0, win_y=0;
	SDL_Rect rect = {0};
    SDL_RendererFlip flip=SDL_FLIP_NONE;
    Window *window=nullptr;
    SDL_Texture* texture = nullptr;
};
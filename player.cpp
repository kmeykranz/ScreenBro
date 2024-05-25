#include "player.h"

Player::Player(float x, float y, float w, float h):Object(x,y,w,h){
	dir_x = 0; dir_y = 0;
	m_x = x; m_y = y;
	v_x = 0; v_y = 0;
	win_x = 0, win_y = 0;
	angle = 0; flip = SDL_FLIP_NONE;

	CreateWindow();
	CreateRender();
	/*if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Cannot init video,%s", SDL_GetError());
		return;
	}*/
	//玩家图像
	texture = IMG_LoadTexture(render, "resource/blue.png");
	if (texture == NULL) {
		SDL_Log("Cannot load texture,%s", SDL_GetError());
	}
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(render);
}

void Player::tick_physics(State state, float delta) {
	// 这里可以添加每个状态的物理逻辑处理
	switch (state) {
	case IDLE:
		Move(0);
		break;
	case WALK:
		Move(SPEED);
		Update();
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

void Player::Update()
{
	rect = { (int)m_x, (int)m_y, (int)m_width, (int)m_height };
	SDL_Point p{ 25,25 };
	SDL_RenderCopyEx(render, texture, NULL, &rect, angle,&p,flip);

	//窗口移动判断
	if (m_x + m_width / 2 >WINDOW_WIDTH) {
		win_x += WINDOW_WIDTH;
		m_x -= WINDOW_WIDTH;
		SDL_SetWindowPosition(win, win_x, win_y);
	}
	else if (m_x+m_width/2 < 0) {
		win_x -= WINDOW_WIDTH;
		m_x += WINDOW_WIDTH;
		SDL_SetWindowPosition(win, win_x, win_y);
	}
	if (m_y+m_height / 2 > WINDOW_HEIGHT) {
		win_y += WINDOW_HEIGHT;
		m_y -= WINDOW_HEIGHT;
		SDL_SetWindowPosition(win, win_x, win_y);
	}
	else if (m_y+ m_height/2 < 0) {
		win_y -= WINDOW_HEIGHT;
		m_y += WINDOW_HEIGHT;
		SDL_SetWindowPosition(win, win_x, win_y);
	}
}

void Player::CreateWindow()
{
	//创建窗口
	win = SDL_CreateWindow(
		"Game",
		m_x, m_y,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN
	);
	if (win == NULL) {
		SDL_Log("Cannot create window,%s", SDL_GetError());
		return;
	}
	return;
}

void Player::CreateRender()
{
	//创建渲染器
	render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (render == NULL) {
		SDL_Log("Cannot create renderer,%s", SDL_GetError());
		return;
	}
	return;
}

SDL_Window* Player::GetWindow()
{
	return win;
}

SDL_Renderer* Player::GetRender()
{
	return render;
}

void Player::Move(float speed)
{
	//加速度
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
	//移动
	float b_x = m_x, b_y = m_y;

	if (dir_y == 1) {
		flip = SDL_FLIP_VERTICAL;
	}
	else if (dir_y == -1){
		flip = SDL_FLIP_NONE;
	}

	if (dir_x && dir_y) {
		m_x += dir_x * v_x*0.707;
		m_y += dir_y * v_y*0.707;
		if (dir_x == 1) angle = -45*dir_y;
		else angle = 45*dir_y;
	}
	else if(dir_x||dir_y){
		angle = 0;
		if (dir_x == 1) { flip = SDL_FLIP_NONE; angle = 90; }
		else if (dir_x == -1) { flip = SDL_FLIP_NONE; angle = -90; }
		m_x += dir_x * v_x;
		m_y += dir_y * v_y;
	}

	//墙体碰撞
	if (m_x+win_x>2*WINDOW_WIDTH||m_x+win_x<0)m_x = b_x;
	if (m_y+win_y >2*WINDOW_HEIGHT||m_y+win_y<0)m_y = b_y;
}

void Player::SetDirectionY(float dir)
{
	dir_y = dir;
}

void Player::SetDirectionX(float dir)
{
	dir_x = dir;
}
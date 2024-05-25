#include "game.h"

void Game::Init()
{
	running = 1;

	if (SDL_Init(SDL_INIT_EVERYTHING)!=0) {
		SDL_Log("Init failed, %s", SDL_GetError());
		running = 0;
		return;
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		SDL_Log("Cannot init img,%s", SDL_GetError());
		return;
	}

	//创建玩家
	player = new Player(10, 10, 50, 50);
	player->Ready();
	win=player->GetWindow();
	render = player->GetRender();
}

void Game::Clean()
{
	delete player;
	IMG_Quit();
	SDL_Quit();
	return;
}

void Game::Events()
{
	//事件
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = 0;
			return;
		case SDLK_0:
			SDL_Log("pressed");
			running = 0;
			return;
		//键盘事件（Y：+1是向下，X：+1是向右）
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				running = 0;
				break;
			default:
				break;
			}
			//移动
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
			if (!keyboard_state_array[SDL_SCANCODE_UP]&& !keyboard_state_array[SDL_SCANCODE_DOWN]) {
				player->SetDirectionY(0);
			}
			if (!keyboard_state_array[SDL_SCANCODE_LEFT]&& !keyboard_state_array[SDL_SCANCODE_RIGHT]) {
				player->SetDirectionX(0);
			}
			break;
		}
	}
	return;
}


void Game::Loop()
{
	player->PhysicsProcess(60);
}

void Game::Render()
{
	//背景色
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderClear(render);
	//player->Render(render);
	player->Update();
	SDL_RenderPresent(render);//生效
}

bool Game::IsRunning()
{
	return running;
}

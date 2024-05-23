#pragma once
#include "resource.h"
#include "player.h"

class Game
{
public:
	void Init();
	void Events();
	void Loop();
	void Render();
	void Clean();
	bool IsRunning();
private:
	bool running;
	SDL_Window* win;
	SDL_Renderer* render;
	Player* player;
	const Uint8* keyboard_state_array;
	int x, y;
};


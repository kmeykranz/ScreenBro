#include "game.h"

int main(int, char**) {
	Game game;
	game.Init();
	while (game.IsRunning())
	{
		//控制帧率
		uint32_t begin = SDL_GetTicks();//获取开始的时间

		game.Events();
		game.Loop();
		game.Render();

		long current = SDL_GetTicks();//结束时间
		long cost = begin - current;//前面耗费的时间
		long frame = 1000 / FRAMERATE;//每帧时间
		long delay = frame - cost;//需要延迟的时间
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}
	game.Clean();
	return 0;
}
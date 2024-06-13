#include "scene_manager.h"
#include "game_scene.h"
#include "menu_scene.h"
#include "window.h"

Window *window;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;

SceneManager scene_manager;

void Init() {
	//SDL初始化
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Init failed, %s", SDL_GetError());
		return;
	}
	//SDL_IMG初始化
	if (!IMG_Init(IMG_INIT_PNG)) {
		SDL_Log("Cannot init img,%s", SDL_GetError());
		return;
	}
	//SDL_TTF 初始化
	TTF_Init();
}

void Quit() {
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

int main(int, char**) {
	Init();

	menu_scene = new MenuScene();
	game_scene = new GameScene();
	scene_manager.set_current_scene(menu_scene);

	while (scene_manager.is_running())
	{
		//控制帧率
		uint32_t begin = SDL_GetTicks();//获取开始的时间

		scene_manager.on_input();
		scene_manager.on_update();
		scene_manager.on_draw();

		long current = SDL_GetTicks();//结束时间
		long cost = begin - current;//前面耗费的时间
		long frame = 1000 / FRAMERATE;//每帧时间
		long delay = frame - cost;//需要延迟的时间
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}

	//释放
	menu_scene->on_destroy();
	game_scene->on_destroy();
	Quit();

	return 0;
}
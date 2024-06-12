#include "scene_manager.h"
#include "game_scene.h"
#include "menu_scene.h"
#include "window.h"
#include "resource.h"

Window *window;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;

SceneManager scene_manager;

int main(int, char**) {
	window = new Window();
	window->on_create();
	resource_load(window);

	menu_scene = new MenuScene(window);
	game_scene = new GameScene(window);
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
	window->on_destroy();
	resource_destroy();
	menu_scene->on_destroy();
	game_scene->on_destroy();

	return 0;
}
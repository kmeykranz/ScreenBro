#pragma once
#include "constant.h"
#include "window.h"

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() {};
	virtual void on_update() {};
	virtual void on_draw() {};
	virtual void on_input() {};
	virtual void on_exit() {};
	virtual void on_destroy() {};

	bool is_running() { return running; };
protected:
	bool running = 1;
};
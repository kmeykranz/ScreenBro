#pragma once
#include <functional>
#include "constant.h"
class Timer {
public:
	Timer() = default;
	~Timer() = default;

	//更新
	void on_update(float delta) {
		if (paused) return;

		pass_time += delta;
		if (pass_time >= wait_time) {
			if ((!one_shot || (one_shot && !shotted))&&callback) {
				callback();
			}
			shotted = true;
			pass_time = 0;
		}
	}

	//设置回调函数
	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	//开始
	void start() {
		pass_time = 0;
		shotted = false;
	}

	//设置触发间隔(s)
	void set_wait_time(float val) {
		wait_time = val;
	}

	//是否为一次性
	void set_one_shot(bool flag) {
		one_shot = true;
	}

	//暂停
	void pause() {
		paused = true;
	}

	//继续
	void resume() {
		paused = false;
	}

private:
	std::function<void()> callback;
	float pass_time=0;
	bool shotted=true;
	bool one_shot = false;
	float wait_time=0;
	bool paused = false;
};
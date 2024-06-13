#pragma once
#include "constant.h"
#include "object.h"

//碰撞检测
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}

// 处理碰撞（敌人&敌人）
void handleCollision(Object& a, Object& b) {
	//原先位置
	float ax = a.position.x, ay = a.position.y;
	float bx = b.position.x, by = b.position.y;

	// 计算分离向量
	float dx = a.position.x - b.position.x;
	float dy = a.position.y - b.position.y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance == 0.0f) {
		distance = 1.0f; // 避免除以0
	}

	float overlap = (a.size.x / 2 + b.size.x / 2) - distance;

	// 按比例分离两个敌人
	a.position.x += (dx / distance) * (overlap / 2);
	a.position.y += (dy / distance) * (overlap / 2);
	if (b.is_player!=1) {
		b.position.x -= (dx / distance) * (overlap / 2);
		b.position.y -= (dy / distance) * (overlap / 2);
	}

	//墙体碰撞

}
	
#include "object.h"

Object::Object(float x, float y, float width, float height)
    : m_x(x), m_y(y), m_width(width), m_height(height) {

}

Object::~Object() {}

void Object::Update() {
    // 更新对象逻辑
}

void Object::Render(SDL_Renderer* render) {
    // 渲染对象
 
    //绘制矩形
    rect = { (int)m_x, (int)m_y, (int)m_width, (int)m_height };
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);//混合模式
    SDL_SetRenderDrawColor(render, 255, 0, 0, 100);//透明度100
    SDL_RenderDrawRect(render, &rect);
}

void Object::Move()
{
}

bool Object::CheckCollision(const Object& other) {
    // 简单的矩形碰撞检测
    if (m_x < other.m_x + other.m_width &&
        m_x + m_width > other.m_x &&
        m_y < other.m_y + other.m_height &&
        m_y + m_height > other.m_y) {
        return true; // 发生碰撞
    }
    return false; // 未发生碰撞
}

//---------状态机----------
void Object::SetCurrentState(State state) {
    transition_state(current_state, state);
    current_state = state;
    state_time = 0.0f;
}

void Object::Ready() {
    // 你可以在这里添加初始化逻辑
    SetCurrentState(IDLE);
}

void Object::PhysicsProcess(float delta) {
    while (true) {
        State next = get_next_state(current_state);
        if (current_state == next) {
            break;
        }
        current_state = next;
        SetCurrentState(current_state);
    }
    tick_physics(current_state, delta);
    state_time += delta;
}
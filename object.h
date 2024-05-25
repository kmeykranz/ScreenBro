#pragma once
#include "resource.h"

//对象基类
class Object
{
public:
    Object(float x, float y, float width, float height);
    ~Object();

    //更新
    virtual void Update(); // 更新对象逻辑
    virtual void Render(SDL_Renderer* renderer);

    //碰撞检测
    bool CheckCollision(const Object& other);

    //状态机
    void SetCurrentState(State state);
    void Ready();
    void PhysicsProcess(float delta);

protected:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    SDL_Rect rect;

    //状态机
    State current_state;
    float state_time;
    //状态的物理逻辑
    virtual void tick_physics(State state, float delta) {}
    // 获取下一个状态的逻辑
    virtual State get_next_state(State current){return current;}
    // 状态转换逻辑
    virtual void transition_state(State current, State next){}
};


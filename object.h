#pragma once
#include "resource.h"
#include "window.h"

//对象基类
class Object
{
public:
    enum class State {
        IDLE,
        WALK,
    };

    Object() = default;
    ~Object()=default;

    bool CheckCollision(const Object& other) {
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
    void SetCurrentState(State state) {
        transition_state(current_state, state);
        current_state = state;
        state_time = 0.0f;
    }

    void PhysicsProcess(float delta) {
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

protected:
    float m_x=50;
    float m_y=50;
    float m_width=50;
    float m_height=50;

    //状态机
    State current_state=State::IDLE;
    float state_time=0;
    //状态的物理逻辑
    virtual void tick_physics(State state, float delta) { return; }
    // 获取下一个状态的逻辑
    virtual State get_next_state(State current){return current;}
    // 状态转换逻辑
    virtual void transition_state(State current, State next) { return; }
};


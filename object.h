#pragma once
#include "constant.h"
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

    //初始化
    virtual void on_create() {
    
    }

    //更新
    virtual void on_update() {
    }

    //退出
    virtual void on_exit(){
    
    }

    //释放
    virtual void on_destroy(){
        delete this;
    }

    void on_move(float speed, float delta)
    {
        //加速度
        if (speed == 0) {
            velocity = Vector2(0, 0);
        }
        else {
            if (velocity.x < speed) {
                velocity.x += ACCELERATION * delta;
            }
            if (velocity.y < speed) {
                velocity.y += ACCELERATION * delta;
            }
        }

        //面部朝向
        if (speed) {
            face_direction.x = direction.x;
            face_direction.y = direction.y;

            if (direction.x && direction.y) {
                if (direction.x > 0) {
                    angle = 90 + direction.y * 45;
                }
                else {
                    angle = -90 - direction.y * 45;
                }
            }
            else if (direction.x) {
                angle = direction.x * 90;
            }
            else if (direction.y) {
                angle = 90 + direction.y * 90;
            }
        }

        //移动计算
        if (direction.x && direction.y) {
            position.x += direction.x * velocity.x * 0.707;
            position.y += direction.y * velocity.y * 0.707;
        }
        else if (direction.x) {
            position.x += velocity.x * direction.x;
        }
        else if (direction.y) {
            position.y += velocity.y * direction.y;
        }
    }

    //设置y移动方向
    void SetDirectionY(float dir)
    {
        direction.y = dir;
    }

    //设置x移动方向
    void SetDirectionX(float dir)
    {
        direction.x = dir;
    }

    //获取面朝方向
    Vector2 get_direction() {
        return face_direction;
    }

    //获取位置
    Vector2 get_position() {
        return position;
    }

    //获取大小
    Vector2 get_size() {
        return size;
    }

    //设置状态
    void SetCurrentState(State state) {
        transition_state(current_state, state);
        current_state = state;
        state_time = 0.0f;
    }

    //状态机循环
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

    // 矩形碰撞检测
    //bool CheckCollision(const Object& other) {
    //    
    //    if (position.x < other.position.x + other.m_width &&
    //        position.x + m_width > other.position.x &&
    //        position.y < other.position.y + other.m_height &&
    //        position.y + m_height > other.position.y) {
    //        return true; // 发生碰撞
    //    }
    //    return false; // 未发生碰撞
    //}

protected:
    Vector2 size = Vector2(50, 50);				//大小
    Vector2 velocity = Vector2(0, 0);			//速度
    Vector2 position = Vector2(0, 0);			//位置
    Vector2 window_position = Vector2(0, 0);	//窗口位置
    Vector2 relevant_position = Vector2(0, 0);	//玩家相对窗口的位置
    SDL_Rect rect = {50,50};                    //图形显示矩形
    Window* window = nullptr;
    Vector2 face_direction = Vector2(0, 0);		//玩家面朝方向
    Vector2 direction = Vector2(0, 0);			//玩家移动方向
    float angle = 0;							//玩家图像面朝角度

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


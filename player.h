#pragma once
#include "resource.h"
#include "object.h"

class Player : public Object
{
public:
    Player(float x, float y, float w, float h);
    ~Player();

    SDL_Window* CreateWindow();

    void Move(float speed);
    void SetDirectionY(float dir);
    void SetDirectionX(float dir);

    //状态机
    void tick_physics(State state, float delta);
    State get_next_state(State current) override;
    void transition_state(State current, State next);

    //窗口视口
    int get_x_expand();
    int get_y_expand();
    void x_expanded();
    void y_expanded();
    void Expand();



private:
    float v_x, v_y;//速度
    float dir_x, dir_y;
    int x_expand, y_expand;
    SDL_Window *win;
};
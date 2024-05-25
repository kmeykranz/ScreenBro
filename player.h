#pragma once
#include "resource.h"
#include "object.h"

class Player : public Object
{
public:
    Player(float x, float y, float w, float h);
    ~Player();

    //窗口和渲染器
    void CreateWindow();
    void CreateRender();
    SDL_Window* GetWindow();
    SDL_Renderer* GetRender();

    //移动函数
    void Move(float speed);
    void SetDirectionY(float dir);
    void SetDirectionX(float dir);

    //状态机
    void tick_physics(State state, float delta);
    State get_next_state(State current) override;
    void transition_state(State current, State next);

    //更新逻辑
    void Update();


private:
    float v_x, v_y; //速度
    float dir_x, dir_y; //方向
    float angle; //角度
    int win_x, win_y;
    SDL_RendererFlip flip;
    SDL_Window *win;
    SDL_Renderer* render;
    SDL_Texture* texture;
};
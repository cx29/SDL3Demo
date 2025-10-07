//
// Created by 二九 on 2025/10/3.
//
// UI 渲染器（用于解耦主程序与具体实现
#pragma once // 防止文件被多次展开， 普遍的宏防护
#ifndef SDL3DEMO_IUIRENDERER_H
#define SDL3DEMO_IUIRENDERER_H

#include <SDL3/SDL.h>

class IUIState; //前向声明

class IUIRenderer {
public:
    virtual ~IUIRenderer() = default;

    //初始化渲染器， window 与 gl_context 从主程序中传入
    //返回 true 代表初始化成功
    virtual bool Init(SDL_Window *window, SDL_GLContext gl_context) = 0;

    //在每帧开始时调用， 负责为 ImGui/UI 做新帧准备
    virtual void NewFrame() = 0;

    // 渲染 ImGui draw data 或其他 UI元素
    virtual void Render() = 0;

    //处理来自 SDL 的事件
    virtual void ProcessEvent(const SDL_Event &event) = 0;

    virtual void Shutdown() = 0;

};

#endif //SDL3DEMO_IUIRENDERER_H

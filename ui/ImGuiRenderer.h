//
// Created by 二九 on 2025/10/3.
//
// - 初始化 ImGui 上下文与平台/渲染后端（SDL3+OpenGL3）
// - 在 NewFrame（）和 Render（）中桥接 ImGui 的生命周期
// - 在 ProcessEvent（）中将 SDL 事件传递给 ImGui 后端
//
// 依赖：
// - imgui core
// - imgui_impl_sdl3
// - imgui_impl_opengl3
// - opengl loader
#pragma once
#ifndef SDL3DEMO_IMGUIRENDERER_H
#define SDL3DEMO_IMGUIRENDERER_H

#include "IUIRenderer.h"
#include <string>

struct SDL_Window;

class ImGuiRenderer : public IUIRenderer {
public:
    ImGuiRenderer();

    ~ImGuiRenderer() override;

    bool Init(SDL_Window *window, SDL_GLContext gl_context) override;

    void NewFrame() override;

    void Render() override;

    void ProcessEvent(const SDL_Event &event) override;

    void Shutdown() override;


private:
    bool initialized_;
    SDL_Window* window_;
    SDL_GLContext gl_context_;
};

#endif //SDL3DEMO_IMGUIRENDERER_H

//
// Created by 二九 on 2025/10/4.
//
// 管理多个 IUIState 以及一个 IUIRenderer
// 负责每帧调度：ProcessEvent->NewFrame->Update->Render->Renderer.Render
#pragma once

#ifndef SDL3DEMO_UIMANAGER_H
#define SDL3DEMO_UIMANAGER_H

#include "IUIRenderer.h"
#include "IUIState.h"
#include <vector>
#include <memory>

class UIManager {
public:
    UIManager();

    ~UIManager();

    // 绑定一个渲染器（外部创建并传入）
    void SetRenderer(std::shared_ptr<IUIRenderer> renderer);

    //注册/注销 UI 状态（窗口）
    void AddState(std::shared_ptr<IUIState> state);

    void RemoveState(const char *name);

    //事件传递给 renderer
    void ProcessEvent(const SDL_Event &event);

    //每帧调用：新建帧， 更新状态，绘制 UI，最终调用 renderer->Render()
    void NewFrame(float delta_seconds);

    //调用渲染器的实际渲染函数
    void Render();

    //清理
    void Shutdown();

private:
    std::shared_ptr<IUIRenderer> renderer_;
    std::vector<std::shared_ptr<IUIState>> states_;
};

#endif //SDL3DEMO_UIMANAGER_H

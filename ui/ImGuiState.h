//
// Created by 二九 on 2025/10/4.
//
//
// 简单的实现实例， 托管一些演示变量
// 不直接管理渲染器， 只提供数据与 UI 绘制逻辑
// 渲染器负责 NewFame/Render 的呼叫顺序
#pragma once
#ifndef SDL3DEMO_IMGUISTATE_H
#define SDL3DEMO_IMGUISTATE_H

#include "IUIState.h"
#include <string>

class ImGuiState : public IUIState {
public:
    ImGuiState();

    ~ImGuiState() override = default;

    void RenderUI() override;

    void Update(float delta_seconds) override;

    const char *Name() const override;

    bool show_demo_;
    bool show_another_window_;
    float clear_color_[4];
    std::string title_;
};

#endif //SDL3DEMO_IMGUISTATE_H

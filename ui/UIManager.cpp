//
// Created by 二九 on 2025/10/4.
//
// 实现 UI 管理器：事件分发，帧更新与 UI 绘制序列

#include "UIManager.h"
#include <algorithm>

UIManager::UIManager() = default;


UIManager::~UIManager() {
    Shutdown();
}

void UIManager::SetRenderer(std::shared_ptr<IUIRenderer> renderer) {
    renderer_ = renderer;
}

void UIManager::AddState(std::shared_ptr<IUIState> state) {
    if (!state) return;
    states_.push_back(state);
}

void UIManager::RemoveState(const char *name) {
    if (!name) return;
    states_.erase(std::remove_if(states_.begin(), states_.end(),
                                 [&](const std::shared_ptr<IUIState> &s) {
                                     return s->Name() && std::string(s->Name()) == std::string(name);
                                 }), states_.end());
}

void UIManager::ProcessEvent(const SDL_Event &event) {
    if (renderer_) {
        renderer_->ProcessEvent(event);
    }
}

void UIManager::NewFrame(float delta_seconds) {
    if (renderer_) {
        renderer_->NewFrame();
    }
    for (auto &s: states_) {
        s->Update(delta_seconds);
        s->RenderUI();
    }
}

void UIManager::Render() {
    if (renderer_) {
        renderer_->Render();
    }
}

void UIManager::Shutdown() {
    if (renderer_) {
        renderer_->Shutdown();
        renderer_.reset();
    }
    states_.clear();
}
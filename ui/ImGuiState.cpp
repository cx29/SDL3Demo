//
// Created by 二九 on 2025/10/4.
//
#include "ImGuiState.h"
#include <imgui.h>


ImGuiState::ImGuiState() : show_demo_(true), show_another_window_(false), title_("ImGuiState Window") {
    clear_color_[0] = 0.1f;
    clear_color_[1] = 0.12f;
    clear_color_[2] = 0.14f;
    clear_color_[3] = 1.0f;
}

void ImGuiState::Update(float delta_seconds) {
    (void) delta_seconds;
    //可以更新动画，计时逻辑等
}

void ImGuiState::RenderUI() {
    //主控制面板
    ImGui::Begin("Control Panel");
    ImGui::Text("This panel is provided by ImGuiState.");
    ImGui::Checkbox("Show ImGui Demo Window", &show_demo_);
    ImGui::Checkbox("Show Another Window", &show_another_window_);
    ImGui::Text("Application:%s", title_.c_str());
    ImGui::Text("Avg %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    if (show_demo_) {
        ImGui::ShowDemoWindow(&show_demo_);
    }
    if (show_another_window_) {
        ImGui::Begin("Another Window", &show_another_window_);
        ImGui::Text("Hello from Another Window!");
        ImGui::End();
    }
}

const char *ImGuiState::Name() const {
    return "ImGuiState";
}
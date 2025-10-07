//
// Created by 二九 on 2025/10/8.
//

#include "MenuWindow.h"
#include <imgui.h>

MenuWindow::MenuWindow() : selected_index_(0), menu_items_({"Home", "Settings", "About"}) {}

void MenuWindow::Update(float delta_seconds) {
    (void) delta_seconds;
}

void MenuWindow::RenderUI() {
    // 获取当前窗口尺寸
    ImVec2 window_size = ImGui::GetIO().DisplaySize;
    // 设置下一个窗口的位置和大小；
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(window_size);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration |
                             ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoTitleBar |
                             ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("Menu Layout", nullptr, flags);

    ImGui::BeginChild("LeftPanel", ImVec2(200, 0), true);
    for (int i = 0; i < menu_items_.size(); ++i) {
        if (ImGui::Selectable(menu_items_[i].c_str(), selected_index_ == i)) {
            selected_index_ = i;
        }
    }
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("RightPanel", ImVec2(0, 0), true);
    if (selected_index_ == 0) {
        ImGui::Text("Welcome to Home Page");
    } else if (selected_index_ == 1) {
        ImGui::Text("Settings Page");
    } else if (selected_index_ == 2) {
        ImGui::Text("About Page");
        ImGui::Text("SDL3+OpenGL+ImGui Example");
    }
    ImGui::EndChild();
    ImGui::End();
}
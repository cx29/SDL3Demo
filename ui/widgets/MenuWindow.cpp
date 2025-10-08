//
// Created by 二九 on 2025/10/8.
//

#include "MenuWindow.h"
#include "Panel/HomePanel.h"
#include "Panel/SettingPanel.h"
#include "Panel/GamePanel.h"
#include <imgui.h>

MenuWindow::MenuWindow() : selected_index_(0) {
    panels_.emplace_back(std::make_unique<HomePanel>());
    panels_.emplace_back(std::make_unique<SettingPanel>());
    panels_.emplace_back(std::make_unique<GamePanel>());

    for (auto &panel: panels_) {
        menu_items_.push_back(panel->GetName());
    }
}

void MenuWindow::Update(float delta_seconds) {
    if (selected_index_ >= 0 && selected_index_ < panels_.size()) {
        panels_[selected_index_]->Update(delta_seconds);
    }
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
    if (selected_index_ >= 0 && selected_index_ < panels_.size()) {
        panels_[selected_index_]->Render();
    }
    ImGui::EndChild();
    ImGui::End();
}

const char *MenuWindow::Name() const {
    return "MenuWindow";
}

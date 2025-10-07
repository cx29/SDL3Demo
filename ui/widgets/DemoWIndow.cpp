//
// Created by 二九 on 2025/10/4.
//
#include "DemoWindow.h"
#include <imgui.h>

DemoWindow::DemoWindow() : opened_(true), title_("Demo Window"), value_(0.5f) {}

void DemoWindow::Update(float delta_seconds) {
    (void) delta_seconds;
}

void DemoWindow::RenderUI() {
    if (!opened_) return;
    ImGui::Begin(title_.c_str(), &opened_);
    ImGui::Text("This is a demo window implemented with ImGui");
    ImGui::End();
}

const char *DemoWindow::Name() const {
    return "DemoWindow";
}


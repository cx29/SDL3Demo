//
// Created by 二九 on 2025/10/8.
//

#pragma once
#ifndef SDL3DEMO_HOMEPANEL_H
#define SDL3DEMO_HOMEPANEL_H

#include "../IPanel.h"
#include <imgui.h>

class HomePanel : public IPanel {
public:

    ~HomePanel() override = default;

    void Render() override {
        ImGui::Text("This is Home Page");
        ImGui::Separator();
    }

    const char *GetName() const override {
        return "Home";
    }

    void Update(float delta_seconds) override {
        (void) delta_seconds;
    }

    void Init(int width, int height) override {

    }
};

#endif //SDL3DEMO_HOMEPANEL_H

//
// Created by 二九 on 2025/10/8.
//
#pragma once
#ifndef SDL3DEMO_SETTINGPANEL_H
#define SDL3DEMO_SETTINGPANEL_H

#include "../IPanel.h"
#include <imgui.h>

class SettingPanel : public IPanel {
public:
    void Render() override {
        ImGui::Text("Settings Page");
        static float volume = 0.5f;
        ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f);

    }

    const char *GetName() const override {
        return "Setting";

    }

    ~SettingPanel() override = default;

    void Update(float delta_seconds) override {
        (void) delta_seconds;
    }

    void Init(int width, int height) override {

    }
};

#endif //SDL3DEMO_SETTINGPANEL_H

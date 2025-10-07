//
// Created by 二九 on 2025/10/4.
//
#pragma once

#ifndef SDL3DEMO_DEMOWINDOW_H
#define SDL3DEMO_DEMOWINDOW_H

#include "../IUIState.h"
#include <string>

class DemoWindow : public IUIState {
public:
    DemoWindow();

    ~DemoWindow() override = default;

    void RenderUI() override;

    void Update(float delta_seconds) override;

    const char *Name() const override;

private:
    bool opened_;
    std::string title_;
    float value_;
};


#endif //SDL3DEMO_DEMOWINDOW_H

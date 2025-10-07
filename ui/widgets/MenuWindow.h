//
// Created by 二九 on 2025/10/8.
//

#pragma once
#ifndef SDL3DEMO_MENUWINDOW_H
#define SDL3DEMO_MENUWINDOW_H

#include "../IUIState.h"
#include <string>
#include <vector>

class MenuWindow : public IUIState {
public:
    MenuWindow();

    void Update(float delta_seconds) override;

    void RenderUI() override;

    const char *Name() const override { return "MenuWIndow"; }

private:
    int selected_index_;
    std::vector<std::string> menu_items_;
};

#endif //SDL3DEMO_MENUWINDOW_H

//
// Created by 二九 on 2025/10/4.
//
#pragma once

#ifndef SDL3DEMO_WIDGETADAPTER_H
#define SDL3DEMO_WIDGETADAPTER_H

#include "../UIManager.h"

template<class ConcreteWidget>
class WidgetAdapter : public UIManager::IWindow {
public:
    template<class... Args>
    WidgetAdapter(Args &&... args):m_widget(std::forward<Args>(args)...) {}

    void draw() override { m_widget.draw(); };
private:
    ConcreteWidget m_widget;
};

#endif //SDL3DEMO_WIDGETADAPTER_H

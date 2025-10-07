//
// Created by 二九 on 2025/10/4.
//
// UI 状态表示界面上的一个可以渲染的窗口/界面
// 目的： 允许不同窗口/面板实现统一接口以便 UI 管理器统一调用
// 通常每一帧会调用 Update（）或者 RenderUI（）来绘制 ImGui 窗口内容
#pragma once

#ifndef SDL3DEMO_IUISTATE_H
#define SDL3DEMO_IUISTATE_H

// 业务层 UI 状态抽象（例如窗口是否打开，当前选中项等）
class IUIState {
public:
    virtual ~IUIState() = default;

    // 每一帧绘制 UI（使用 ImGui Api）
    virtual void RenderUI() = 0;

    //更新逻辑
    virtual void Update(float delta_seconds) = 0;

    //返回一个标识符
    virtual const char *Name() const = 0;
};

#endif //SDL3DEMO_IUISTATE_H

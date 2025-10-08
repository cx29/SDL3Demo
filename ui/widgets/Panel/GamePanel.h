//
// Created by 二九 on 2025/10/8.
//
#pragma once

#ifndef SDL3DEMO_GAMEPANEL_H
#define SDL3DEMO_GAMEPANEL_H

#include "../../IPanel.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <chrono>

class GamePanel : public IPanel {
public:
    GamePanel();

    ~GamePanel();

    void Update(float delta_seconds) override;

    void Render() override;

    const char *GetName() const override { return "Game"; }

private:
    GLuint fbo_ = 0, color_tex_ = 0, rbo_ = 0;
    GLuint vao_ = 0, vbo_ = 0, shader_ = 0;
    int width_ = 800, height_ = 600;
    float angle_ = 0.0f;

    void InitFramebuffer();

    void InitCube();

    void InitShader();
};

#endif //SDL3DEMO_GAMEPANEL_H

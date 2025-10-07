//
// Created by 二九 on 2025/10/4.
//
#include "ImGuiRenderer.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>
#include <SDL3/SDL.h>
#include <iostream>

ImGuiRenderer::ImGuiRenderer() : initialized_(false), window_(nullptr), gl_context_(nullptr) {}

ImGuiRenderer::~ImGuiRenderer() {
    if (initialized_) {
        Shutdown();
    }
}

bool ImGuiRenderer::Init(SDL_Window *window, SDL_GLContext gl_context) {
    if (initialized_) return true;

    if (!window) {
        std::cerr << "ImGuiRenderer::Init: window is null" << std::endl;
        return false;
    }
    window_ = window;
    gl_context_ = gl_context;

    //创建 ImGui 的上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    //开启键盘事件监控
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // 主题颜色为亮
    ImGui::StyleColorsDark();

    //初始化平台/渲染器后端
    const char *glsl_version = "#version 330";
    if (!ImGui_ImplSDL3_InitForOpenGL(window, gl_context)) {
        std::cerr << "ImGui_ImplSDL3_InitForOpenGL failed" << std::endl;
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
        std::cerr << "ImGui_ImplOpenGL3_Init failed" << std::endl;
        return false;
    }
    initialized_ = true;
    return true;
}

void ImGuiRenderer::NewFrame() {
    if (!initialized_) return;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void ImGuiRenderer::Render() {
    if (!initialized_) return;
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiRenderer::ProcessEvent(const SDL_Event &event) {
    if (!initialized_) return;
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void ImGuiRenderer::Shutdown() {
    if (!initialized_)return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    initialized_ = false;
    window_ = nullptr;
    gl_context_ = nullptr;
}


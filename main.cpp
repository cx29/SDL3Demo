// 1. 初始化  SDL3负责初始化窗口 + OpenGL 上下文， glad 加载opengl 相关函数
// 2. 主循环 SDL3处理事件（鼠标键盘输入）--> ImGui预处理输入--> ImGui绘制命令生成
// 3. 渲染阶段 OpenGL 清屏-->ImGui Renderer 将绘制命令提交给 OpenGL-->SDL_GL_SwapWindow()显示结果
// 4. 退出阶段 销毁 ImGui 上下文-->销毁 OpenGL 上下文-->销毁 SDL3窗口
#include<glad/glad.h>       //GLAD 自动生成的 opengl 函数加载器头， 生命力 opengl 的函数指针类型与接口方便调用 opengl 函数
#include <iostream>
#include <SDL3/SDL.h>        // 主头文件，提供窗口，事件，openGL 上下文等跨平台功能
#include "ui/UIManager.h"       //UI 管理器
#include "ui/ImGuiState.h"
#include "ui/ImGuiRenderer.h"
#include "ui/Windows/MenuWindow.h"

// argc 参数个数， argv 每个参数的地址
int main(int argc, char *argv[]) {
    (void) argc;//标注未使用，防止编译器警告
    (void) argv;//标注未使用，防止编译器警告
    //1. 初始化 SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        std::cerr << "Failed to initialize SDL3:" << SDL_GetError() << std::endl;
        return -1;
    }

    //2. 设置 OpenGL 上下文属性（SDL3使用相同的接口，在创建窗口/上下文前进行)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);//请求 opengl 主版本，3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);//请求 opengl 次版本，3   合并之后则是 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);//使用 core profile 不兼容旧的 API
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//请求双缓冲避免闪烁（通常为 1）
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);//请求 24位深度缓冲（用于深度测试）
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);// 请求 8 位模板缓冲

    //3. 创建带 opengl 支持且可以更改窗口大小的窗口
    SDL_Window *window = SDL_CreateWindow("SDL3 Demo + OpenGL + ImGui Demo", 1280, 720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << "Failed to create SDL window:" << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    //4. 创建 OpenGL 上下文
    // 如果没有 glad 则无法调用 opengl 相关的 api
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Failed to create OpenGL context:" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    //5. 初始化 glad
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize glad." << std::endl;
        SDL_GL_DestroyContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1);// 开启垂直同步
    std::cout << "OpenGL Info:" << std::endl;
    std::cout << " Vendor:" << glGetString(GL_VENDOR) << std::endl;
    std::cout << " Renderer:" << glGetString(GL_RENDERER) << std::endl;
    std::cout << " Version:" << glGetString(GL_VERSION) << std::endl;
    //6. 创建 UI 系统
    UIManager uiManager;
    auto renderer = std::make_shared<ImGuiRenderer>();// 在堆上新建一个对象并返回一个智能指针
    if (!renderer->Init(window, glContext)) {
        std::cerr << "Failed to initialize ImGuiRenderer" << std::endl;
        SDL_GL_DestroyContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    uiManager.SetRenderer(renderer);
    auto menuWindow=std::make_shared<MenuWindow>();
    uiManager.AddState(menuWindow);

    bool running = true;
    SDL_Event event;
    auto last = std::chrono::high_resolution_clock::now();
    while (running) {
        auto now = std::chrono::high_resolution_clock::now();
        float delta_seconds = std::chrono::duration<float>(now - last).count();
        last = now;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                int w = event.window.data1;
                int h = event.window.data2;
                glViewport(0, 0, w, h);
            }
            uiManager.ProcessEvent(event);
        }
        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        uiManager.NewFrame(delta_seconds);
        uiManager.Render();
        SDL_GL_SwapWindow(window);
    }
    uiManager.Shutdown();
    renderer->Shutdown();
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

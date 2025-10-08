cmake_minimum_required(VERSION 4.0)
project(SDL3Demo)

set(CMAKE_CXX_STANDARD 20)

# 全局使用需要配置 clion 的 cmake 指令需要将 VCPKG_ROOT 的绝对路径配置进去
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
message(STATUS "VCPKG_ROOT= $ENV{VCPKG_ROOT}")

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(imgui CONFIG REQUIRED)
message(STATUS "SDL3 fount at :${SDL3_DIR}")

add_executable(SDL3Demo main.cpp
        ui/IUIRenderer.h
        ui/ImGuiRenderer.h
        ui/ImGuiRenderer.cpp
        ui/IUIState.h
        ui/ImGuiState.h
        ui/ImGuiState.cpp
        ui/widgets/DemoWindow.h
        ui/widgets/DemoWIndow.cpp
        ui/UIManager.h
        ui/UIManager.cpp
        ui/widgets/MenuWindow.h
        ui/widgets/MenuWindow.cpp
        ui/IPanel.h
        ui/widgets/Panel/HomePanel.h
        ui/widgets/Panel/SettingPanel.h
        ui/widgets/Panel/GamePanel.h
        ui/widgets/Panel/GamePanel.cpp
)

target_link_libraries(SDL3Demo PRIVATE
        SDL3::SDL3
        glad::glad
        SDL3_image::SDL3_image-static
        SDL3_ttf::SDL3_ttf-static
        OpenGL::GL
        imgui::imgui
)

//
// Created by 二九 on 2025/10/8.
//
#include "GamePanel.h"
#include <iostream>

const char *vertex_shader_src = R"(
#version 330 core
layout (location=0) in vec3 aPos;
uniform mat4 uMVP;
void main(){
    gl_Position=uMVP*vec4(aPos,1.0);
}
)";

const char *fragment_shader_src = R"(
#version 330 core
out vec4 FragColor;
void main(){
    FragColor=vec4(0.2,0.7,1.0,1.0);
}
)";

static GLuint CreateShader(GLenum type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader compile error:" << log << std::endl;
    }
    return shader;
}

GamePanel::GamePanel() {
    InitFramebuffer();
    InitCube();
    InitShader();
}

GamePanel::~GamePanel() {
    glDeleteFramebuffers(1, &fbo_);
    glDeleteTextures(1, &color_tex_);
    glDeleteRenderbuffers(1, &rbo_);
    glDeleteVertexArrays(1, &vao_);
    glDeleteProgram(shader_);
}

void GamePanel::InitFramebuffer() {
    glGenFramebuffers(1, &fbo_);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    glGenTextures(1, &color_tex_);
    glBindTexture(GL_TEXTURE_2D, color_tex_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex_, 0);
    glGenRenderbuffers(1, &rbo_);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GamePanel::InitCube() {
    float vertices[] = {
            // positions
            -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,

            0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f
    };
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glBindVertexArray(0);
}

void GamePanel::InitShader() {
    GLuint vs = CreateShader(GL_VERTEX_SHADER, vertex_shader_src);
    GLuint fs = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_src);
    shader_ = glCreateProgram();
    glAttachShader(shader_, vs);
    glAttachShader(shader_, fs);
    glLinkProgram(shader_);
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void GamePanel::Update(float delta_seconds) {
    angle_ += delta_seconds * 50.0f;//每秒旋转 50度
}

void GamePanel::Render() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    glViewport(0, 0, width_, height_);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_);
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(angle_), glm::vec3(1.0, 1.0, 0.0));
    glm::mat view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3.0));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) width_ / height_, 0.1f, 100.0f);
    glm::mat4 mvp = proj * view * model;

    GLint loc = glGetUniformLocation(shader_, "uMVP");
    glUniformMatrix4fv(loc, 1, GL_FALSE, &mvp[0][0]);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::Text("Game Scene:");
    ImGui::Image((ImTextureID) (intptr_t) color_tex_, ImVec2(width_, height_), ImVec2(0, 1), ImVec2(1, 0));
}

void GamePanel::Init(int width, int height) {

}

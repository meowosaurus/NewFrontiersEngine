//
// Created by Sonnen on 14.05.2022.
//

#include "Editor/OpenGL/Public/EditorOpenGLWidget.h"
#include "Editor/EditorFramework/Public/EditorError.h"

#include "Runtime/RendererCore/Public/Shader.h"

#include <QApplication>
#include <QKeyEvent>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

/*const char *vertexShaderSource = "#version 120\n"
                                 "attribute vec3 vertexPosition_modelspace;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(vertexPosition_modelspace, 1);\n"
                                 "}\0";*/

/*const char *fragmentShaderSource = "#version 120\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "   gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                   "}\n\0";*/


static const GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
};

static const unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
};

EngineOpenGLWidget::EngineOpenGLWidget(QWidget *parent) {}

EngineOpenGLWidget::~EngineOpenGLWidget()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgramUInt);
}

void EngineOpenGLWidget::initializeGL(void)
{
    initializeOpenGLFunctions();

    mainShader = new Shader("Engine/Shaders/SimpleVertexShader.vert",
                            "Engine/Shaders/SimpleFragmentShader.frag");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
}

void EngineOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainShader->use();

    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
}

void EngineOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}
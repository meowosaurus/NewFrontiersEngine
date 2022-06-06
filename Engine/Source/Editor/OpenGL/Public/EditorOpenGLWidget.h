//
// Created by Sonnen on 15.05.2022.
//

#ifndef NEWFRONTIERSENGINE_EDITORTESTGLWIDGET_H
#define NEWFRONTIERSENGINE_EDITORTESTGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class EditorError;
class Shader;

class EngineOpenGLWidget : public QOpenGLWidget,
                           protected QOpenGLFunctions_3_3_Core
{
public:
    EngineOpenGLWidget(QWidget *parent = 0);
    ~EngineOpenGLWidget();

protected:
    void initializeGL(void);

    void paintGL();

    void resizeGL(int w, int h);

private:
    EditorError *err;
    Shader *mainShader;

private:
    unsigned int VAO, VBO, EBO;
    unsigned int vertexShader, fragmentShader, shaderProgramUInt;
};

#endif //NEWFRONTIERSENGINE_EDITORTESTGLWIDGET_H

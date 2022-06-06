//
// Created by Sonnen on 20.05.2022.
//

#ifndef NEWFRONTIERSENGINE_SHADER_H
#define NEWFRONTIERSENGINE_SHADER_H

#include <string>
#include "Editor/General/nf_error.h"

class EditorError;
class QOpenGLFunctions_3_3_Core;

class Shader
{
public:
    /**
     * Loads and initializes a new shader. Initial directory is NewFrontiersEngine/Engine/
     * @param vertexPath const char* Path to vertex shader
     * @param fragmentPath const char* Path to fragment shader
     */
    Shader(const char* vertexPath, const char* fragmentPath);

    /**
     * Render following objects with current shader
     * @return NF_ERROR returns NF_ERROR::ok
     */
    NF_ERROR use();

    /**
     * Sets bool to name inside shader
     * @param name const std::string Name of bool in shader code
     * @param value bool Value of bool in shader code
     * @return NF_ERROR returns NF_ERROR::ok
     */
    NF_ERROR setBool(const std::string &name, bool value);
    /**
     * Sets int to name inside shader
     * @param name const std::string Name of int in shader code
     * @param value int Value of int in shader code
     * @return NF_ERROR returns NF_ERROR::ok
     */
    NF_ERROR setInt(const std::string &name, int value);
    /**
     * Sets float to name inside shader
     * @param name const std::string Name of float in shader code
     * @param value float Value of float in shader code
     * @return NF_ERROR returns NF_ERROR::ok
     */
    NF_ERROR setFloat(const std::string &name, float value);

private:
    /**
     * Checks for errors in program/shader and displays them via an EditorError window
     * @param shader unsigned int Generate OpenGL id of shader
     * @param type std::string "PROGRAM" => shader program, every else => vertex/fragment shader
     * @return NF_ERROR returns NF_ERROR::ok
     */
    NF_ERROR checkCompileErrors(unsigned int shader, std::string type);

private:
    unsigned int ID;
    unsigned int vertex, fragment;

    EditorError* err;
    QOpenGLFunctions_3_3_Core *functions;
};

#endif //NEWFRONTIERSENGINE_SHADER_H

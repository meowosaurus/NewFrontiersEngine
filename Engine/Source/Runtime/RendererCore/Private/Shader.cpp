//
// Created by Sonnen on 20.05.2022.
//

#include "Runtime/RendererCore/Public/Shader.h"
#include "Editor/EditorFramework/Public/EditorError.h"

#include <QOpenGLFunctions_3_3_Core>
#include <QApplication>

#include <fstream>
#include <sstream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    err = new EditorError();

    functions = new QOpenGLFunctions_3_3_Core();
    functions->initializeOpenGLFunctions();

    std::string vPath = qApp->applicationDirPath().toStdString() + "/../" + std::string(vertexPath);
    std::string fPath = qApp->applicationDirPath().toStdString() + "/../" + std::string(fragmentPath);

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vPath);
        fShaderFile.open(fPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        NF_ERR_CHECK(NF_ERROR::error, err, "Unable to read shader files!");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    vertex = functions->glCreateShader(GL_VERTEX_SHADER);
    functions->glShaderSource(vertex, 1, &vShaderCode, NULL);
    functions->glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = functions->glCreateShader(GL_FRAGMENT_SHADER);
    functions->glShaderSource(fragment, 1, &fShaderCode, NULL);
    functions->glCompileShader(fragment);
    checkCompileErrors(vertex, "FRAGMENT");

    ID = functions->glCreateProgram();
    functions->glAttachShader(ID, vertex);
    functions->glAttachShader(ID, fragment);
    functions->glLinkProgram(ID);
    checkCompileErrors(vertex, "PROGRAM");

    functions->glDeleteShader(vertex);
    functions->glDeleteShader(fragment);
}

NF_ERROR Shader::use()
{
    functions->glUseProgram(ID);
    return NF_ERROR::ok;
}

NF_ERROR Shader::setBool(const std::string &name, bool value)
{
    functions->glUniform1i(functions->glGetUniformLocation(ID, name.c_str()), (int)value);
    return NF_ERROR::ok;
}

NF_ERROR Shader::setInt(const std::string &name, int value)
{
    functions->glUniform1i(functions->glGetUniformLocation(ID, name.c_str()), value);
    return NF_ERROR::ok;
}

NF_ERROR Shader::setFloat(const std::string &name, float value)
{
    functions->glUniform1f(functions->glGetUniformLocation(ID, name.c_str()), value);
    return NF_ERROR::ok;
}

NF_ERROR Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        functions->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            functions->glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            NF_ERR_CHECK(NF_ERROR::error, err, infoLog);
        }
    }
    else
    {
        functions->glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            functions->glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            NF_ERR_CHECK(NF_ERROR::error, err, infoLog);
        }
    }

    return NF_ERROR::ok;
}
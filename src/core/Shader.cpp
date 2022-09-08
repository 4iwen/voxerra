#include <sstream>
#include "Shader.h"

#include "fstream"

#include "spdlog/spdlog.h"
#include "glad/glad.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // create shader program
    ID = glCreateProgram();
    spdlog::info("Created Shader with ID: {0}", ID);

    // create vertex and fragment shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // read shader codes from file
    std::string vertexCode = ReadFile(vertexPath);
    std::string fragmentCode = ReadFile(fragmentPath);

    // convert source code to const char* for OpenGL
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    //
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

    // compile shaders and check for errors
    glCompileShader(vertexShader);
    CheckForCompileErrors(vertexShader, "VERTEX");
    glCompileShader(fragmentShader);
    CheckForCompileErrors(fragmentShader, "FRAGMENT");

    // attach shaders to shader program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    // link shader program and check for errors
    glLinkProgram(ID);
    CheckForCompileErrors(ID, "PROGRAM");

    // delete shaders because we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
    spdlog::info("Deleted Shader with ID: {0}", ID);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::SetBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value)
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value)
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string &name, const glm::vec4 &value)
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &mat)
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &mat)
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::CheckForCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            spdlog::error("Shader compilation error of type: {0}\n{1}", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            spdlog::error("Shader program linking error of type: {0}\n{1}", type, infoLog);
        }
    }
}

std::string Shader::ReadFile(const char* path)
{
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    }
    catch (std::ifstream::failure e)
    {
        spdlog::error("Failed to read shader file: {0}", path);
    }
    return code;
}
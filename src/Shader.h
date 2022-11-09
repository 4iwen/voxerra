#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad/glad.h"
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"
#include "cerrno"

std::string GetFileContents(const char* pathToFile);

class Shader
{
public:
    GLuint ID;
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    void Activate() const;
    void Delete() const;
    void CheckForCompileErrors(unsigned int shader, const char* type);
};

#endif

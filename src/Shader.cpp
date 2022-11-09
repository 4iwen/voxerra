#include "Shader.h"

std::string GetFileContents(const char* pathToFile)
{
    std::ifstream in(pathToFile, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw std::runtime_error(std::string("File \"") + std::string(pathToFile) + std::string("\" was not found"));
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    std::string vertexCode = GetFileContents(vertexShaderPath);
    std::string fragmentCode = GetFileContents(fragmentShaderPath);

    // Convert the shader source strings into character arrays
    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);
    CheckForCompileErrors(vertexShader, "VERTEX");

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);
    CheckForCompileErrors(fragmentShader, "FRAGMENT");

    // Create Shader Program Object and get its reference
    ID = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(ID);
    CheckForCompileErrors(ID, "PROGRAM");

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() const
{
    glUseProgram(ID);
}

void Shader::Delete() const
{
    glDeleteProgram(ID);
}

void Shader::CheckForCompileErrors(unsigned int shader, const char* type)
{
    GLint hasCompiled;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for: " << type << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "SHADER_LINKING_ERROR for: " << type << std::endl;
        }
    }
}
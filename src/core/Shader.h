#include "string"

#include "glm/glm.hpp"

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void Use();
    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    void SetVec2(const std::string &name, const glm::vec2 &value);
    void SetVec3(const std::string &name, const glm::vec3 &value);
    void SetVec4(const std::string &name, const glm::vec4 &value);
    void SetMat2(const std::string &name, const glm::mat2 &mat);
    void SetMat3(const std::string &name, const glm::mat3 &mat);
    void SetMat4(const std::string &name, const glm::mat4 &mat);

private:
    void CheckForCompileErrors(unsigned int shader, std::string type);
    std::string ReadFile(const char* path);
};
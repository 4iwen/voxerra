#include "string"

#include "glm/glm.hpp"

class Shader
{
public:
    unsigned int id;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void use();
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setVec2(const std::string &name, const glm::vec2 &value);
    void setVec3(const std::string &name, const glm::vec3 &value);
    void setVec4(const std::string &name, const glm::vec4 &value);
    void setMat2(const std::string &name, const glm::mat2 &mat);
    void setMat3(const std::string &name, const glm::mat3 &mat);
    void setMat4(const std::string &name, const glm::mat4 &mat);

private:
    void checkForCompileErrors(unsigned int shader, std::string type);
    std::string readFile(const char* path);
};
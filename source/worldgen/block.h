#include "../utils/enums.h"
#include "glm/vec3.hpp"


class block {
public:
    block();

    void setType(blockType type);
    blockType type;

    int blue();
    int red();
    int green();
private:
    glm::vec3 rgb;
};

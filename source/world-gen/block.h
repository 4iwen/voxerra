#include "../utils/enums.h"


class block {
public:
    block();

    void setType(blockType type);
    blockType type;

    int blue();
    int red();
    int green();
private:
    int r;
    int g;
    int b;
};

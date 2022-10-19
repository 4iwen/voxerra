#include "block.h"

void block::setType(blockType type) {
    this->type = type;

    switch(type)
    {
        case(blockType::DIRT):
            rgb.x = 50;
            rgb.y = 100;
            rgb.z = 0;
            break;
        case(blockType::GRASS):
            rgb.x = 0;
            rgb.y = 200;
            rgb.z = 0;
            break;
        case(blockType::STONE):
            rgb.x = 100;
            rgb.y = 100;
            rgb.z = 100;
            break;
    }
}

int block::red() {
    return rgb.x;
}

int block::blue() {
    return rgb.y;
}

int block::green() {
    return rgb.z;
}

block::block() {

}

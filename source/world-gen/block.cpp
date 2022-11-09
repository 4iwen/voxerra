#include "block.h"

void block::setType(blockType type) {
    this->type = type;

    switch(type)
    {
        case(blockType::DIRT):
            r = 50;
            g = 100;
            b = 0;
            break;
        case(blockType::GRASS):
            r = 0;
            g = 200;
            b = 0;
            break;
        case(blockType::STONE):
            r = 100;
            g = 100;
            b = 100;
            break;
    }
}

int block::red() {
    return r;
}

int block::blue() {
    return g;
}

int block::green() {
    return b;
}

block::block() {

}

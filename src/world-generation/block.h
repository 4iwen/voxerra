//
// Created by Liquid on 10/15/2022.
//

#ifndef VOXERRA_BLOCK_H
#define VOXERRA_BLOCK_H
#include "../utils/enums.h"

class block {
public:
    block(blockType type);

    blockType type;
    int r;
    int g;
    int b;
};


#endif //VOXERRA_BLOCK_H

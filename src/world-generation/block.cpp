//
// Created by Liquid on 10/15/2022.
//

#include "block.h"

block::block(blockType type) {
    this->type = type;
    switch (this->type) {
        case dirt:
            this->r = 100;
            this->g = 50;
            this->b = 0;
            break;
        case grass:
            this->r = 0;
            this->g = 100;
            this->b = 0;
            break;
        case stone:
            this->r = 100;
            this->g = 100;
            this->b = 100;
            break;
        case bedrock:
            this->r = 0;
            this->g = 0;
            this->b = 100;
            break;
    }
}
#pragma once

enum BlockType
{
    AIR = 0,
    GRASS,
    DIRT,
    STONE,
    SAND,
    WATER
};

struct BlockColor
{
    float r, g, b;
};
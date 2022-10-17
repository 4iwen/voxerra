//
// Created by 42077 on 10/17/2022.
//

#include "heightGenerator.h"

int heightGenerator::getHeight(int x, int y, biome biome, FastNoiseLite noiseOne, FastNoiseLite noiseTwo) {
    this->noiseOne = noiseOne;
    this->noiseTwo = noiseTwo;
    this->x = x;
    this->y = y;

    switch (biome) {
        case flats:
            height = heightMaths();
            break;
        case desert:
            height = heightMaths();
            break;
    }
    return height;
}
int heightGenerator::heightMaths()
{
    float tempOne = noiseOne.GetNoise((float)x,(float)y) * 10;
    float tempTwo = noiseTwo.GetNoise((float)x, (float)y) * 12;
    float tempThree = abs((tempOne + tempTwo)/2);
    return (int)tempThree;
}
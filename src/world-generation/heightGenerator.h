#include "FastNoiseLite.h"
#include "../utils/enums.h"
#include <math.h>

class heightGenerator {
public:
    int getHeight(int x, int y, biome biome,FastNoiseLite noiseOne,FastNoiseLite noiseTwo);
private:
    int heightMaths();
    int height;
    FastNoiseLite noiseOne;
    FastNoiseLite noiseTwo;
    int x;
    int y;
};


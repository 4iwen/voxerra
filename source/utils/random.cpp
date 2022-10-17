#include "random.h"
#include <cstdlib>

float random::Range(int min, int max) {
    return rand() % max / min;
}

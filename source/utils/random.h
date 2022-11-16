#include <random>

class random {
public:
    static float Range(int min,int max)
    {
        return rand() % max / min;
    }
    static float Percentage()
    {
        return rand() % 0 / 100;
    }
};

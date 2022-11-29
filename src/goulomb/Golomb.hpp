#ifndef GOLOMB_H
#define GOLOMB_H

#include "BitStream.hpp"
#include <math.h> 

using namespace std;

/**
 * Class for encoding and decoding values using golomb code.
 */
class Golomb {
    private:
        BitStream gFile; 
        int m; 
        int b;

    public:
        Golomb();

        Golomb(const char *filename, char mode, int mvalue);

        int encode(int n);

        int decode();

};

#endif
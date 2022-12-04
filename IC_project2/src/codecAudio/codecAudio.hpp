#ifndef CODECAUD_H
#define CODECAUD_H

#include <stdio.h>
#include <sndfile.h>
#include <vector>

/**
 * Class for encoding and decoding audio files.
 */

class Codecaud{
    private:
        char* filename;
        SF_INFO sfinfo;
        int ninput;
        std::vector<short> chs = {};
        std::vector<short> rn = {};
        
    public:
        Codecaud();

        Codecaud(const char *filename);
              
};

#endif
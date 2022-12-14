#ifndef CODECAUD_H
#define CODECAUD_H

#include <stdio.h>
#include <sndfile.h>
#include <vector>

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

        void compress(const char *fileDst, int num, bool lossy, int shamt);

        void predictor(std::vector<short> vetSrc);

        void decompress(const char *fileSrc);
              
};

#endif
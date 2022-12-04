#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <map>

using namespace std;

class BitStream {
    private:
        fstream file;
        int mode; 
        unsigned char buffer;  
        int pointer; 
        int size; 

    public:
  
        BitStream();

        BitStream(const char *filename, char mode);

        unsigned char readBit();

        void writeBit(char bit);

        void readNBits(char* bits, int n);

        void writeNBits(char* bits, int n);

        bool endOfFile();

        void close();
};

#endif

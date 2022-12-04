#ifndef GOLOMB_H
#define GOLOMB_H

#include "../bitstream/BitStream.cpp"
#include <math.h> 

using namespace std;

class Golomb {
    public:
        Golomb();

        Golomb(const char *filename, char mode, int mvalue);

        int encode(int n);

        int decode();

        int fold(int n);

        int unfold(int n);

        void encodeM(int n);

        int decodeM();

        void SoundHeaderEncode(int nFrames, int sampleRate, int Channels, int format, bool lossy);

        void SoundHeaderDecode(int arr[]);

        void encondeShamt(int shamt);

        int decodeShamt();

        void setM(int mi);

        void close();

    private:
        BitStream gFile; 
        int m; 
        int b;
};

#endif

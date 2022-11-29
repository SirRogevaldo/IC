#include "Golomb.hpp"
#include "BitStream.hpp"
#include <math.h>
#include <cstdlib>

using namespace std;

Golomb::Golomb(){}

Golomb::Golomb(const char *filename, char mode, int mvalue){
    if (mode != 'e' && mode != 'd' && mode != 'E' && mode != 'D'){
        cout << "ERROR: invalid mode!" << endl;
        exit(1);
    }
    if (mode == 'd' || mode == 'D')
        gFile = BitStream(filename, 'r');
    else
        gFile = BitStream(filename, 'w');
    m = mvalue;
    b =  ceil(log2(m));
}

int Golomb::encode(int n){
    
    int q = floor((int)(n / m));
    int r = n - q*m;

    // number of bits for the binary code part
    int binBits;
    // value to be coded in the binary code part
    int binValue;

    // m == 2^x ?
    if (m!=0 && (m & (m-1)) == 0){
        binValue = r;
        binBits  = b;
    }
    else{
        // Encode the first 2b − m values of r using the first 2^b − m binary codewords of b − 1 bits.
        if(r < pow(2, b) - m){
            binValue = r;
            binBits  = b-1;
        }
        // Encode the remainder values of r by coding the number r + 2^b − m in binary codewords of b bits.
        else{
            binValue = r + pow(2, b) - m;
            binBits  = b;
        }
    }
    
    // unary code part
    int tmp = q;
    while(tmp != 0){
        gFile.writeBit('1');
        tmp--;
    }
    gFile.writeBit('0');

    // binary code part
    string tmp2 = "";   
    while(binBits =! 0){
        if(binValue % 2 == 0){
            tmp2 += '0';
        }else{
            tmp2 += '1';
        }
        binValue /= 2;
        binBits--;
    }

    for(int i = binBits-1; i >= 0; i-- )
        gFile.writeBit(tmp2[i]);

    return 0; //?
}

int Golomb::decode(){

    int q = 0;

    // unary counter (AKA number of 1s before 0)
    char c;
    while(true){
        c = gFile.readBit();
        if((c & 0x01) == 0x00)
            break;
        q++;
    }

}
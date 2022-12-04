#include "Golomb.hpp"
#include "../bitstream/BitStream.hpp"
#include <math.h>
#include <cstdlib>

using namespace std;

//Auxiliary function to convert char array from bin to int
int convertToInt(char arr[], int size){
    int x=0;
    for(int i=0;i<size;i++){
        if(arr[i] != 0x00){
            x=pow(2, i);
        }
    }
    return x;

}
// convert int to string in binary with binBits bits
string convertToBin(int value, int binBits){
    string aux = "";
    while (value != 0){
        aux += ( value % 2 == 0 ? '0' : '1' );
        value /= 2;
        binBits --;
    }
    while(binBits != 0){
        aux+= '0';
        binBits--;
    }
    return aux;
}

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

    if (n >= 0)
        n = n*2;
    else
        n = abs(n)*2-1;
    
    int q = floor((int)(n / m));
    int r = n - q*m;
    int size = 0;

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
        size++;
        tmp--;
    }
    gFile.writeBit('0');
    size++;

    // binary code part
    string tmp2 = "";   
    int binBitsTmp = binBits;
    while(binValue != 0){
        if(binValue % 2 == 0){
            tmp2 += '0';
        }else{
            tmp2 += '1';
        }
        binValue /= 2;
        binBitsTmp--;
    }
    while(binBitsTmp != 0){
        tmp2+= '0';
        binBitsTmp--;
    }

    size += binBits;

    for(int i = binBits-1; i >= 0; i-- )
        gFile.writeBit(tmp2[i]);
    return size;
}

int Golomb::decode(){
    int q = 0;
    int r = 0;
    // int size = 0;

    char c;
    //Count number of 1s before the first zero (q)
    while(true){
        c = gFile.readBit();
        if((c & 0x01) == 0x00)
            break;
        q++;
    }

    // m == 2^x ?
    if (m!=0 && (m & (m-1)) == 0){

        char binary[b];
        gFile.readNBits(binary,b);
    
        int aux = 0;
        for( int i = b-1; i >= 0; i--){
            if(binary[i] != 0x0)
                r+= pow(2, aux);
            aux++;
        }
        return unfold(m*q + r);
    }
    // if m == 2^x
    else{
        int tmp = 0;
        char binary[b];
        gFile.readNBits(binary,b-1);
        binary[b-1] = 0;

        for (int i = b-2; i >= 0; i--){
            if(binary[i] != 0x00)
                r+= pow(2, tmp);
            tmp++;
        } 
 
        if(r < pow(2, b) - m){
            return unfold(m*q + r);
        }
        else{
            binary[b-1] = gFile.readBit();
            r=0, tmp=0;
            for (int i = b-1; i >= 0; i--){
                if(binary[i] != 0x0)
                    r+= pow(2, tmp);
                tmp++;
            }
            return unfold(m*q + r - (pow(2, b) - m)); 
        }
    }
    return 0;
}

void Golomb::SoundHeaderEncode(int nFrames, int sampleRate, int Channels, int format, bool isLossy){
    /* Header Compsition:
     * Golomb m          -> 32 bits
     * 
     * isLossy           ->  1 bit
     * Num of samples    -> 32 bits
     * Sample Rate       -> 32 bits
     * Format            -> 32 bits
     * Channels          ->  4 bits
     *                     --------
     *                     101 bits
     */ 
    string header;
    if(isLossy)
        header = '1';
    else
        header = '0';

    header += convertToBin(nFrames, 32);
    header += convertToBin(sampleRate, 32);
    header += convertToBin(format,32);
    header += convertToBin(Channels, 4);

    char tmpHeader[101];
    for(int i=0; i < 101; i++)
        tmpHeader[i] = header[i];
    gFile.writeNBits(tmpHeader, 101);
}

void Golomb::SoundHeaderDecode(int header[]){
    /*
     *header[0] isLossy       -> 1 bit
     *header[1]Num of samples -> 32 bits
     *header[2]Sample Rate    -> 32 bits
     *header[3] Format        -> 32 bits
     *header[4]Channels       ->  4 bits
     */
    char option = gFile.readBit();
    header[0] = int(option&0x1);    
    char tmp[32];
    gFile.readNBits(tmp, 32);
    header[1] = convertToInt(tmp,32);
    gFile.readNBits(tmp, 32);
    header[2] = convertToInt(tmp,32);
    gFile.readNBits(tmp, 32);
    header[3] = convertToInt(tmp,32);
    char tmp2[4];
    gFile.readNBits(tmp2, 4);
    header[4] = convertToInt(tmp2,4);
}

void Golomb::encodeM(int m){
    string s = convertToBin(m, 32);
    char space[32];

    for(int i = 0; i < 32; i++){
        space[i] = s[i];
    }

    gFile.writeNBits(space, 32);
}

int Golomb::decodeM(){
    char space[32];
    gFile.readNBits(space, 32);
    return convertToInt(space, 32);
}

void Golomb::encondeShamt(int shamt){
    string sh = convertToBin(shamt, 5);
    char hdr[5];
    for(int i=0; i < 5; i++)
        hdr[i] = sh[i];
    gFile.readNBits(hdr, 5);
}

int Golomb::decodeShamt(){
    char shamt[5];
    gFile.readNBits(shamt, 5);
    return convertToInt(shamt,5);
}

int Golomb::fold(int n){
    if (n >= 0)
        return n = n*2;
    else
        return n = abs(n)*2-1;
}

int Golomb::unfold(int n){
    if (n % 2 == 0)
        return n/2;
    else
        return (-1)*ceil(n/2)-1;
}

void Golomb::setM(int mi){
    this->m = mi;
    b =  ceil(log2(m));
}

void Golomb::close(){
    gFile.close();
}
#include "Golomb.hpp"
#include "../bitstream/BitStream.hpp"
#include <math.h>
#include <cstdlib>

using namespace std;

//Auxiliary function to convert char array from bin to int
int convertToInt(char arr[], int size){
    int res=0;
    for(int i=0;i<size;i++){
        if(arr[i] != 0x00){
            res+=pow(2, i);
        }
    }
    return res;

}
//Auxiliary function to convert int value to string in binary with numBits bits
string convertToBin(int value, int numBits){
    string aux = "";
    while (value != 0){
        aux += ( value % 2 == 0 ? '0' : '1' );
        value /= 2;
        numBits --;
    }
    while(numBits != 0){
        aux+= '0';
        numBits--;
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
        gFile.readNbits(binary,b);
    
        //Get b+1 Lsbits of the origingal value to be decoded (R = (0)+b Lsbit in decimal)
        int aux = 0;
        for( int i = b-1; i >= 0; i--){
            if(binary[i] != 0x0)
                r+= pow(2, aux);
            aux++;
        }
        //Calculate decoded value
        return unfold(m*q + r);
    }
    //If m is not power of two
    else{
        int tmp = 0;
        char binary[b];
        gFile.readNbits(binary,b-1);
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

void Golomb::encodeM(int m){
    string s = convertToBin(m, 32);
    char space[32];

    for(int i = 0; i < 32; i++){
        space[i] = s[i];
    }

    gFile.writeNbits(space, 32);
}

int Golomb::decodeM(){
    char space[32];
    gFile.readNbits(space, 32);
    return convertToInt(space, 32);
}

int Golomb::unfold(int n){
    if (n % 2 == 0)
        return n/2;
    else
        return (-1)*ceil(n/2)-1;
}

void Golomb::close(){
    gFile.close();
}
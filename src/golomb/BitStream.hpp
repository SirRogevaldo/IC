#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <iostream>
#include <fstream>

using namespace std;

class BitStream {
    private:
        fstream file;
        int mode;
        unsigned char buffer;
        int pointer;
        int size;   // file size in bytes

    public:

    BitStream();

    BitStream(const char *filename, char fileMode){
    
        if(fileMode == 'r' || fileMode == 'R'){  
            file = fstream(filename, ios::binary | ios::in);
            pointer = 0;
            mode = 0;
            file.seekg(0, ios::end);
            size = file.tellg();
            file.seekg(0, ios::beg);
        }else if(fileMode == 'w' || fileMode == 'W'){ 
            file = fstream(filename, ios::binary | ios::out);
            pointer = 8;
            mode = 1;
        }else{
            throw runtime_error("File mode invalid");
        }
        if(!file.is_open()){throw runtime_error("Could not open file");}
        buffer = 0x00;
    }

    unsigned char readBit(){
        if(mode == 1) throw runtime_error("Read disabled for Write mode");
        if(pointer == 0){
            pointer = 8;
            file.read(reinterpret_cast<char*>(&buffer), sizeof(char));
        }
        pointer--;
        return (buffer >> pointer) & 0x01;
    }

    void writeBit(char c){
        if(mode == 0) throw runtime_error("Write disabled for Read mode");
        if(pointer == 1){
            buffer |= (c & 0x01);
            file.write(reinterpret_cast<char*>(&buffer), 1);
            buffer = 0;
            pointer = 8;
            return;
        }
        pointer--;
        buffer |= ((c & 0x01) << pointer);
    }

    void readNBits(char* c, int n){
        
        for (int i = 0; i < n; i++) {
            c[i] = readBit();
        }
    }

    void writeNBits(char* c, int n){

        int j;
        if(n % 8 != 0){
            j = 8 - (n % 8);
        }

        for (int i = 0; i < n; i++) {
            writeBit(c[i]);
        }

        for (int i = n; i < n+j; i++) { // padding in case n % 8 != 0
            writeBit('0');
        }

    }

    // not sure if 100% correct
    bool endOfFile(){
        if(mode == 1) throw runtime_error("EndOfFile disabled in Write mode");
        if(file.tellg() < size) return false;
        if(pointer > 0) return false;
        return true;
    }

    // So you close file whenever
    void close(){
        file.close();
    }
};

#endif
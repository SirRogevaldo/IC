#include "codecAudio.hpp"
#include "Golomb.cpp"

#include <iostream>
#include <stdio.h>
#include <sndfile.h>
#include <math.h>
#include <vector>
#include <map>
#include <sndfile.h>

using namespace std;

Codecaud::Codecaud(){}

Codecaud::Codecaud(const char *filename){

    SNDFILE *infile;
    int readcount;
    short ch[2];

	if (! (infile = sf_open (filename, SFM_READ, &sfinfo))) {
        cout << "File doesn't exist" << endl;
        exit(EXIT_FAILURE);
	}
    
    while ((readcount = (int) sf_readf_short (infile, ch, 1)) > 0) {
        chs.push_back(ch[0]);
        chs.push_back(ch[1]);
    }
    
	sf_close (infile) ;  
}

void Codecaud::compress(const char *fileDst, int num, bool lossy, int shamt) {

    ninput = num;

    /*if(lossy)
        preditorLossy(chs, shamt);
    else
        preditor(chs);*/

    // Golomb
    Golomb g(fileDst, 'e', 0);

    double m = 0;
    for(int i = 0; i < (int)rn.size(); i++) {
        m += g.fold(rn[i]);
    }
    m = m/rn.size();

    m = (int) ceil(-1/(log2(m/(m+1))));

    g.setM(m);
    g.encodeM(m);
    g.SoundHeaderEncode(sfinfo.frames, sfinfo.samplerate, sfinfo.channels, sfinfo.format, lossy);
    /*if(lossy)
        g.encondeShamt(shamt);
    */

    for(int i = 0; i < (int)rn.size(); i++) {
        g.encode(rn[i]);
    } 
    g.close();
}

void Codecaud:: predictor(vector<short> vectorSrc) {
    vector<short> left;
    vector<short> right;
    for(int i = 0; i < chs.size()-1; i+=2){
        left.push_back(chs[i]);
        right.push_back(chs[i+1]);
    }

    vector<short> xnl, xnr;

    if(ninput == 1) {
        for(int i = 0; i < left.size(); i++) {
            if(i == 0) {
                xnl.push_back(0);
                xnr.push_back(0);
            }
            else {
                xnl.push_back(left[i-1]);
                xnr.push_back(right[i-1]);
            }
            rn.push_back(left[i]-xnl[i]);
            rn.push_back(right[i]-xnr[i]);
        }
    }
    else if(ninput == 2) {
        for(int i = 0; i < left.size(); i++) {
            if(i == 0 || i == 1) {
                xnl.push_back(0);
                xnr.push_back(0);
            }
            else {
                xnl.push_back(2*left[i-1] - left[i-2]);
                xnr.push_back(2*right[i-1] - right[i-2]);
            }
            rn.push_back(left[i]-xnl[i]);
            rn.push_back(right[i]-xnr[i]);
        }
    }
    else {
        for(int i = 0; i < left.size(); i++) {
            if(i == 0 || i == 1 || i == 2) {
                xnl.push_back(0);
                xnr.push_back(0);
            }
            else {
                xnl.push_back(3*left[i-1] - 3*left[i-2] + left[i-3]);
                xnr.push_back(3*right[i-1] - 3*right[i-2] + right[i-3]);
            }
            rn.push_back(left[i]-xnl[i]);
            rn.push_back(right[i]-xnr[i]);
        }
    }
}

void Codecaud::decompress(const char *fileSrc) {

    cout << " Decompressing " << endl;

    Golomb g(fileSrc, 'd', 0);
    int m = g.decodeM();

    g.setM(m);

    int decoderData[5]; 
    g.SoundHeaderDecode(decoderData);

    vector<short> resChs;
    vector<short> resl, resr;
    vector<short> resXl, resXr;

    for(int i = 0; i < decoderData[1]*decoderData[4]; i++)
        resChs.push_back(g.decode()) ;

    for(int i = 0; i < resChs.size()-1; i+=2){
        resl.push_back(resChs[i]);
        resr.push_back(resChs[i+1]);
    }

    g.close();

    vector<short> resXN;
    vector<short> resHatXl, resHatXr; 
    
    if(ninput == 1) {
        resXl.push_back(resl[0]);
        resXr.push_back(resr[0]);
        resXN.push_back(resl[0]);
        resXN.push_back(resr[0]);
        for(int i = 1; i < resl.size(); i++) {
            resXl.push_back((short) resl[i] + resXl[i-1]);
            resXr.push_back((short) resr[i] + resXr[i-1]);
            resXN.push_back(resXl[i]);
            resXN.push_back(resXr[i]);
        }
    }
    else if(ninput == 2) {
        for(int i = 0; i < 2; i++) {
            resHatXl.push_back(0);
            resHatXr.push_back(0);
            resXl.push_back(resl[i]);
            resXr.push_back(resr[i]);
            resXN.push_back(resXl[i]);
            resXN.push_back(resXr[i]);
        }
        for(int i = 2; i < resl.size(); i++) {
            resHatXl.push_back((int) (2*resXl[i-1] - resXl[i-2]));
            resHatXr.push_back((int) (2*resXr[i-1] - resXr[i-2]));
            resXl.push_back((short) resl[i] + resHatXl[i]);
            resXr.push_back((short) resr[i] + resHatXr[i]);
            resXN.push_back(resXl[i]);
            resXN.push_back(resXr[i]);
        }
    }
    else {
        for(int i = 0; i < 3; i++) {
            resHatXl.push_back(0);
            resHatXr.push_back(0);
            resXl.push_back(resl[i]);
            resXr.push_back(resr[i]);
            resXN.push_back(resXl[i]);
            resXN.push_back(resXr[i]);
        }
        for(int i = 3; i < resl.size(); i++) {
            resHatXl.push_back((int) (3*resXl[i-1] - 3*resXl[i-2] + resXl[i-3]));
            resHatXr.push_back((int) (3*resXr[i-1] - 3*resXr[i-2] + resXr[i-3]));
            resXl.push_back((short) resl[i] + resHatXl[i]);
            resXr.push_back((short) resr[i] + resHatXr[i]);
            resXN.push_back(resXl[i]);
            resXN.push_back(resXr[i]);
        }
    }

    SF_INFO sfinfoOut ;
    sfinfoOut.channels = decoderData[4];
    sfinfoOut.samplerate = decoderData[2];
    sfinfoOut.format = decoderData[3];
    sfinfoOut.frames = decoderData[1];

    SNDFILE * outfile = sf_open("out.wav", SFM_WRITE, &sfinfoOut);
    sf_count_t count = sf_write_short(outfile, &resXN[0], resXN.size()) ;
    sf_write_sync(outfile);
    sf_close(outfile);
}

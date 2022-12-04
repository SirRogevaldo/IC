#include "codecAudio.hpp"
#include "Golomb.cpp"

#include <iostream>
#include <stdio.h>
#include <sndfile.h>
#include <math.h>
#include <vector>
#include <map>

using namespace std;
namespace plt = matplotlibcpp;

Codecaud::Codecaud(){}

Codecaud::Codecaud(const char *filename){

    SNDFILE *infile;
    int readcount;
    short ch[2];

	if (! (infile = sf_open (filename, SFM_READ, &sfinfo))) {
        cout << "File doesn't exists" << endl;
        exit(EXIT_FAILURE);
	}
    
    while ((readcount = (int) sf_readf_short (infile, ch, 1)) > 0) {
        chs.push_back(ch[0]);
        chs.push_back(ch[1]);
    }
    
	sf_close (infile) ;  
}




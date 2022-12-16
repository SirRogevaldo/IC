#include "fcm.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

void readChar(ifstream &inFile, char *c){
    char s;
    do{
        inFile.get(s);
        if(!(s == '\n'| s == '\t')) {
            *c = s;
        }
    }while((*c == '\n'|*c == '\t') && !inFile.eof());
}

fcm::fcm(int k, double alpha){
    this->k = k;
    this->alpha = alpha;
}

void fcm::estimate(map<string, map<char, int>> &model, char *filename){

    ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open()){
        throw runtime_error("Error: Could not open file");
    }
    
    
}

void fcm::loadModel(map<string, map<char, int>> &model, char *filename){

    ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open()){
        throw runtime_error("Error: Could not open file");
    }

    // small string (k length) where the next char ocurences (aux) will be counted
    string context;
    char aux;

    // init context
    for (int i = 0; i < k; i++){
        readChar(inFile, &aux);
        context.append(1, aux);
    }

    do{
        readChar(inFile, &aux);

        if(model.count(context) > 0){
            model[context][aux]++;

        }else{
            map <char, int> newC;
            model[context] = newC;
            model[context][aux]++;
        }

        // set to next context
        context.erase(0, 1);
        context.append(1, aux);

    }while(!inFile.eof());

    inFile.close();

    ofstream outFile(filename, std::ios::out);
    outFile.open("testfile.txt");
    outFile << k << "\t" << alpha << endl;
    for(auto m: model){
        outFile << m.first;
        for (auto i: m.second){
            outFile << "\t" << i.first << " " << i.second;
        }
        outFile << "\n";
    }

    outFile.close();
}

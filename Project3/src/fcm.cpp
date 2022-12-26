#include "fcm.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

#define ALPHABET_SIZE 26

using namespace std;

fcm::fcm(){}

fcm::fcm(int k, double alpha){
    this->k = k;
    this->alpha = alpha;
}

void readChar(ifstream &inFile, char *c){
    char s;
    do{
        inFile.get(s);
        if(!(s == '\n'| s == '\t')) {
            *c = s;
        }
    }while((*c == '\n'|*c == '\t') && !inFile.eof());
}

void fcm::estimate(map<string, map<char, int>> &model, char *filename){
    
    ifstream inFile(filename, std::ios::in);
    if(!inFile.is_open()){
        throw runtime_error("Error: Could not open file");
    }

    // small string (k length) where the next char occurrences (aux) will be counted
    string context;
    char aux;

    // init context
    for (int i = 0; i < k; i++){
        readChar(inFile, &aux);
        context.append(1, aux);
    }

    int occNumber = 0, occTotal = 0, count = 0;
    double d = 0;

    do{
        readChar(inFile, &aux);

        if(model.count(context) > 0){
            map<char, int> occ = model[context];
            if(occ[aux] > 0){
                occNumber = occ[aux];
            }else{
                occNumber = 0;
            }
            for(auto i : occ){
                occTotal += i.second;
            }

        }else{
            occNumber = 0;
            occTotal = 0;
        }

        count++;

        d += -log2((occNumber + alpha) / (occTotal + (alpha * ALPHABET_SIZE)));

        // set to next context
        context.erase(0, 1);
        context.append(1, aux);

    }while(!inFile.eof());


    distance = d;
    estimatedEntropy = d / count;
    nLetters = count;

    cout << "distance: " << distance << " estimated entropy: " << estimatedEntropy <<" nLetters: " << nLetters << endl; 
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

    string outFileName = string(filename).substr(0, string(filename).length() - 4); // tirar ".txt"
    outFileName = outFileName + to_string(k) + "kModel.txt";

    ofstream outFile;
    outFile.open(outFileName);
    outFile << k << "\t" << alpha << endl;
    for(auto m: model){
        outFile << m.first;
        map<char,int> &occ = model[m.first];
        for (auto i: occ){
            outFile << "\t" << i.first << " " << i.second;
        }
        outFile << "\n";
    }


    outFile.close();
}

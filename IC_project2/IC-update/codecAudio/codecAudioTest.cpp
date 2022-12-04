// g++ test_codecaud.cpp -o test_codecaud -lsndfile -I/usr/include/python3.8 -lpython3.8
#include "codecAudio.cpp"
#include <ctime>

int main(int argc, char* argv[]){

    //Command line arguments processing
    if(argc != 2){
        cout << "\033[1;31mError: Following argument is required <input filename>\033[0m" << endl;
        return 0; 
    }
    char *inputfile = argv[1];

    Codecaud c(inputfile);

    int op1 = -1;
    while(!(op1 == 0 || op1 == 1)) {
        cout << "Choose codec option isLossy: ";
        cin >> op1;
    }
    int op2 = 0;
    while(op2 < 1 || op2 > 3) {
        cout << "Choose the predictor (1, 2 or 3): ";
        cin >> op2;
    }
    
    clock_t begin = clock();
    c.compress("compress.bin", op2, op1, 0);
    clock_t end = clock();
    cout <<"Duration: " <<  (double(end - begin) / CLOCKS_PER_SEC) << endl;
    printf("... done encoding\n\n");

    c.decompress("compress.bin");
    printf("... done decompress\n\n");

    return 0;
}
#include "../src/fcm.cpp"

int main(int argc, char** argv){

    map<string, map<char, int>> model;
    
    // argv[argc-1] is the text, all else are models
    if(argc < 2){
        cout << "Error: Syntax: <Model> * numberOfModels <Text> " << endl;
        return 0; 
    }

    fcm f(3, 0.1);
    f.loadModel(model, argv[1]);

    f.estimate(model,argv[2]);
    model.clear();

}
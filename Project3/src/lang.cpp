#include "../src/fcm.cpp"

int main(int argc, char** argv){

    map<string, map<char, int>> model;
    
    if(argc != 3){
        cout << "Error: Syntax: <Model> <Text> " << endl;
        return 0; 
    }

    fcm f(3, 0.1);
    f.loadModel(model, argv[1]);

    f.estimate(model,argv[2]);
    model.clear();

}
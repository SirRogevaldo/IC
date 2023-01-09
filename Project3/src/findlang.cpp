#include "../src/fcm.cpp"

int main(int argc, char** argv){

    map<string, map<char, int>> model;
    string modelL;
    int minD = 0;
    
    // argv[argc-1] is the text, all else are models
    if(argc < 2){
        cout << "Error: Syntax: <Model> * numberOfModels <Text> " << endl;
        return 0; 
    }

    fcm f(3, 0.1);

    for(int i = 1; i < argc - 1; i++){

        f.loadAvailableModel(model, argv[i]); // load model from file
        f.estimate(model, argv[argc-1]); // argv[argc-1] is the text, all else are models

        if(i == 1) {    // model language is the first model can't compare to any other
            modelL = argv[i]; 
            minD = f.distance;
        }

        else {
            if(minD > f.distance) { // check which model distance is lower

                modelL = argv[i];
                minD = f.distance;
            }
        }
    }
    
    cout << "The text is most likely to be written in: " << modelL << endl;
    cout << "The distance between the text and the model is: " << minD << endl;

    model.clear();

}
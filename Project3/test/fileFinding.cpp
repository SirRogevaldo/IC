#include <string>
#include <iostream>
#include <filesystem>
#include <string.h>

#include "../src/fcm.cpp"

using namespace std;

namespace fs = std::filesystem;

int main()
{
    string fs = "";
    fcm f(3, 0.1);
    map<string, map<char, int>> model;
    

    string path = "../models";
    for (const auto & entry : fs::directory_iterator(path))

        fs = string(entry.path());
        size_t dot = fs.find_last_of(".");
        string destFilename = fs.substr(0, dot);
        cout << destFilename << endl;

        char* char_arr = &destFilename[0];


    f.loadModel(model, char_arr);

}
// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c

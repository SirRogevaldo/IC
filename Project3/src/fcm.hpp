#ifndef FCM_H
#define FCM_H

#include<map>
#include<string>

using namespace std;

/**
 * fcm - Finite Context Machine:
 * Collects statistical information about texts
 */
class fcm {
    private:
        int k; // k-order model
        double alpha; // smoothing parameter

    public:

        double distance;
        
        double estimatedEntropy;
        
        int nLetters;

        fcm();
        /**
         * FCM constructor
         * @param k order of the context model
         * @param alpha smoothing parameter
         */
        fcm(int k, double alpha);

        /**
         * FCM estimator
         * @brief Estimate the entropy and distance of file with initialized model
         * @param model model representing map data structure (INITIALIZED)
         * @param filename path to file
         */
        void estimate(map<string, map<char, int>> &model, char *filename);


        /**
         * FCM model loader
         * @brief load a model from a given file name
         * @param model model representing map data structure
         * @param filename source file
         */
        void loadModel(map<string, map<char, int>> &model, char *filename);


        /**
         * FCM existing model loader
         * @brief load existing model from a given file name
         * @param model data structure that will represent the model and will be loaded with information
         * @param filename source file
         */
        void loadAvailableModel(map<string, map<char, int>> &model, char *filename);

};

#endif
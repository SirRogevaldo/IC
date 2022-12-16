#ifndef FCM_H
#define FCM_H

#include<map>
#include<string>

using namespace std;

/**
 * fcm - Finite Context Machine. Collects statistical information about texts
 */
class fcm {
    private:
        int k; // k-order model
        double alpha;

    public:
        /**
         * @brief variable to store distance calculated
         */
        double distance;
        
        /**
         * @brief variable to store the estimated entropy of a given text previously calculated
         */
        double estimatedEntropy;
        
        /**
         * @brief variable to store number of letters of a file to be estimated
         */ 
        int nLetters;

        fcm();
        /**
         * FCM class constructor
         * @param k order of the context model
         * @param alpha smoothing parameter
         */
        fcm(int k, double alpha);

        /**
         * FCM estimator
         * @brief For a given model (already initialized) and a new file estimate the entropy and distance to the given file
         * @param model data structure that already must be initialized
         * @param filename path to file
         */
        void estimate(map<string, map<char, int>> &model, char *filename);


        /**
         * FCM model loader
         * @brief load a model from a given file name
         * @param model data structure that will represent the model and will be loaded with information
         * @param filename source file
         */
        void loadModel(map<string, map<char, int>> &model, char *filename);

};

#endif
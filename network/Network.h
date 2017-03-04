//
// Created by Vitaliy Schreibmann on 25/02/2017.
//

#ifndef MNIST_C_NN_NETWORK_H
#define MNIST_C_NN_NETWORK_H


#include "Nodes.h"
#include "NodesLayer.h"
#include <vector>

using namespace std;

class Network {

        unsigned int mNumberOfLayers;
        unsigned int* mLayerSizes;
        NodesLayer** layers;
        //displays the learning
        float averageError = 0;
        float numberOfTrainginSamples;

    public:
        Network(unsigned int layerSizes[], unsigned int);
        Network(const Network&);
        ~Network();

        void print();
        void print(unsigned int layer);
        vector<float> getOutputLayer();
        void feedforward(const vector<uint8_t>& input);
        void backPropagation(vector<uint8_t>& targetValue);

        void setNumberOfTrainingSamples(float number) {
            this->numberOfTrainginSamples = number;
        }

        float getAverageError() {
            return this->averageError;
        }


    protected:
        void generateBiases(NodesLayer* layer);
        void generateWeights(NodesLayer* layer);
        void generateNodes(NodesLayer* layer, unsigned int layerNr);

};


#endif //MNIST_C_NN_NETWORK_H

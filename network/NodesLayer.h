//
// Created by Vitaliy Schreibmann on 25/02/2017.
//

#ifndef MNIST_C_NN_NODESLAYER_H
#define MNIST_C_NN_NODESLAYER_H


#include "Nodes.h"
#include <vector>

using namespace std;

class NodesLayer {
    private:
        unsigned int layerNumber;

    public:
        NodesLayer();
        NodesLayer(unsigned int, unsigned int);
        ~NodesLayer();

        NodesLayer* prev;
        NodesLayer* next;
        Nodes** nodes;

        void print();
        unsigned int numberOfNodes;

        void feedforward(void);
        void calcHiddenGradient(void) const;
        void updateInputWeights(void);
        vector<float> getOutputAsVector() const;
        float summDOW(const NodesLayer* layer, const unsigned int currentNodeIndex) const;

};



#endif //MNIST_C_NN_NODESLAYER_H

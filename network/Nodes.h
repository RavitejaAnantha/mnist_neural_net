//
// Created by Vitaliy Schreibmann on 25/02/2017.
//

#ifndef MNIST_C_NN_NODES_H
#define MNIST_C_NN_NODES_H

#include <vector>

struct Connections {
    //Current weight of the connection to a node
    float weight;
    float deltaWeight;
};


class Nodes {

    private:
        //result of actionation function
        float outputValue;
        unsigned int myIndex;

    public:
        float mBias;
        float mGradient;

        Nodes(unsigned int myIndex);
        Nodes(unsigned int edges, unsigned int myIndex);
        ~Nodes();

        std::vector<Connections> outputWeights;
        void print();
        void calcGradient(const float);
        void calcHiddenGradient(const float);

        void setOutputValue(float value) {
            outputValue  = value;
        }

        float getOutputValue(void) const {
            return outputValue;
        }

};


#endif //MNIST_C_NN_NODES_H

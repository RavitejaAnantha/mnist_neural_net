//
// Created by Vitaliy Schreibmann on 25/02/2017.
//

#include "Nodes.h"
#include <iostream>
#include <cmath>
#include "MathNN.h"

using namespace std;

Nodes::Nodes(unsigned int myIndex) {
    this->myIndex = myIndex;
    mBias = 0;
}

Nodes::Nodes(unsigned int connections, unsigned int myIndex) {
    this->myIndex = myIndex;

    for(unsigned int i = 0; i < connections; ++i) {
        this->outputWeights.push_back(Connections());
    }
}

Nodes::~Nodes() {
    this->outputWeights.clear();
}

void Nodes::print() {
    cout << "Node: " << this->myIndex << " with Value " << this->outputValue << " with Bias: " << mBias;

    if(this->outputWeights.size() <= 0) {
        cout << endl;
        return;
    }

    cout << " and Weights ";

    for(size_t i = 0; i < this->outputWeights.size(); ++i) {
        cout << this->outputWeights[i].weight  << " ";
    }

    cout << endl;

}

void Nodes::calcGradient(const float targetValue) {
    float delta = targetValue - outputValue;
    this->mGradient = delta * MathNN::sigmoidDerivative(this->outputValue);
}

void Nodes::calcHiddenGradient(const float value) {
    this->mGradient = value * MathNN::sigmoidDerivative(this->outputValue);
}

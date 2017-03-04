//
// Created by Vitaliy Schreibmann on 25/02/2017.
//

#include "NodesLayer.h"
#include "MathNN.h"
#include <random>
#include <iostream>
#include <numeric>
#include <vector>

using namespace  std;

NodesLayer::NodesLayer() {
}

NodesLayer::NodesLayer(unsigned int numberOfnodes, unsigned int layerNumber) {
    this->layerNumber = layerNumber;
    this->numberOfNodes = numberOfnodes;
    nodes = new Nodes*[numberOfnodes];
    this->next = NULL;
    this->prev = NULL;
}

NodesLayer::~NodesLayer() {
    delete[] nodes;
}


void NodesLayer::print() {
    cout << "Layer: " << this <<  " with prev " << this->prev << " and next " << this->next << endl;

    for(unsigned int i = 0; i < this->numberOfNodes; ++i) {
        nodes[i]->print();
    }

    cout << endl;
}

void NodesLayer::feedforward() {
    //cout << "Layer " << this->layerNumber << endl;

    for(unsigned int i = 0; i < this->numberOfNodes; ++i) {
        const Nodes* currentNode = this->nodes[i];
        float summ = 0;


        //go trough all nodes from prev layer and multipley with my weight, summ it up
        for(unsigned int j = 0; j <  this->prev->numberOfNodes; ++j) {
            const Nodes* prevNode = this->prev->nodes[j];
            summ += prevNode->getOutputValue() * prevNode->outputWeights[i].weight;
        }

        //put the summ in the activation function and consider bias?
        const float active = MathNN::sigmoid(summ + currentNode->mBias);
        //        cout << "NA(" << this->layerNumber << "|" << i << "|" << active << ")" << endl;

        this->nodes[i]->setOutputValue(active);
    }
}

vector<float> NodesLayer::getOutputAsVector() const {
    vector<float> result;

    for(unsigned int var = 0; var < this->numberOfNodes; ++var) {
        result.push_back(this->nodes[var]->getOutputValue());
    }

    return result;
}

void NodesLayer::calcHiddenGradient(void) const {

    for(unsigned int i = 0; i < this->numberOfNodes; ++i) {
        const float summ = summDOW(next, i);
        this->nodes[i]->calcHiddenGradient(summ);
    }
}

float NodesLayer::summDOW(const NodesLayer* nextlayer, const unsigned int currentNodeIndex) const {

    float summ = 0.0f;

    for(unsigned int i = 0; i < nextlayer->numberOfNodes; ++i) {
        summ += this->nodes[currentNodeIndex]->outputWeights[i].weight *  nextlayer->nodes[i]->mGradient;
    }

    return summ;
}

void NodesLayer::updateInputWeights(void) {

    for(unsigned int i = 0; i < this->numberOfNodes; ++i) {
        const Nodes* current = this->nodes[i];

        for(unsigned int j = 0; j < this->prev->numberOfNodes ; ++j) {
            Nodes* prevNode = this->prev->nodes[j];
            float oldDeltaWeight = prevNode->outputWeights[i].deltaWeight;
            float newdeltaWeight = MathNN::eta * prevNode->getOutputValue() * current->mGradient + MathNN::alpha * oldDeltaWeight;

            prevNode->outputWeights[i].deltaWeight = newdeltaWeight;
            prevNode->outputWeights[i].weight += newdeltaWeight;
        }
    }
}

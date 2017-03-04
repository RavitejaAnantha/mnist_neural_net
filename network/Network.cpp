//
// Created by Vitaliy Schreibmann on 25/02/2017.
//

#include "Network.h"
#include "MathNN.h"
#include <random>
#include <iostream>
#include <numeric>
using namespace std;;

Network::Network(unsigned int layerSizes[], unsigned int size) : mLayerSizes(layerSizes) {
    mNumberOfLayers = size;
    layers = new NodesLayer*[mNumberOfLayers];

    for(unsigned int i = 0; i < mNumberOfLayers; ++i) {
        this->layers[i] = new NodesLayer(mLayerSizes[i], i);
        this->layers[i]->numberOfNodes = mLayerSizes[i];

        if(i > 0) {
            this->layers[i - 1]->next = this->layers[i];
            this->layers[i]->prev = this->layers[i - 1];
        }
    }

    for(unsigned int i = 0; i < mNumberOfLayers; ++i) {
        this->generateNodes(layers[i], i);
        this->generateBiases(layers[i]);
        this->generateWeights(layers[i]);
    }
}

Network::Network(const Network& src) {
    this->mLayerSizes = src.mLayerSizes;
    this->layers = src.layers;
    this->mNumberOfLayers = src.mNumberOfLayers;
}

Network::~Network() {
    delete[] mLayerSizes;

    for(unsigned int i = 0; i < mNumberOfLayers; ++i) {
        delete layers[i];
    }

    delete[] layers;
}

void Network::generateNodes(NodesLayer* layer, unsigned int layerNr) {
    layer->nodes = new Nodes*[mLayerSizes[layerNr]];

    for(unsigned int i = 0; i < mLayerSizes[layerNr]; ++i) {
        layer->nodes[i] = layer->next == NULL ? new Nodes(i) : new Nodes(mLayerSizes[layerNr + 1], i) ;
    }
}

void Network::generateBiases(NodesLayer* layer) {
    float value = MathNN::rand();

    for(unsigned int i = 0; i < layer->numberOfNodes; ++i) {
        layer->nodes[i]->mBias = value;
    }
}

void Network::generateWeights(NodesLayer* layer) {
    if(layer->next == NULL) {
        return;
    }

    for(unsigned int i = 0; i < layer->numberOfNodes; ++i) {
        const unsigned int numberOfWeights = layer->next->numberOfNodes;

        for(unsigned int j = 0; j < numberOfWeights; ++j) {
            float value = MathNN::rand();
            layer->nodes[i]->outputWeights[j].weight = value;
        }
    }
}

void Network::feedforward(const vector<uint8_t>& input) {

    //set input (first) layer
    for(unsigned int i = 0 ; i < layers[0]->numberOfNodes; ++i) {
        this->layers[0]->nodes[i]->setOutputValue(input[i]);
    }

    //Forward propagation starting after input layer
    for(unsigned int layerNum = 1 ; layerNum < mNumberOfLayers; ++layerNum) {
        this->layers[layerNum]->feedforward();
    }
}

void Network::backPropagation(vector<uint8_t>& targetValue) {

    //dont calucate the error for everthing but for every node invidualy and compute new weights based on thsi invidual error

    const NodesLayer* outputLayer = this->layers[this->mNumberOfLayers - 1];
    const vector<float> lastLayerOutput  = outputLayer->getOutputAsVector();
    const float cost_error = MathNN::calcMean(lastLayerOutput, targetValue);

    this->averageError = (this->averageError * this->numberOfTrainginSamples + cost_error) / (this->numberOfTrainginSamples + 1.0f);

    //calucate gradient for output
    for(unsigned int i = 0; i < outputLayer->numberOfNodes; ++i) {
        outputLayer->nodes[i]->calcGradient(targetValue[i]);
    }

    //calculate gradien for hidden
    for(unsigned int layerNum = this->mNumberOfLayers - 2; layerNum > 0 ; layerNum--) {
        this->layers[layerNum]->calcHiddenGradient();
    }

    //update weights
    for(unsigned int layerNum = this->mNumberOfLayers - 1; layerNum > 0 ; --layerNum) {
        this->layers[layerNum]->updateInputWeights();
    }
}


void Network::print() {
    for(unsigned int i = 0; i < this->mNumberOfLayers; ++i) {
        this->layers[i]->print();
    }
}

void Network::print(unsigned int layer) {
    this->layers[layer]->print();
}

vector<float> Network::getOutputLayer() {
    return this->layers[this->mNumberOfLayers - 1]->getOutputAsVector();
}

#include <iostream>
#include "network/Network.h"
#include "utils/MathNN.h"
#include "Mnist.h"
#include <iostream>
#include <string>

using namespace std;

struct Classfication {
    Classfication(float from, float to) {
        this->from = from;
        this->to = to;
        this->count = 0;
    }

    float from;
    float to;
    int count;
};


int labelDataToNumber(vector<uint8_t>& data);
void outPutValues(vector<float>& data);
void printState(Network* net, Mnist* mnist, size_t iteration);
void classify(vector<Classfication>& classes, vector<float> output, vector<uint8_t>& labels);

int main() {
    std::cout << "Hello, Neural Net!" << std::endl;
    vector<Classfication> classes;

    for(int from = 0, to = 5; to <= 100 ; from = from + 5, to = to + 5) {
        Classfication c(from, to);
        classes.push_back(c);
    }

    const int trainignBatchSize = 10000;
    const int testingBatchSize = 1000;
    const unsigned int interations = 1;

    Mnist* mnist = new Mnist(trainignBatchSize, true);
    //mnist->print();

    unsigned int layerSizes[] = {728, 100, 10};
    Network* net = new Network(layerSizes, 3);

    cout << "TRAINING" << endl;

    for(unsigned int iter = 0; iter < interations; ++iter) {
        cout << "iterations" << iter << endl;

        for(size_t i = 0; i < trainignBatchSize; ++i) {
            net->feedforward(mnist->images[i]);
            net->backPropagation(mnist->labels[i]);

            printState(net, mnist, i);

        }
    }

    cout << "TESTING" << endl;
    Mnist* mnist_test = new Mnist(testingBatchSize, false);

    for(size_t i = 0; i < testingBatchSize; ++i) {
        net->feedforward(mnist_test->images[i]);
        printState(net, mnist_test, i);
        classify(classes, net->getOutputLayer(), mnist_test->labels[i]);
    }

    cout << "CLASSES" << endl;

    for(size_t i = 0; i < classes.size(); ++i) {
        cout << "Class(" << classes[i].from << "-" << classes[i].to << "): " << classes[i].count << endl;
    }

    return 0;
}


void printState(Network* net, Mnist* mnist, size_t iteration) {
    vector<float> values = net->getOutputLayer();
    const int targetValue = labelDataToNumber(mnist->labels[iteration]);
    cout << "Should be : " << targetValue << " but is";
    outPutValues(values);
    cout << " with error: " << net->getAverageError() << endl;
}

int labelDataToNumber(vector<uint8_t>& data) {
    for(size_t i = 0; i < 10; ++i) {
        if(data[i] > 0) {
            return int(i);
        }
    }

    return -1;
}

void outPutValues(vector<float>& data) {

    for(size_t i = 0; i < data.size(); ++i) {
        cout << " N(" << i << "|" << data[i] << ") ";
    }
}

void classify(vector<Classfication>& classes, vector<float> output, vector<uint8_t>& labels) {
    const int value = labelDataToNumber(labels);

    //search classs for output
    for(size_t var = 0; var < classes.size(); ++var) {
        const float outPercent = output[value] * 100.0f;

        if(outPercent > classes[var].from && outPercent < classes[var].to) {
            classes[var].count++;
            break;
        }
    }
}


/**
    InputL -> HiddenL -> OutputL

    initialize network with random weights

    while(training data is there){

        for each sample x:
            prediction = neural_output(network, x)
            actucal = trained-output(x)
            error is (prediction - actual) on output node

        backwardpass:
            compute weights from hidden layer to ouptut layer
            compute weights from input layer to hidden layer
            update network weights
            until all are samples x are classified correctyl

            return finalized network
    }

*/

//
// Created by Vitaliy Schreibmann on 26/02/2017.
//

#include <cmath>
#include <cstdlib>
#include <vector>
#include "MathNN.h"
#include <random>
#include <cmath>
using namespace std;

//Random Number Generator
std::random_device rd;
std::mt19937 generator(rd());
//Distribution funciton
std::normal_distribution<float> distribution(0.0, 1.0);


/**
 * Calculates the cost function following http://neuralnetworksanddeeplearning.com/chap1.html
 * @param is is y(x)
 * @param should a
 * @return C(w,b) should be near 0
 */
float MathNN::calcMean(const vector<float>& is, const vector<uint8_t>& should) {
    float sum_sq = 0;

    for(size_t i = 0; i < is.size(); ++i) {
        const float a = is[i] - should[i];
        sum_sq += a * a;
    }

    return sqrt(sum_sq / is.size());
}

float MathNN::rand() {
    const float number = distribution(generator);
    return number >= -1.0f && number <= 1.0f ? number : rand();
}


/*
 * def sigmoid(z):
    return 1.0/(1.0+np.exp(-z))
    */

float MathNN::sigmoid(float z) {
    return 1.0f / (1.0f + exp(-z));
}

float MathNN::sigmoidDerivative(float value) {
    //derivates of sigmoid s: s*(1-s)
    const float temp = sigmoid(value);
    return temp * (1 - temp);
}

/** Activition function instead of the sigmoid function
 * @brief Nodes::activationFunction
 * @param value
 * @return
 */
float MathNN::atanh(float value) {
    return tanh(value);
}

float MathNN::atanhDerivative(float value) {
    return 1 - value * value; //approximation of tanh derivitive
}

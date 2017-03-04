//
// Created by Vitaliy Schreibmann on 26/02/2017.
//

#ifndef NN_C_MATHNN_H
#define NN_C_MATHNN_H

#include <vector>
using namespace std;

class MathNN {

    public:
        static float rand();
        static float sigmoid(float z);
        static float sigmoidDerivative(float value);

        static float atanh(float value);
        static float atanhDerivative(float value);

        static float calcMean(const vector<float>& is, const vector<uint8_t>& should);

        //learningrate
        static constexpr float eta = 0.2f;     //could be 0.0, 0.2, 0.5 bis 1.0

        //momentum
        static constexpr float alpha = 0.5f;  //could be 0.00f und 0.5f
};


#endif //NN_C_MATHNN_H

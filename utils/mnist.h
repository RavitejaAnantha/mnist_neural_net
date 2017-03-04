#ifndef MNIST_H
#define MNIST_H

#include <vector>

using namespace std;

class Mnist
{
    private:
        const int test_set_size = 10000;
        const int train_set_size = 60000;
        const char* file_test_images = "../../../assets/t10k-images-idx3-ubyte";
        const char* file_test_labels = "../../../assets/t10k-labels-idx1-ubyte";
        const char* file_train_images = "../../../assets/train-images-idx3-ubyte";
        const char* file_train_labels = "../../../assets/train-labels-idx1-ubyte";
        const int image_size = 28 * 28;


    public:
        Mnist();
        Mnist(int size, bool training);
        ~Mnist();

        vector<vector<uint8_t>> images;
        vector<vector<uint8_t>> labels;

        void print();
};

#endif // MNIST_H

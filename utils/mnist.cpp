#include "Mnist.h"
#include "MnistReader.h"

#include <iostream>

Mnist::Mnist()
{
}

Mnist::Mnist(int size, bool training) {

    MnistReader* reader = new MnistReader();
    const char* fileImages = training ? this->file_train_images : this->file_test_images;
    const char* fileLabels = training ? this->file_train_labels : this->file_test_labels;

    reader->readImageFile(fileImages, size, this->image_size, this->images);
    reader->readLabelFile(fileLabels, size, this->labels);
}

void Mnist::print() {

    if(!this->images.empty()) {
        cout << "Images data: " << endl;

        for(size_t i = 0; i < this->images.size(); ++i) {
            cout << "Image " << i << endl;

            for(int j = 0; j < this->image_size; ++j) {
                cout << int(this->images[i][j]) << " , ";
            }

            cout << endl;
        }
    }

    if(!this->labels.empty()) {
        cout << "Labels data: " << endl;

        for(size_t i = 0; i < this->labels.size(); ++i) {
            for(size_t j = 0; j < this->labels[i].size(); ++j) {
                cout << (char)(this->labels[i][j] + 48) << " , ";
            }

            cout << endl;
        }
    }
}

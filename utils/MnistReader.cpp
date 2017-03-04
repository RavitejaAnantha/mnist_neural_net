#include <string>
#include <vector>
#include <cstdio>
#include <math.h>
#include <iostream>
#include <fstream>

#include "MnistReader.h"

using namespace std;

int inverse(int i) {
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return int(ch1 << 24) + int(ch2 << 16) + int(ch3 << 8) + ch4;
}

void MnistReader::readImageFile(const char* filname, int NumberOfImages, int DataOfAnImage, vector<vector<uint8_t>>& arr) {
    arr.resize(NumberOfImages, vector<uint8_t>(DataOfAnImage));
    ifstream file(filname, ios::binary | ios::out);

    if(file.is_open()) {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = inverse(magic_number);
        file.read((char*) &number_of_images, sizeof(number_of_images));
        number_of_images = inverse(number_of_images);
        file.read((char*) &n_rows, sizeof(n_rows));
        n_rows = inverse(n_rows);
        file.read((char*) &n_cols, sizeof(n_cols));
        n_cols = inverse(n_cols);

        for(int i = 0; i < NumberOfImages; ++i) {
            for(int r = 0; r < n_rows; ++r) {
                for(int c = 0; c < n_cols; ++c) {
                    unsigned char temp = 0;
                    file.read((char*) &temp, sizeof(temp));
                    arr[i][(n_rows * r) + c] = temp;
                }
            }
        }

        file.close();
    }
}

void MnistReader::readLabelFile(const char* filname, int numberOFlabels, vector<vector<uint8_t>>& arr) {
    const int valuesPerSet = 10; //0-9
    const size_t batchsize = size_t(numberOFlabels);

    arr.resize(batchsize);
    ifstream file(filname, ios::binary);

    if(file.is_open()) {
        int maggic_number = 0;
        int number_of_labels = 0;
        file.read((char*)&maggic_number, 4);
        maggic_number = inverse(maggic_number);
        file.read((char*) &number_of_labels, 4);
        number_of_labels = inverse(number_of_labels);

        for(size_t i = 0; i < batchsize; i++) {
            unsigned char temp = 0;
            file.read((char*) &temp, sizeof(temp));
            vector<uint8_t> zeroone(valuesPerSet);
            zeroone[temp] = 1;
            arr[i] = zeroone;
        }

        file.close();
    }
}

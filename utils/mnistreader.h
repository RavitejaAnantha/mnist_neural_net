#ifndef MNISTREADER_H
#define MNISTREADER_H

#endif // MNISTREADER_H

#include <vector>

using namespace  std;

class MnistReader {

    public:
        void readLabelFile(const char* filname, int numberOFlabels, vector<vector<uint8_t>>& arr);
        void readImageFile(const char* filname, int NumberOfImages, int DataOfAnImage, vector<vector<uint8_t>>& arr);
};

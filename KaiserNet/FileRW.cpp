#include "Shared.hpp"
#include <fstream>

vector<unsigned char> ReadFromFile(string fileName) { //read the file, return the first line
    vector<unsigned char> binaryVec = vector<unsigned char>();

    std::ifstream fileReader{ fileName, std::ios::binary }; //ifstream needed instead of ofstream
    if (!fileReader.good() || !fileReader.is_open()) {
        Error("Couldn't read " + fileName + "!", 6, false); //big problem
        return binaryVec;
    }

    binaryVec = vector<unsigned char>(std::istreambuf_iterator<char>(fileReader), {});

    fileReader.close(); //won't need to read individual lines so i can close the reader

    if (binaryVec.empty())
        Error(fileName + " was empty!", 6, false);

    return binaryVec;
}

unsigned int FlipByte(unsigned int bits) {
    //bits =	0b 1110 0100; //example start
    //bits =	0b 0100 1110; //swap left with right
    //bits =	0b 0001 1011; //swap 1,2 with 3,4, and right side
    //bits =	0b 0010 0111; //swap bit 1 with 2 and 3 with 4 ,etc
    //result =	0b 0010 0111; //result
    bits = (bits & 0b11110000) >> 4 | (bits & 0b00001111) << 4; //swap left with right
    bits = ((bits & 0b11001100) >> 2) | ((bits & 0b00110011) << 2); //swap 1,2 ...
    bits = (bits & 0b10101010) >> 1 | ((bits & 0b01010101) << 1); //swap bit 1 with 2...
    return bits;
}
#ifndef FRONTCOMPRESSION_H
#define FRONTCOMPRESSION_H

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class FrontCompression{

    public:
        FrontCompression();
        void compress(string, string outputFilePath="");
        void decompress(string, string outputFilePath="");

    private:
        //return vector (dynamic array) each element in the vector consists of two elements name, phone
        vector<pair<string, string>> splitList(string);
        //the map is key value pair each character corresponds to an integer value (a => 10, …)
        map<char, short> charCodes;
        //will use this string to get the character by index intCodes[10] => a
        const string intCodes = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
        //flag to indicate that next number is the number produced by front compression algorithm
        const int FLAG = 63;
        //function to get the characters until finding a space or a new line
        int getCharCode(string, int &);
        //boolean to indicate if the file exists
        bool validFile;
};

#endif // FRONTCOMPRESSION_H

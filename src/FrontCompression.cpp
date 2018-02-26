#include "FrontCompression.h"
//fstream to read/write files
#include <fstream>
#include <ctype.h>
#include <vector>
#include <sstream>

FrontCompression::FrontCompression(){
    //each character is can be considered as an integer value
    //that integer value is the ASCII
    //fill the map with characters from 0 to 10
    for(int i = 0; i < 10; ++i)
        charCodes[i + '0'] = i;

    //fill the map with characters from a to z
    for(int i = 'a'; i <= 'z'; ++i)
        //'a' - 'a' = 0, 0 + 10 = 10
        //'z' - 'a' = 25, 25 + 10 = 35
        charCodes[i] = i - 'a' + 10;

    //fill the map with characters from A to Z
    for(int i = 'A'; i <= 'Z'; ++i)
        //'A' - 'A' = 0, 0 + 36 = 36
        //'Z' - 'A' = 25, 25 + 36 = 51
        charCodes[i] = i - 'A' + 36;

    //space = 62
    charCodes[' '] = 62;
    //initially the file is valid
    validFile = true;
}

vector<pair<string, string>> FrontCompression::splitList(string inputFilePath){
    //create a file
    ifstream file(inputFilePath);
    //if the file exists the it will be true else false
    validFile = (bool) file;
    vector<pair<string, string>> phoneList;
    //if the file is valid
    if(validFile){
        string line;
        int length;
        //while getting lines from the file
        //the string line will hold the value of the lines
        while(getline(file, line)) {
            //get line length
            length = (int) line.length();
            //loop through the characters of the line
            for (int i = 0; i < length - 1; ++i) {
                //if the current character is space
                //and the next character is number
                if (isspace(line[i]) && isdigit(line[i + 1])) {
                    //add pair in the vector
                    //the first element in the pair is string taken from the line starting
                    //from 0 until the index of the space
                    //the second element in the pair is string taken from the line starting
                    //from the index after the space until the end of the line
                    //ex: Ahmed 160 => {Ahmed, 160}
                    phoneList.push_back({
                        line.substr(0, i), line.substr(i+1, length - i - 1)
                        });
                    break;
                }
            }
        }
        //close the file
        file.close();
    }
    //return the vector
    return phoneList;
}

void FrontCompression::compress(string inputFilePath, string outputFilePath){
    //the input file path is the path of the file to compress
    //the output file path is the path of the file to write compression into it
    //if the outputFilePath is not empty string
    //then make a new file with the name of the input file + [compressed]
    outputFilePath = (int) outputFilePath.length() ? outputFilePath :
        (inputFilePath.substr(0, (int) inputFilePath.length() - 4) + "[compressed].txt");
    //get the name phone pair
    vector<pair<string, string>> phoneList = splitList(inputFilePath);
    //if the file path is not valid, finish
    if(!validFile){
        cout << "Compress: Invalid file path" << endl;
        return;
    }
    //if the file is empty, finish
    else if((int) phoneList.size() < 1){
        cout << "Compress: Empty file" << endl;
        return;
    }
    //create output file
    ofstream file(outputFilePath);
    //output the first line
    //get the length of the first name and the first phone number
    //phoneList[0] => the first element in the vector
    //phoneList[0].first => the first element in the pair
    //phoneList[0].second => the second element in the pair
    int nameLength = (int) phoneList[0].first.length(),
        numLength = (int) phoneList[0].second.length();
    //loop through each character in the name
    for(int i = 0; i < nameLength; ++i){
        //write in the file the integer value of that character
        file << charCodes[phoneList[0].first[i]];
        //if it is the last character
        if(i == nameLength - 1)
            //write in the file the integer value of space
            file << " " << charCodes[' '];
        //write a space
        file << " ";
    }
    //loop through each character in the phone number
    for(int i = 0; i < numLength; ++i){
        //write in the file the integer value of that character
        file << charCodes[phoneList[0].second[i]];
        //if it is the last character
        if(i == numLength - 1)
            //write in the file a new line
            file << "\n";
        //else write a space
        else
            file << " ";
    }
    //compress the rest of lines
    //get the number of elements in the vector = (number of lines in the file)
    int listSize = (int) phoneList.size();
    //initialize a counter to count the number of matching characters from the previous line
    int counter = 0;
    //boolean value to indicate if i'm counting
    bool counting = true;
    int outChar, k;
    //loop through each element in the vector
    for(int i = 1; i < listSize; ++i){
        //get the length of the name
        nameLength = (int) phoneList[i].first.length();
        //get the length of the phone number
        numLength = (int) phoneList[i].second.length();
        //loop through each character in the name
        for(k = 0; k < nameLength; ++k){
            //if the k < the length of the previous name
            //and the current character in the name == the current character in the previous name
            //increment the counter
            if(k < (int) phoneList[i - 1].first.length() &&
               phoneList[i].first[k] == phoneList[i - 1].first[k] && counting){
                   ++counter;
            }
            //if i was counting (but now i have stopped counting)
            else if(counting){
                //set counting to false
                counting = false;
                //get the character value to write in the file
                outChar = charCodes[phoneList[i].first[k]];
                //if the counter is > 0
                if(counter)
                    //write the flag then write the counter in the file
                    file << FLAG << " " << counter << " ";
                //write the current character value in the file
                file << outChar << " ";
                //reset the counter
                counter = 0;
            }
            //if i'm not counting
            else if(!counting){
                //get the current character value
                outChar = charCodes[phoneList[i].first[k]];
                //write in the file
                file << outChar;
                //if it is the last character in the name
                if(k == nameLength - 1)
                    //write space in the file
                    file << " " << charCodes[' '];
                file << " ";
            }
        }
        //if i end looping through the name and i was still counting
        //example: Loay Nour
        //Loay Nour
        if(counting){
            //if the counter > 0
            if(counter)
                //write in the file the flag and the counter
                file << FLAG << " " << counter << " ";
            //write a space
            file << charCodes[' '] << " ";
            //reset the counter
            counter = 0;
        }
        //set the counting flag to true
        counting = true;
        //loop through each character in the phone number
        for(int k = 0; k < numLength; ++k){
            //get the character value
            outChar = charCodes[phoneList[i].second[k]];
            //write it in the file
            file << outChar;
            //if it is the last character then write a new line
            if(k == numLength - 1)
                file << "\n";
            //else write a apace
            else
                file << " ";
        }
    }
    //close the file
    file.close();
}

//function to get the characters until it finds a space or new line or the line ends
int FrontCompression::getCharCode(string line, int &startingIndex){
    string str = "";
    //get the length of the string
    int length = (int) line.length();
    //loop through each character in the line starting form the startingIndex
    for(int i = startingIndex; i < length; ++i){
        //increment the index
        ++startingIndex;
        //if the character is a new line or space, end the loop
        if(line[i] == '\n' || line[i] == ' ')
            break;
        //add the character to the string
        str += line[i];
    }
    //convert the string into an integer
    stringstream ss(str);
    int charCode;
    ss >> charCode;
    //return the integer
    return charCode;
    //we will use that integer to find the character (intCodes[charCode] = character)
}

void FrontCompression::decompress(string inputFilePath, string outputFilePath){
    //the input file path is the path of the file to decompress
    //the output file path is the path of the file to write decompression into it
    //if the outputFilePath is not empty string
    //then make a new file with the name of the input file + [decompressed]
    outputFilePath = (int) outputFilePath.length() ? outputFilePath:
        inputFilePath.substr(0, (int) inputFilePath.length() - 4) + "[decompressed].txt";
    //the file to get the input from it
    ifstream inFile(inputFilePath);
    //if the file exists the it will be true else false
    validFile = (bool) inFile;
    //if the file path is not valid, finish
    if(!validFile){
        cout << "Decompress: Invalid file path" << endl;
        return;
    }
    //if the file is empty, finish
    //if the current character is the end of file
    else if(inFile.peek() == EOF){
        cout << "Decompress: Empty file" << endl;
        return;
    }
    //create file to write the output into it
    ofstream outFile(outputFilePath);
    string line;
    //create an empty vector
    vector<string> phoneList;
    //line index is the index of the line to write in the file
    int length, startingIndex = 0, charCode, lineIndex = 0;
    //get line by line from the file
    while(getline(inFile, line)){
        //get the line length
        length = (int) line.length();
        //while the starting index is < the length of the line
        while(startingIndex < length){
            //get the code of the character
            charCode = getCharCode(line, startingIndex);
            //add an empty string into the vector
            phoneList.push_back("");
            //if the code is the flag
            if(charCode == FLAG){
                //get the next number which is the number of character to take from the previous line
                charCode = getCharCode(line, startingIndex);
                //take the characters from the previous line
                phoneList[lineIndex] += phoneList[lineIndex - 1].substr(0, charCode);
            }
            //else (if the code is not the flag)
            else{
                //get the character corresponding to that number
                phoneList[lineIndex] += intCodes[charCode];
            }
        }
        //write the line to the file
        outFile << phoneList[lineIndex] << "\n";
        //reset the starting index
        startingIndex = 0;
        //increment the line index
        ++lineIndex;
    }
    //close the files
    inFile.close();
    outFile.close();
}

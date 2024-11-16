#include <iostream>
#include <fstream>
#include <unordered_map>

/*
This program implements a simple statisticial distribution of a given text.
The aim is to gather values for detecting a language for a given text.
*/

std::string subString(std::string target, int start, int length){
    std::string temp = "";
    for(int i = start; i < length; i++){
        temp += target[i];
    };
    return temp;
};

unsigned long int sumCounts(std::unordered_map<std::string, unsigned long int> m){
    unsigned long int count = 0;
    for(auto a : m){
        count += a.second;
    };
    return count;
};

std::unordered_map<std::string, double> nGramPVals(std::unordered_map<std::string, unsigned long int> m){
    std::unordered_map<std::string, double> tempM;
    unsigned long int count = 0;
    unsigned long int countMOne = 0;
    for(auto a : m){
        if(a.first.length() > 1){
            count = a.second;
            countMOne = m[subString(a.first, 0, a.first.length() - 1)];
            tempM[a.first] = count / countMOne;
            
        }
    };
    return tempM;
};

std::unordered_map<std::string, unsigned long int> count(std::unordered_map<std::string, unsigned long int> m, int nGramSize, std::string text){
    std::string tempText = "";
    std::string window = "";

    for(int j = 0; j < nGramSize; j++){
        tempText += "<s>";
    };
    tempText += text + "</s>";
    for(unsigned long int i = 0; i < text.length(); i++){
        window = subString(tempText, i, i+nGramSize);
        if(!m.count(window)){
            m[window] = 1;
        }
        else{
            m[window] += 1;
        }
    };
    
    return m;
};

unsigned int nGramCounts(std::unordered_map<std::string, unsigned long int> m, int nGramCount){
    unsigned int count = 0;
    for(auto e : m){
        if(e.second == nGramCount){
            count += e.second;
        }
    };
    return count;
};

int main(int argc, char **argv){
    std::unordered_map<std::string, unsigned long int> nGramCount;
    std::string mystring = "<s>";
    std::string testStr = "";
    int i = 4;
    unsigned long int N1 = 0;
    unsigned long int N2 = 0;
    double backOff = 0.0; 
    std::ifstream myfile ("../../res/prideAndPrejudice.txt");

    while(!myfile.eof()){
        mystring += (char) myfile.get();
    };
    myfile.close();
    for(i; i > 0; i--){
        nGramCount = count(nGramCount, i, mystring);
    };
    //k = sumCounts(nGramCount);
    N1 = nGramCounts(nGramCount, 1);
    N2 = nGramCounts(nGramCount, 2);
    backOff = N1 / (N1 + 2*N2);
    std::cout << backOff << "\n";
    return 0;
}

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <chrono>
#include <windows.h>
/*
This program implements a simple statisticial distribution of a given text.
The aim is to gather values for detecting a language for a given text.
*/

std::string subString(std::string target, int start, int length){
    std::string temp = "";
    for(int i = start; i < start + length; i++){
        temp += target[i];
    };
    return temp;
};

long int sumCounts(std::unordered_map<std::string, long int> m){
    long int count = 0;
    for(auto a : m){
        count += a.second;
    };
    return count;
};

std::unordered_map<std::string, float> nGramPVals(std::unordered_map<std::string, long int> m){
    std::unordered_map<std::string, float> tempM;
    long int count = 0;
    long int countMOne = 0;
    for(auto a : m){
        if(a.first.length() > 1){
            count = a.second;
            countMOne = m[subString(a.first, 0, a.first.length() - 1)];
            tempM[a.first] = count / countMOne;
            
        }
    };
    return tempM;
};

std::unordered_map<std::string, long int> count(std::unordered_map<std::string, long int> m, int nGramSize, std::string path){
    std::string tempText = "";
    std::string window = "";
    std::ifstream myfile(path);

    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();
    unsigned char ch;
    /*
    for(int j = 0; j < nGramSize; j++){
        tempText += "<s>";
    };
    tempText += text + "</s>";
    */
    for(int c = 0; c < nGramSize; c++){
        myfile >> ch;
        tempText += ch;//myfile.get();
    };
    
    std::cout << "Begin counting of n-gram-size: " << nGramSize  << "\n";
    while(!myfile.eof()){
        if(!m.count(tempText)){
            m[tempText] = 1;
        }
        else{
            m[tempText] += 1;
        }
        std::cout << tempText;
        myfile >> ch;
        tempText += ch;//myfile.get();
        tempText = subString(tempText, 1, nGramSize);
    };/*

    for(long int i = 0; i < text.length(); i++){
        window = subString(tempText, i, i+nGramSize);
        if(!m.count(window)){
            m[window] = 1;
        }
        else{
            m[window] += 1;
        }
    };
    */
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    ms d = std::chrono::duration_cast<ms>(fs);
    std::cout << "End count of n-gram-size: " << nGramSize << "\n";
    //std::cout << fs.count() << "s\n";
    std::cout << d.count() << "ms\n";
    return m;
};

unsigned int nGramCounts(std::unordered_map<std::string, long int> m, int nGramCount){
    unsigned int count = 0;
    for(auto e : m){
        if(e.second == nGramCount){
            count += e.second;
        }
    };
    return count;
};

std::vector<std::string> splitStr(std::string s, std::string spl){
    std::string sub = "";
    std::string temp = "";
    std::vector<std::string> container;
    unsigned int i = 0;
    
    while(i < s.length()){
        sub = subString(s, i, spl.length());
        if(sub == spl){
            container.push_back(temp);
            temp = "";
            i += spl.length();
        }
        else{
            temp += s[i];
            i++;
        }
    };
    if(temp != ""){
        container.push_back(temp);
    };
    return container;

}

void writeToFile(std::string path, std::unordered_map<std::string, long int> container){

    std::ofstream myfile(path);
    for(auto c : container){
        myfile << c.first << " " << c.second << "\n";
    }
    return;
}

int main(int argc, char **argv){
    std::unordered_map<std::string, long int> nGramCount;
    std::string mystring = "";
    std::string testStr = "";
    long int N1 = 0;
    long int N2 = 0;
    float backOff = 0.0;
    /*
    std::ifstream myfile ("../../../res/prideAndPrejudice.txt");
    std::cout << "test\n";
    while(!myfile.eof()){
        mystring += (char) myfile.get();
    };    std::ifstream myfile ("../../../res/prideAndPrejudice.txt");
    std::cout << "test\n";
    while(!myfile.eof()){
        mystring += (char) myfile.get();
    };
    myfile.close();
    std::cout << mystring.length();
    myfile.close();
    std::cout << mystring.length();
    */
    
    for(int i = 1; i > 0; i--){
        nGramCount = count(nGramCount, i, "./../res/Language-Samples/german.txt");
        //nGramCount = count(nGramCount, i, "../../../res/prideAndPrejudice.txt");
    };
    
    std::cout << "Zählen erfolgreich \n";
    writeToFile("./../res/test.txt", nGramCount);
    
    /*
    //k = sumCounts(nGramCount);
    N1 = nGramCounts(nGramCount, 1);
    N2 = nGramCounts(nGramCount, 2);
    backOff = N1 / (N1 + 2*N2);
    std::cout << backOff << "\n";
    */
    return 0;
}

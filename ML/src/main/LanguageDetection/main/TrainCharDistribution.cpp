#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <chrono>

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

int getUTF8Length(std::string s){

    unsigned char c = 0x80;
    unsigned char d = c >> 1;
    int counter = 1;
    std::string checker = "";
    for(auto x : s){
        checker += x & c ? "1" : "0";
        checker += x & d ? "1" : "0";
        if(checker[0] == '0'){
            return counter;
        }
        else if(checker[0] == '1' && checker[1] == '0'){
            counter += 1;
        }
        else{
            if(counter > 1){
                return counter;
            }
        }
        checker = "";
    }
    return counter;
};

std::string getUTF8Str(std::string s){
    std::string temp = "";
    unsigned char c = 0x80;
    unsigned char d = c >> 1;
    int counter = 1;
    std::string checker = "";
    for(auto x : s){
        temp += x;
        checker += x & c ? "1" : "0";
        checker += x & d ? "1" : "0";
        if(checker[0] == '0'){
            return temp;
        }
        else if(checker[0] == '1' && checker[1] == '0'){
            counter += 1;
            continue;
        }
        else{
            if(counter > 1){
                return temp;
            }
        }
        checker = "";
    }
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
    
    
    for(int i = 1; i > 0; i--){
        nGramCount = count(nGramCount, i, "./../res/Language-Samples/german.txt");
        //nGramCount = count(nGramCount, i, "../../../res/prideAndPrejudice.txt");
    };
    
    std::cout << "Zählen erfolgreich \n";
    writeToFile("./../res/test.txt", nGramCount);
    */
    /*
    
    string temp = ""; 
    string temp2 = "";
    string start = "";
    string s = "fhwoxkrjeoelnddbdhowofhwoxk)aä@âáàåã&-$%śccxvttøœrjeoelnddbdà";
    for(int i = 0; i < s.length(); i++){
      
      temp = "";
      for(unsigned char c = 0x80; c; c >>=1){
        temp += (s[i] & c ? "1" : "0");
      }
    
      if(temp[0] == '0'){
        if(temp2.length() > 0){
          cout << start << ": " << temp2 << "\n";
          temp2 = "";
          start = "";
        }
        start = s[i];
        cout << start << ": " << temp << "\n";
        temp = "";
        start = "";
        temp2 = "";
      }
      
      else if(temp[0] == '1' && temp[1] == '1'){
        if(temp2.length() > 0){
          cout << start << ": " << temp2 << "\n";
          temp2 = "";
          start = "";
        }
        start += s[i];
        temp2 += temp + " ";
      }
      else{
      
        temp2 += temp + " ";
        start += s[i];
        if(i == s.length() - 1){
          //cout << i << " " << s.length() << "\n";
          cout << start << ": " << temp2 << "\n";
        }
      }
    }
    */
    std::cout << getUTF8Length("ä") << "\n";
    std::cout << getUTF8Str("*") << "\n\n";
    std::cout << getUTF8Length("𒀁") << "\n";
    std::cout << getUTF8Str("𒀁") << "\n";
    return 0;
}

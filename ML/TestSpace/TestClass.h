#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;
class TestClass{

    public:
     

     TestClass(string word);
     char getChar();
     void inc();
     int getInd();
     int getCharCount(char c);
     void dec();
     unordered_map<char, int> getMap();
     string getWord();
     
    private:
     int i;
     string c;     
     unordered_map<char, int> m;
     int k;
     void countChars();//unordered_map<char, int> m, string word, int len);
     void toLower();



};
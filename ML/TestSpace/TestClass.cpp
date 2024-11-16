#include "TestClass.h"



TestClass::TestClass(string word){

    c = word;
    i = 0;
    k = word.length() - 1;
    unordered_map<char, int> m;
    toLower();
    countChars();
}

void TestClass::toLower(){
    string temp = "";
    for(char x : c){
        if(x >= 65 && x <= 90){
            temp += x + 32;
        }
        else{
            temp += x;
        }
    }
    c = temp;
};

void TestClass::countChars(){//unordered_map<char, int> m, string word, int f){
    for(int l = 0; l <= k; l++){
        char x = c[l];
        if(!m.count(x)){
            m.insert({x, 1});
        }
        else{
            m[x] += 1;
        }
    }
}

void TestClass::inc(){
    if(i == k){
        cout << "Can't increase anymore" << "\n";
        return;
    }
    i += 1;
}

void TestClass::dec(){
    if(!i){
        cout << "Cant't decrease anymore" << "\n";
        return;
    }
    i -= 1;
}
int TestClass::getInd(){

    return i;
}

char TestClass::getChar(){

    return c[i];
}
string TestClass::getWord(){
    
    return c;

}
int TestClass::getCharCount(char c){
    return m[c];
}

unordered_map<char, int> TestClass::getMap(){

    return m;
}

int main(int argc, char **argv){
    string f = "Hallihallo!";
    int len = f.length();
    TestClass t(f);
    cout << t.getCharCount('h') << "\n";
    return 0;
}
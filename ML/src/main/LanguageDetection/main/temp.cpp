#include <iostream>
#include <fstream>
int main(int argc, char** argv){
    std::ofstream myfile("./baum.txt");
    myfile << "ß";
    std::cout << "ß\n";
    return 0;
}
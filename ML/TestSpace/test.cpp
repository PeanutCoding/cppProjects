#include <map>
#include <iostream>

int main(int argc, char **argv){

    std::map<std::string, int> m;
    m["hello"] = 1;
    printf("%d\n", m["hello"]);
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
int main()
{
    std::ifstream comm("/proc/self/comm");
    std::string name;
    getline(comm, name);
    std::cout << "my name is " << name << '\n';
}

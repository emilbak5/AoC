#include <iostream>
#include <fstream>
#include <vector>





template<typename T>
std::vector<T> read_file(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<T> result;
    T value;

    while (std::getline(file, value))
        result.push_back(value);
    return result;
}






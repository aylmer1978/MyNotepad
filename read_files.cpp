#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main () {

    fs::path my_path = fs::current_path();
    std::cout << my_path << std::endl;

    for (auto& entry : fs::directory_iterator{my_path}) {
        std::cout << entry << std::endl;
    }

    return 0;
}
#include <filesystem>
#include <iostream>
#include <string>

int main () {

    for (const auto &entrada : std::filesystem::directory_iterator(".")) {
        std::string file = entrada.path().string();
        if (file.length() >= 3) {
            if (file.substr(file.length()-4) == ".txt") {
                std::cout << file << std::endl;
            }
        }
    }

    return 0;
}

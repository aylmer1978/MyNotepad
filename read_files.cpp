// #include <iostream>
// #include <filesystem>

// namespace fs = std::filesystem;

// int main () {

//     fs::path my_path = fs::current_path();
//     std::cout << my_path << std::endl;

//     for (auto& entry : fs::directory_iterator{my_path}) {
//         std::cout << entry << std::endl;
//     }

//     return 0;
// }
//

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

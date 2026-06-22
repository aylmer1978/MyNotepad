#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

 std::vector<std::string> files_in_directory() {
     std::vector<std::string> archivos_txt;

     for (const auto &entrada : std::filesystem::directory_iterator(".")) {
         std::string file = entrada.path().string();
         if (file.length() >= 4) {
             if (file.substr(file.length()-4) == ".txt") {
                 //std::cout << file << std::endl;
                 archivos_txt.push_back(file);
             }
         }
     }

     return archivos_txt;
 }

std::string return_load_txt() {

    int load_txt;

    for (size_t i = 0;i< files_in_directory().size();i++) {
        std::cout << i << ": " << files_in_directory().at(i) << std::endl;
    }

    std::cout << "Elige el archivo a cargar: ";
    std::cin >> load_txt;

    return files_in_directory().at(load_txt);

}

int main () {

    std::string eleccion = return_load_txt();
    std::cout << "Has elegido: " << eleccion << std::endl;

    return 0;
}

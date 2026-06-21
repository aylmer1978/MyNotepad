#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main () {

    std::vector<std::string> frases = {"Frase 1", "Frase 2", "Frase 3"};

    std::string name_file;
    std::cout << "Escribe el nombre del archivo: " << std::endl;
    std::cin >> name_file;
    name_file.append(".txt");
    
    std::ofstream archivo(name_file);

    for (size_t i=0;i<frases.size();i++) {
        std::cout << frases.at(i) << std::endl;
        archivo << frases.at(i) << std::endl;
    }

    archivo.close();

    return 0;
}
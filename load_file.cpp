#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main () {
    std::ifstream archivo("my_file.txt");

    std::vector<std::string> lineas_cargadas;

    std::string linea_leida;
    while (std::getline(archivo, linea_leida)) {
        lineas_cargadas.push_back(linea_leida);
    }

    for (size_t i=0;i < lineas_cargadas.size();i++) {
        std::cout << lineas_cargadas.at(i) << std::endl;
    }


    return 0;
}
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// Esta funcion devuelve los .txt en un array
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

// Esta función usa un array de strings para elegir uno y devuelve el string para su carga
std::string return_load_txt(std::vector<std::string> archivos) {

    size_t load_txt;

    for (size_t i = 0;i< archivos.size();i++) {
        std::cout << i << ": " << archivos.at(i) << std::endl;
    }

    std::cout << "Elige el archivo a cargar: ";
    std::cin >> load_txt;

    while (std::cin.fail()) {
        std::cin.clear();                                              // resetea el "semáforo"
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // descarta lo que quedó atascado
        std::cout << "No es un número, elige de nuevo de 0 a " << archivos.size() << ": ";
        std::cin >> load_txt;                                          // ahora sí, intento limpio
    }

    while (load_txt >= archivos.size()) {
        std::cout << "No en rango. Elige el archivo a cargarde 0 a " << archivos.size() << ": ";
        std::cin >> load_txt;
        while (std::cin.fail()) {
            std::cin.clear();                                         
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "No es un número, elige de nuevo de 0 a " << archivos.size() << ": ";
            std::cin >> load_txt;                                   
        }
    }
    return archivos.at(load_txt);
}


int main () {

    std::string eleccion = return_load_txt(files_in_directory());
    std::cout << "Has elegido: " << eleccion << std::endl;

    return 0;
}

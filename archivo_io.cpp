#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Esta funcion devuelve los .txt en un array
std::vector<std::string> files_in_directory() {
  std::vector<std::string> archivos_txt;

  for (const auto &entrada : std::filesystem::directory_iterator(".")) {
    std::string file = entrada.path().string();
    if (file.length() >= 4) {
      if (file.substr(file.length() - 4) == ".txt") {
        // std::cout << file << std::endl;
        archivos_txt.push_back(file);
      }
    }
  }

  archivos_txt.insert(archivos_txt.begin(), "Archivo en blanco.");

  return archivos_txt;
}

// Esta función usa un array de strings para elegir uno y devuelve el string
// para su carga
std::string return_load_txt(std::vector<std::string> archivos) {

  size_t load_txt;

  for (size_t i = 0; i < archivos.size(); i++) {
    std::cout << i << ": " << archivos.at(i) << std::endl;
  }

  std::cout << "Elige el archivo a cargar: ";
  std::cin >> load_txt;

  while (std::cin.fail() || load_txt >= archivos.size()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Erróneo, elige de nuevo de 0 a " << archivos.size() - 1
              << ": ";
    std::cin >> load_txt;
  }

  return archivos.at(load_txt);
}

// Funcion para guardar el documento
void save_file(const std::vector<std::string> &frases, std::string name_file) {
    std::ofstream archivo(name_file);

    for (size_t i=0;i<frases.size();i++) {
        archivo << frases.at(i) << std::endl;
    }

    archivo.close();
}

// Funcion para cargar el documento al inicio
std::vector<std::string> load_file(std::string name_file) {

    std::vector<std::string> lineas_cargadas;

    if (name_file == "Archivo en blanco.") {
      lineas_cargadas = {""};

    } else {

      std::ifstream archivo(name_file);

      std::string linea_leida;
      while (std::getline(archivo, linea_leida)) {
          lineas_cargadas.push_back(linea_leida);
      }

      if (lineas_cargadas.empty()) {
        lineas_cargadas = {""};
      }

    }

    return lineas_cargadas;
}
#include <iostream>
#include <string>
#include <vector>

void show_frases(const std::vector<std::string>& lineas, int fila, int columna) {
  for (size_t i = 0; i < lineas.size(); i++) {
    if (i == fila) {
      std::cout << lineas.at(fila).substr(0, columna) << "|" << lineas.at(fila).substr(columna) << std::endl;
    } else {
      std::cout << lineas.at(i) << std::endl;
    }
  }
}


int main() {

  std::vector<std::string> lineas = {"Esta es la primera linea.", "Corto", "Esta es la tercera linea."};

  int fila = 1;
  int columna = 2;

  
  int cursor = 0;
  char comando = ' ';
  
  std::cout << "Escribe 'd' o 'i'" << std::endl;
  
  show_frases(lineas, fila, columna);

  while (comando != 'q') {

    std::cin >> comando;

    if (comando == 'd') {
      if (columna < lineas.at(fila).length()) {
        columna++;
      } 

    } else if (comando == 'i') {
      if (columna > 0) {
        columna--;
      }
    } else if (comando == 'w') {
      if (fila > 0) {
        fila--;
        if (columna > lineas.at(fila).length()) {
          columna = lineas.at(fila).length();
        }
      }
      
    } else if (comando == 's') {
      if (fila < lineas.size() - 1) {
        fila++;
        if (columna > lineas.at(fila).length()) {
          columna = lineas.at(fila).length();
        }
      }
    }

    show_frases(lineas, fila, columna);
    
  }
  
  return 0;
}

#include <iostream>
#include <string>
#include <vector>

void show_frases(const std::vector<std::string> &lineas, int fila,
                 int columna) {
  for (size_t i = 0; i < lineas.size(); i++) {
    if (i == fila) {
      std::cout << lineas.at(fila).substr(0, columna) << "|"
                << lineas.at(fila).substr(columna) << std::endl;
    } else {
      std::cout << lineas.at(i) << std::endl;
    }
  }
}

// Main function donde introduzco letras y muevo el cursor con las teclas d/i/w/s
int main() {

  std::vector<std::string> lineas = {
      "Esta es la primera linea.", "Texto corto.", "Esta es la tercera linea."};

  int fila = 0;
  int columna = 0;

  char comando = ' ';

  std::cout << "Escribe 'd/i' (der/izq), 'w/s' (up/down) o 'q' (quit)"
            << std::endl;

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
    } else {
      lineas.at(fila).insert(columna, 1, comando);
      columna++;

    }

    show_frases(lineas, fila, columna);
  }

  return 0;
}

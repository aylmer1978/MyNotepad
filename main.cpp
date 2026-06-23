#include <iostream>
#include <string>
#include <vector>
#include "archivo_io.h"

// Funcion con la que muestro todos los textos en pantalla con el cursor.
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

// Función con avance del cursor si es UTF-8
int bytes_del_caracter (const std::string &texto, size_t posicion) {
  unsigned char byte = texto[posicion];
  if ((byte & 0xE0) == 0xC0) {
    return 2;
  } else {
    return 1;
  }
}

int main (){
  
  std::string my_word = "moño";

  for (size_t i = 0;i<my_word.length();i++) {
    std::cout << bytes_del_caracter(my_word,i);
    std::cout << my_word.at(i) << std::endl;
  }

  return 0;
}

// Main function donde introduzco letras y muevo el cursor con las teclas 'd/i/w/s'
// int main() {

//   // esto es un resto de la prueba de carga, solo provisional
//   std::string eleccion = return_load_txt(files_in_directory());
//   std::cout << "Has elegido: " << eleccion << std::endl;

//   std::vector<std::string> lineas;

//   lineas = load_file(eleccion);

//   int fila = 0;
//   int columna = 0;

//   char comando = ' ';

//   std::cout << "Escribe 'd/i' (der/izq), 'w/s' (up/down) o 'q' (quit)"
//             << std::endl;

//   show_frases(lineas, fila, columna);

//   while (comando != 'q') {

//     std::cin >> comando;

//     if (comando == 'd') {
//       if (columna < lineas.at(fila).length()) {
//         columna++;
//       }

//     } else if (comando == 'i') {
//       if (columna > 0) {
//         columna--;
//       }
//     } else if (comando == 'w') {
//       if (fila > 0) {
//         fila--;
//         if (columna > lineas.at(fila).length()) {
//           columna = lineas.at(fila).length();
//         }
//       }

//     } else if (comando == 's') {
//       if (fila < lineas.size() - 1) {
//         fila++;
//         if (columna > lineas.at(fila).length()) {
//           columna = lineas.at(fila).length();
//         }
//       }

//     } else if (comando == 'x') {
//       if (columna > 0) {
//         lineas.at(fila).erase(columna - 1, 1);
//         columna--;
//       } else {
//         if (fila > 0) {
//           size_t longitud = lineas.at(fila - 1).length();
//           lineas.at(fila - 1) += lineas.at(fila);
//           lineas.erase(lineas.begin() + fila);
//           fila--;
//           columna = longitud;
//         }
//       }

//     } else if (comando == 'v') {
//       if (columna == lineas.at(fila).length()) {
//         if (fila < lineas.size() - 1) {
//           lineas.at(fila) += lineas.at(fila + 1);
//           lineas.erase(lineas.begin() + fila + 1);
//         }
//       } else {
//         lineas.at(fila).erase(columna, 1);
//       }

//     } else if (comando == 'n') {
//       std::string nueva_linea = lineas.at(fila).substr(0, columna);
//       lineas.insert(lineas.begin() + fila + 1, lineas.at(fila).substr(columna));
//       lineas.at(fila) = nueva_linea;
//       fila++;
//       columna = 0;

//     } else if (comando == 'g') {
//       save_file(lineas);

//     } else {
//       lineas.at(fila).insert(columna, 1, comando);
//       columna++;
//     }

//     show_frases(lineas, fila, columna);
//   }

//   return 0;
// }

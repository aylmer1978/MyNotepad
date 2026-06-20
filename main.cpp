#include <iostream>
#include <string>

int main() {

  std::string contenido = "Hello, world!";
  std::string nuevo_valor;
  int cursor = 0;
  char comando = ' ';

  std::cout << "Escribe 'd' o 'i'" << std::endl;

  std::cout << contenido.substr(0, cursor) << "|"
            << contenido.substr(cursor, contenido.length() - cursor)
            << std::endl;

  while (comando != 'q') {

    std::cin >> comando;

    if (comando == 'd') {
      if (cursor < contenido.length()) {
        cursor++;
      }

    } else if (comando == 'i') {
      if (cursor > 0) {
        cursor--;
      }

    } else if (comando == 'b') {
      if (cursor > 0) {
        contenido.erase(cursor - 1, 1);
        cursor--;
      }

    } else if (comando == 'q') {
      break;

    } else if (comando == 'x') {
      if (cursor < contenido.length()) {
        contenido.erase(cursor, 1);
      }

    } else {
      contenido.insert(cursor, 1, comando);
      cursor++;
    }

    std::cout << contenido.substr(0, cursor) << "|"
              << contenido.substr(cursor, contenido.length() - cursor)
              << std::endl;
  }

  return 0;
}

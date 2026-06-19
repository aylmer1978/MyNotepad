#include <iostream>
#include <string>

int main() {

  std::string contenido = "Hello, world!";
  std::string nuevo_valor;
  int cursor = 0;
  char comando = ' ';

  std::cout << "Escribe 'd' o 'i'" << std::endl;
  

  while (comando != 'q') {

    std::cin >> comando;

    if (comando == 'd') {
      if (cursor < contenido.length()) {
        cursor++;
      }
      std::cout << "El cursor está en la posición: " << cursor << std::endl;
    } else if (comando == 'i') {
      if (cursor > 0) {
        cursor--;
        
      }
      std::cout << "El cursor está en la posición: " << cursor << std::endl;
    } else if (comando == 'q') {
      break;
    }

    std::cout << contenido.substr(0, cursor) << "|" << contenido.substr(cursor, contenido.length()-cursor) << std::endl;

  }

  return 0;
}

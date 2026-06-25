#include <iostream>
#include <string>
#include <vector>
#include "archivo_io.h"
#include "ncurses.h"

#define CTRL(x) ((x) & 0x1f)

// Funcion con la que muestro todos los textos en pantalla con el cursor.
void show_frases(const std::vector<std::string> &lineas, int fila,
                 int columna, std::string nombre_archivo) {
  clear();
  
  std::string name_program = "Write Something Nice";
  std::string texto_barra = name_program + " - " + nombre_archivo;

  size_t filas, columnas;

  getmaxyx(stdscr, filas, columnas);

  std::string relleno((columnas - texto_barra.length())/2, ' ');
  std::string relleno_2(columnas - texto_barra.length() - relleno.length(), ' ');
  std::string fila_superior = relleno + texto_barra + relleno_2;

  attron(A_REVERSE);
  mvprintw(0, 0, "%s", fila_superior.c_str());
  attroff(A_REVERSE);

  for (size_t i = 0; i < lineas.size(); i++) {
    mvprintw(i+2, 0, "%s", lineas.at(i).c_str());
  }

  move(fila+2,columna);
  refresh();
}

// Estas tres funcionmes sirven para comprobar el tamaño de bytes de un caracter 

// Función con avance del cursor si es UTF-8
int bytes_del_caracter (const std::string &texto, size_t posicion) {
  unsigned char byte = texto[posicion];
  if ((byte & 0xE0) == 0xC0) {
    return 2;
  } else {
    return 1;
  }
}

// Funcion para comprobar si el caracter anterior es especial
int bytes_caracter_izquierda (const std::string &texto, size_t posicion) {
  unsigned char byte = texto[posicion-1];
  if ((byte & 0xC0) == 0x80) {
    return 2;
  } else {
    return 1;
  }
}

// Funcion que comprueba si la posicion del cursor ha caido en medio de los bytes de un caracter especial al subir y bajar
bool es_continuacion (const std::string &texto, size_t posicion) {
  unsigned char byte = texto[posicion];
  if ((byte & 0xC0) == 0x80) {
    return true;
  } else {
    return false;
  }
}

// Main function donde introduzco letras y muevo el cursor con las teclas 'd/i/w/s'
int main() {
  
  // esto es un resto de la prueba de carga, solo provisional
  std::string nombre_archivo_actual = return_load_txt(files_in_directory());
  std::cout << "Has elegido: " << nombre_archivo_actual << std::endl;
  
  std::vector<std::string> lineas;
  
  lineas = load_file(nombre_archivo_actual);
  
  int fila = 0;
  int columna = 0;
  
  int comando = ' ';

  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  
  show_frases(lineas, fila, columna, nombre_archivo_actual);

  while (comando != CTRL('q')) {

    comando = getch();

    if (comando == KEY_RIGHT) {
      if (columna < lineas.at(fila).length()) {
        columna += bytes_del_caracter(lineas.at(fila), columna);
      }

    } else if (comando == KEY_LEFT) {
      if (columna > 0) {
        columna -= bytes_caracter_izquierda(lineas.at(fila), columna);
      }

    } else if (comando == KEY_UP) {
      if (fila > 0) {
        fila--;
        if (columna > lineas.at(fila).length()) {
          columna = lineas.at(fila).length();
        }
          if (columna < lineas.at(fila).length() && es_continuacion(lineas.at(fila), columna)) {
            columna--;  
          }
      }

    } else if (comando == KEY_DOWN) {
      if (fila < lineas.size() - 1) {
        fila++;
        if (columna > lineas.at(fila).length()) {
          columna = lineas.at(fila).length();
        }
          if (columna < lineas.at(fila).length() && es_continuacion(lineas.at(fila), columna)) {
            columna--;  
          }
      }

    } else if (comando == KEY_BACKSPACE) {

        if (columna > 0) {
          int posiciones = bytes_caracter_izquierda(lineas.at(fila), columna);
          lineas.at(fila).erase(columna - posiciones, posiciones);
          columna -= posiciones;

        } else {
          if (fila > 0) {
            size_t longitud = lineas.at(fila - 1).length();
            lineas.at(fila - 1) += lineas.at(fila);
            lineas.erase(lineas.begin() + fila);
            fila--;
            columna = longitud;
          }
        }

    } else if (comando == KEY_DC) {

      if (columna == lineas.at(fila).length()) {
        if (fila < lineas.size() - 1) {
          lineas.at(fila) += lineas.at(fila + 1);
          lineas.erase(lineas.begin() + fila + 1);
        }
      } else {
        lineas.at(fila).erase(columna, bytes_del_caracter(lineas.at(fila), columna));
      }

    } else if (comando == '\n') {
      std::string nueva_linea = lineas.at(fila).substr(0, columna);
      lineas.insert(lineas.begin() + fila + 1, lineas.at(fila).substr(columna));
      lineas.at(fila) = nueva_linea;
      fila++;
      columna = 0;

    } else if (comando == CTRL('s')) {
      endwin();
      nombre_archivo_actual = save_file(lineas);
      initscr();
      raw();
      keypad(stdscr, TRUE);
      noecho();

    } else if (comando == CTRL('l')) {
      endwin();
      std::string nueva_eleccion = return_load_txt(files_in_directory());
      lineas = load_file(nueva_eleccion);
      nombre_archivo_actual = nueva_eleccion;
      fila = 0;
      columna = 0;
      initscr();
      raw();
      keypad(stdscr, TRUE);
      noecho();

    } else {
      lineas.at(fila).insert(columna, 1, comando);
      columna++;
    }

    show_frases(lineas, fila, columna, nombre_archivo_actual);
  }

  endwin();

  return 0;
}

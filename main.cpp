//#include <iostream>
#include <string>
#include <vector>
#include "archivo_io.h"
#define _XOPEN_SOURCE_EXTENDED
#include <ncurses.h>
#include <cwchar>
#include <locale.h>
#include "mensajes.h"

#define CTRL(x) ((x) & 0x1f)

// FUNCIONES PARA DIBUJAR LAS BARRAS INFERIOR Y SUPERIOR
// Barra inferior
void dibujar_barra_inferior(const std::string &texto) {
    size_t filas, columnas;
    getmaxyx(stdscr, filas, columnas);
    
    std::string contenido(columnas, ' ');
    contenido.replace(0, texto.length(), texto);
    
    attron(A_REVERSE);
    mvprintw(filas - 1, 0, "%s", contenido.c_str());
    attroff(A_REVERSE);
}

// Esto pide el nombre al guardar
std::string pedir_nombre_archivo() {
    std::string nombre;
    wint_t tecla;
    int tipo;
    
    do {
        dibujar_barra_inferior("Nombre del archivo a guardar: " + nombre);
        refresh();
        
        tipo = get_wch(&tecla);
        
        if (tecla == '\n') {
          if (!nombre.empty()) {
              break;
          } else {
              dibujar_barra_inferior("El nombre no puede estar vacío. Pulsa cualquier tecla para continuar.");
              refresh();
              get_wch(&tecla);
          }
        } else if (tecla == KEY_BACKSPACE && !nombre.empty()) {
            nombre.pop_back();
        } else if (tipo != KEY_CODE_YES) {
            nombre += (char)tecla;
        }
        
    } while (true);
    
    return nombre;
}

std::string guardar_documento(const std::vector<std::string> &lineas, std::string nombre_archivo_actual) {
    std::string nombre_final;
    
    if (nombre_archivo_actual == "Archivo en blanco.") {
        nombre_final = pedir_nombre_archivo();
        nombre_final += ".txt";
    } else {
        nombre_final = nombre_archivo_actual;
    }
    
    save_file(lineas, nombre_final);
    
    return nombre_final;
}

// FUNCIONES PARA EL CHEQUEO DE LOS CARACTERES ESPECIALES
// Estas funcionmes sirven para comprobar el tamaño de bytes de un caracter, un rollo 
std::string codificar_utf8(int numero) {
    unsigned char byte1 = 0xC0 | (numero >> 6);
    unsigned char byte2 = 0x80 | (numero & 0x3F);
    
    std::string resultado;
    resultado += byte1;
    resultado += byte2;
    
    return resultado;
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

int columna_visual(const std::string &texto, size_t columna_bytes) {
    int visual = 0;
    size_t i = 0;
    while (i < columna_bytes) {
        i += bytes_del_caracter(texto, i);
        visual++;
    }
    return visual;
}

// Funcion con la que muestro todos los textos en pantalla con el cursor.
void show_frases(const std::vector<std::string> &lineas, int fila,
                 int columna, std::string nombre_archivo, std::string mensaje_estado, bool modificado) {
  clear();
  
  std::string name_program = "Write Something Nice";
  std::string texto_barra = name_program + " - " + nombre_archivo;

  size_t filas, columnas;
  
  if (modificado) {
    texto_barra += " *";
  }
  
  getmaxyx(stdscr, filas, columnas);

  std::string relleno((columnas - texto_barra.length())/2, ' ');
  std::string relleno_2(columnas - texto_barra.length() - relleno.length(), ' ');
  std::string fila_superior = relleno + texto_barra + relleno_2;
  std::string fila_inferior = std::string(columnas, ' ');


  attron(A_REVERSE);
  mvprintw(0, 0, "%s", fila_superior.c_str());
  dibujar_barra_inferior(mensaje_estado);
  attroff(A_REVERSE);

  for (size_t i = 0; i < lineas.size(); i++) {
    mvprintw(i+2, 0, "%s", lineas.at(i).c_str());
  }

  move(fila+2, columna_visual(lineas.at(fila), columna));
  refresh();
}


// Main function donde introduzco letras y muevo el cursor con las teclas 'd/i/w/s'
int main() {
  
  // esto es un resto de la prueba de carga, solo provisional
  std::string nombre_archivo_actual = return_load_txt(files_in_directory());
  
  std::vector<std::string> lineas;
  
  lineas = load_file(nombre_archivo_actual);
  
  int fila = 0;
  int columna = 0;
  
  wint_t comando = ' ';
  int tipo;

  bool modificado = false;

  setlocale(LC_ALL, "");
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  
  show_frases(lineas, fila, columna, nombre_archivo_actual,"", modificado);

  while (comando != CTRL('q')) {

    std::string frase_final = "";

    tipo = get_wch(&comando);

    if (tipo == KEY_CODE_YES) {

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
            modificado = true;

          } else {
            if (fila > 0) {
              size_t longitud = lineas.at(fila - 1).length();
              lineas.at(fila - 1) += lineas.at(fila);
              lineas.erase(lineas.begin() + fila);
              fila--;
              columna = longitud;
              modificado = true;
            }
          }

      } else if (comando == KEY_DC) {

        if (columna == lineas.at(fila).length()) {
          if (fila < lineas.size() - 1) {
            lineas.at(fila) += lineas.at(fila + 1);
            lineas.erase(lineas.begin() + fila + 1);
            modificado = true;
          }
        } else {
          lineas.at(fila).erase(columna, bytes_del_caracter(lineas.at(fila), columna));
          modificado = true;
        }

      } 

    } else {
      if (comando == '\n') {
        std::string nueva_linea = lineas.at(fila).substr(0, columna);
        lineas.insert(lineas.begin() + fila + 1, lineas.at(fila).substr(columna));
        lineas.at(fila) = nueva_linea;
        fila++;
        columna = 0;
        modificado = true;

      } else if (comando == CTRL('s')) {
        nombre_archivo_actual = guardar_documento(lineas,nombre_archivo_actual);
        modificado = false;

      } else if (comando == CTRL('l')) {
        endwin();
        std::string nueva_eleccion = return_load_txt(files_in_directory());
        lineas = load_file(nueva_eleccion);
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        nombre_archivo_actual = nueva_eleccion;
        fila = 0;
        columna = 0;
        modificado = false;


      } else if (comando == CTRL('q')) {
          if (modificado) {
            dibujar_barra_inferior("¿Quieres guardar los cambios realizados antes de salir? (S/N)");
            refresh();
            
            wint_t respuesta;
            get_wch(&respuesta);
            
            while (respuesta != 's' && respuesta != 'n') {
              get_wch(&respuesta);
            } 

            if (respuesta == 's') {
              nombre_archivo_actual = guardar_documento(lineas,nombre_archivo_actual);
            }
          }

        } else {
          std::string texto_a_insertar;
          if (comando < 128) {
            texto_a_insertar += (char)comando;
          } else {
            texto_a_insertar = codificar_utf8((int)comando);
          }
          lineas.at(fila).insert(columna, texto_a_insertar);
          columna += texto_a_insertar.length();
          modificado = true;
          frase_final = mensaje_aleatorio(texto_a_insertar); 
        }
    } 

    show_frases(lineas, fila, columna, nombre_archivo_actual, frase_final, modificado);
  }

  endwin();

  return 0;
}

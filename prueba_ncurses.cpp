#define _XOPEN_SOURCE_EXTENDED
#include <ncurses.h>
#include <cwchar>
#include <locale.h>
#include <string>

#define CTRL(x) ((x) & 0x1f)

std::string codificar_utf8(int numero) {
    unsigned char byte1 = 0xC0 | (numero >> 6);
    unsigned char byte2 = 0x80 | (numero & 0x3F);
    
    std::string resultado;
    resultado += byte1;
    resultado += byte2;
    
    return resultado;
}

int main() {
    setlocale(LC_ALL, "");
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    wint_t tecla;
    int tipo;

    do {
        tipo = get_wch(&tecla);

        if (tipo == KEY_CODE_YES) {
            if (tecla == KEY_RIGHT) {
                mvprintw(0, 0, "Flecha derecha detectada!          ");
            }
        } else {
            std::string codificado = codificar_utf8((int)tecla);
            mvprintw(0, 0, "Codigo: %d - Caracter codificado: %s          ", (int)tecla, codificado.c_str());
        }

        refresh();

    } while (tecla != CTRL('q'));

    endwin();
    return 0;
}
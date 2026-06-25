#define _XOPEN_SOURCE_EXTENDED
#include <ncurses.h>
#include <cwchar>
#include <locale.h>

#define CTRL(x) ((x) & 0x1f)

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
            mvprintw(0, 0, "Caracter normal, codigo: %d          ", (int)tecla);
        }

        refresh();

    } while (tecla != CTRL('q'));

    endwin();
    return 0;
}
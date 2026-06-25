#include <ncurses.h>
#include <iostream>
#include <string>

#define CTRL(x) ((x) & 0x1f)

int main() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int tecla;

    do {
        tecla = getch();
        mvprintw(0, 0, "Has pulsado: %c (codigo %d)          ", tecla, tecla);

        unsigned char byte = tecla;
        if ((byte & 0xE0) == 0xC0) {
            mvprintw(1,0,"%c Es un caracter especial.", tecla);
            refresh();
        } else {
            mvprintw(1,0,"%c Es un caracter normal.", tecla);
            refresh();
        }

    } while (tecla != CTRL('q'));

    endwin();
    return 0;
}
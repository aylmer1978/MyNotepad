#include "ncurses.h"
#define CTRL(x) ((x) & 0x1f)

int main() {

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int tecla;
    
    
    do {
        tecla = getch();
        if (tecla == CTRL('s')) {
            mvprintw(2, 0, "Ctrl+S detectado! codigo: %d", tecla);
        } else  if (tecla == CTRL('q')) {
            mvprintw(2, 0, "Ctrl+Q detectado! codigo: %d", tecla);
        } else {
            mvprintw(2, 0, "                                        "); // borra el mensaje anterior, línea de espacios
        }
        mvprintw(0,0, "Has pulsado: %c (codigo %d)", tecla, tecla);
        refresh();
    } while (tecla != 'q');

    endwin(); 
    return 0;
}
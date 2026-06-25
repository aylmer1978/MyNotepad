#include <iostream>
#include <string>
#include "ncurses.h"

int main() {
    initscr();

    size_t filas, columnas;

    getmaxyx(stdscr, filas, columnas);

    std::string name_program = "Write Something Nice";
    
    std::string relleno((columnas - name_program.length())/2, ' ');
    std::string relleno_2(columnas - name_program.length() - relleno.length(), ' ');
    std::string fila_superior = relleno + name_program + relleno_2;
    
    attron(A_REVERSE);
    mvprintw(0,0,"%s",fila_superior.c_str());
    attroff(A_REVERSE);

    mvprintw(2,0,"Esta es una linea normal");

    refresh();
    getch();
    endwin();

    return 0;
}
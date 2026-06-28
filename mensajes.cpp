#include <iostream>
#include <string>
#include <random>
#include <vector>

std::string mensaje_aleatorio(const std::string &letra) {
    static std::random_device rd;
    static std::mt19937 generador(rd());
    
    std::vector<std::string> plantillas = {
        "Has escrito una maravillosa " + letra + ".",
        "Una " + letra + " es justo lo que el mundo necesitaba.",
        "Sigue escribiendo, va genial.",
        "Contador secreto: alguien escribió " + letra + " y nadie se dio cuenta.",
        "Honestamente, la " + letra + " está sobrevalorada.",
        "Vaya " + letra + " más bonita te ha quedado",
        "Creo que la " + letra + " es la letra más bonita del mundo.",
        "Si repites muchas veces la " + letra + " te sale una novela estupenda.",
        " " + letra + " " + letra + " " + letra + " " + letra + " " + 
            letra + " " + letra + " " + letra + " " + letra + " " + letra + " " + letra + " " + letra + " " + letra + " " + letra + " " + letra,
    };
    
    std::uniform_int_distribution<size_t> distribucion(0, plantillas.size() - 1);
    return plantillas.at(distribucion(generador));
}
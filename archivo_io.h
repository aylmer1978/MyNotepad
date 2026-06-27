#include <string>
#include <vector>

std::vector<std::string> files_in_directory();

std::string return_load_txt(std::vector<std::string> archivos);

void save_file(const std::vector<std::string> &frases, std::string name_file);

std::vector<std::string> load_file(std::string name_file);
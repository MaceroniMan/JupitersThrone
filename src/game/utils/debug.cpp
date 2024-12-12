#include "debug.h"
#include <iomanip>
#include <iostream>

void JupThrUtils::log(std::string catagory, std::string text) {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    std::cout << "JupitersThrone [" << std::put_time(&tm, "%c")  << "] " << catagory << ": " << text << std::endl;
};

void JupThrUtils::log(std::string text) {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    std::cout << "JupitersThrone [" << std::put_time(&tm, "%c") << "] default: " << text << std::endl;
};

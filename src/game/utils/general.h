#ifndef GENERAL_H
#define GENERAL_H

#include <string>

namespace JupThrUtils {
struct Pos {
    int x;
    int y;
};

void replaceAll(std::string& s, std::string const& toReplace, std::string const& replaceWith);

} // namespace Utils

#endif // GENERAL_H

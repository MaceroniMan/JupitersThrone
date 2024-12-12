#ifndef COLORS_H
#define COLORS_H
#include <string>

namespace JupThrGraphics {
class Colors;
} // namespace Graphics

class JupThrGraphics::Colors
{
public:
    static std::string Red(std::string text);
    static std::string Blue(std::string text);
    static std::string Green(std::string text);
    static std::string Aqua(std::string text);
    static std::string Purple(std::string text);
    static std::string Yellow(std::string text);
    static std::string White(std::string text);

    static std::string Italic(std::string text);
    static std::string Underline(std::string text);
    static std::string Bold(std::string text);

    static std::string Newline();

    static std::string renderToHtml(std::string);
};

#endif // COLORS_H

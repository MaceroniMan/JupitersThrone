#include "colors.h"
#include "general.h"

std::string JupThrGraphics::Colors::Red(std::string text) {
    return "R;{" + text + "}";
};
std::string JupThrGraphics::Colors::Blue(std::string text) {
    return "B;{" + text + "}";
};
std::string JupThrGraphics::Colors::Green(std::string text) {
    return "G;{" + text + "}";
};
std::string JupThrGraphics::Colors::Aqua(std::string text) {
    return "A;{" + text + "}";
};
std::string JupThrGraphics::Colors::Purple(std::string text) {
    return "P;{" + text + "}";
};
std::string JupThrGraphics::Colors::Yellow(std::string text) {
    return "Y;{" + text + "}";
};
std::string JupThrGraphics::Colors::White(std::string text) {
    return "W;{" + text + "}";
};

std::string JupThrGraphics::Colors::Italic(std::string text) {
    return "I;{" + text + "}";
};
std::string JupThrGraphics::Colors::Underline(std::string text) {
    return "U;{" + text + "}";
};
std::string JupThrGraphics::Colors::Bold(std::string text) {
    return "S;{" + text + "}";
};

std::string JupThrGraphics::Colors::Newline() {
    return "N;";
};

std::string JupThrGraphics::Colors::renderToHtml(std::string text) {
    JupThrUtils::replaceAll(text, "B;{", "<span style=\"color:blue;\">");
    JupThrUtils::replaceAll(text, "G;{", "<span style=\"color:green;\">");
    JupThrUtils::replaceAll(text, "A;{", "<span style=\"color:aqua;\">");
    JupThrUtils::replaceAll(text, "R;{", "<span style=\"color:red;\">");
    JupThrUtils::replaceAll(text, "P;{", "<span style=\"color:purple;\">");
    JupThrUtils::replaceAll(text, "Y;{", "<span style=\"color:yellow;\">");
    JupThrUtils::replaceAll(text, "W;{", "<span style=\"color:white;\">");

    JupThrUtils::replaceAll(text, "I;{", "<span style=\"font-style: italic;\">");
    JupThrUtils::replaceAll(text, "U;{", "<span style=\"text-decoration: underline;\">");
    JupThrUtils::replaceAll(text, "S;{", "<span style=\"font-weight: bold;\">");

    JupThrUtils::replaceAll(text, "N;", "<br/>");
    JupThrUtils::replaceAll(text, "}", "</span>");

    return text;
}

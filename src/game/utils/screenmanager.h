#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <mutex>
#include <string>
#include <vector>
#include <functional>
#include <map>

#include "general.h"

namespace JupThrGraphics {
class ScreenManager;
} // namespace Graphics

class JupThrGraphics::ScreenManager
{
public:
    ScreenManager();

    void updateLines(std::vector<std::string> lines);
    void print(std::string content, JupThrUtils::Pos position);

    void alert(std::string message);
    bool confirm(std::string message);
    std::string prompt(std::string message);

    void frozen(bool freeze = true);

    std::string createLink(std::string content, std::string id, std::function<void (std::string)> callback);

private:
    void draw();
    std::string parse(std::string input);

    bool is_frozen;

    std::map<std::string, std::function<void (std::string)>> link_callbacks;
    std::mutex link_callbacks_mutex;

    std::vector<std::string> lines;
    std::mutex lines_mutex;
};

#endif // SCREENMANAGER_H

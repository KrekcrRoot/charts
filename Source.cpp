#include <Charts.h>

int main() {

    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 16;

    Config cfg {
        "Charts",
        sf::VideoMode(1900, 1000),
        contextSettings,
        sf::Color::White,
        sf::Color(230, 230, 230),
        sf::Color(31, 184, 240),
        1,
        false
    };

    std::shared_ptr<Window> window = std::make_shared<Window>(cfg);
    window->init();

    return 0;
}

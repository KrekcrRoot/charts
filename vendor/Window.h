//
// Created by xenon on 21.04.23.
//

#ifndef CHARTS_WINDOW_H
#define CHARTS_WINDOW_H

#include <SFML/Graphics.hpp>
#include <Config.h>
#include <Log.h>
#include <Camera.h>
#include <memory>

class Window {

public:

    explicit Window(const Config& cfg);
    void init();

protected:

    void tick();
    void eventListener(const sf::Event& event);
    void renderCharts();
    void loadFont();
    float getCellSize();

    std::shared_ptr<sf::RenderWindow> renderWindow;
    std::shared_ptr<Camera> camera;

    const sf::Color background, axesColor, chartsColor;
    float cellSize;
    sf::Vector2f lastMousePos;
    sf::Font font;
    const bool trigonometry;

};


#endif //CHARTS_WINDOW_H

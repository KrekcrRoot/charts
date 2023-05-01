//
// Created by xenon on 22.04.23.
//

#ifndef CHARTS_CONFIG_H
#define CHARTS_CONFIG_H

#include <string>
#include <SFML/Graphics.hpp>


struct Config {

    const std::string& title;
    const sf::VideoMode videoMode;
    const sf::ContextSettings settings;
    const sf::Color backgroundColor;
    const sf::Color axesColor;
    const sf::Color chartsColor;
    const float cellSize;
    const bool trigonometry = false;

};


#endif //CHARTS_CONFIG_H

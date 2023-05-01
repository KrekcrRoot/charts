//
// Created by xenon on 22.04.23.
//

#ifndef CHARTS_CAMERA_H
#define CHARTS_CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {

public:

    Camera();
    Camera(sf::Vector2f _position, float _scale);

    [[nodiscard]] sf::Vector2f getPosition() const;
    sf::Vector2f getRawPosition();
    [[nodiscard]] float getScale() const;
    [[nodiscard]] bool isDragged() const;

    void setPosition(float _x, float _y);
    void setPosition(sf::Vector2f _position);
    void setDragged(bool _dragged);
    void setScale(float _scale);

    void addScaleImpulse(float _scale);
    void addImpulse(float _x, float _y);
    void tick();

protected:

    float x{}, y{}, scale{};
    bool dragged = false;
    float accX{}, accY{}, accScale{};

};


#endif //CHARTS_CAMERA_H

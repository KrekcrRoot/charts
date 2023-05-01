//
// Created by xenon on 22.04.23.
//

#include "Camera.h"


Camera::Camera() = default;

Camera::Camera(sf::Vector2f _position, float _scale) {
    this->x = _position.x;
    this->y = _position.y;
    this->scale = _scale;
}


sf::Vector2f Camera::getPosition() const {
    return {
        this->x * this->scale,
        this->y * this->scale
    };
}

float Camera::getScale() const {
    return this->scale;
}

bool Camera::isDragged() const {
    return this->dragged;
}


void Camera::setPosition(float _x, float _y) {
    this->x = _x;
    this->y = _y;
}

void Camera::setPosition(sf::Vector2f _position) {
    this->x = _position.x;
    this->y = _position.y;
}

void Camera::setDragged(bool _dragged) {
    this->dragged = _dragged;
}

void Camera::setScale(float _scale) {
    this->scale = _scale;
}

sf::Vector2f Camera::getRawPosition() {
    return {
        this->x,
        this->y
    };
}

void Camera::addImpulse(float _x, float _y) {

    this->accX += _x;
    this->accY += _y;

}

void Camera::addScaleImpulse(float _scale) {

    if(abs(this->accScale) < 10)
        this->accScale += _scale;

}

void Camera::tick() {

    this->x += this->accX;
    this->y += this->accY;
    this->scale += this->accScale;

    this->accX *= 0.9;
    this->accY *= 0.9;
    this->accScale *= 0.8;

    if(this->scale < 5) this->scale = 5;
    else if(this->scale > 500) this->scale = 500;

}
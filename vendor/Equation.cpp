//
// Created by xenon on 22.04.23.
//

#include "Equation.h"

Equation::Equation(const std::string &_equation): raw(_equation)
{

}

std::string Equation::getRaw() {
    return this->raw;
}

float Equation::calculate() {

}
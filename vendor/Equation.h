//
// Created by xenon on 22.04.23.
//

#ifndef CHARTS_EQUATION_H
#define CHARTS_EQUATION_H

#include <string>
#include <functional>

struct Equation {

    explicit Equation(const std::string& _equation);

    std::string getRaw();
    float calculate();



protected:

    const std::string &raw;

};


#endif //CHARTS_EQUATION_H

//
// Created by xenon on 21.04.23.
//

#ifndef CHARTS_LOG_H
#define CHARTS_LOG_H

#include <iostream>
#include <string>

class Log {


public:


    template<typename T>
    static void raw(const T& data) {
        std::cout << data;
    }

    template<typename T>
    static void line(const T& data) {
        Log::raw(data);
        std::cout << std::endl;
    }

    template<typename T>
    static void errl(const T& data) {
        std::cerr << data << std::endl;
    }

    explicit Log(const std::string& _name);
    ~Log();


protected:

    std::string getLogName();

    const std::string& name;

};


#endif //CHARTS_LOG_H

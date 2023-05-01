//
// Created by xenon on 21.04.23.
//

#include "Log.h"

Log::Log(const std::string &_name) : name(_name) {

}

Log::~Log() {
    Log::line(this->getLogName() + "destruct log");
}

std::string Log::getLogName() {

    return "[" + this->name + "] - ";

}
//
// Created by Jean-Luc Thumm on 7/24/17.
//

#ifndef STEREO_READER_CORRELATION_H
#define STEREO_READER_CORRELATION_H

#include <string>

class Correlation {
public:
    std::string prefix;
    double s_angle;
    double o_angle;

    Correlation(std::string &prefix, double s_angle, double o_angle)
            : prefix{prefix}, s_angle{s_angle}, o_angle{o_angle} {}

    double diff() { return s_angle - o_angle; }
};

#endif //STEREO_READER_CORRELATION_H

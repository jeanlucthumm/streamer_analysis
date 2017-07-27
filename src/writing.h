//
// Created by Jean-Luc Thumm on 7/27/17.
//

#ifndef STEREO_READER_WRITING_H
#define STEREO_READER_WRITING_H

#include <fstream>
#include <vector>
#include "Correlation.h"

namespace writing {
    void write_angle_diff(std::ofstream &out, const std::vector<Correlation> &data);

    void write_angle(std::ofstream &out, const std::vector<Correlation> &data);

    void write_diff(std::ofstream &out, const std::vector<Correlation> &data);
};


#endif //STEREO_READER_WRITING_H

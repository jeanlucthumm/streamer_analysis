//
// Created by Jean-Luc Thumm on 7/20/17.
//

#ifndef STEREO_READER_NAMEPROCESSOR_H
#define STEREO_READER_NAMEPROCESSOR_H

#include <boost/filesystem/path.hpp>
#include <vector>
#include <string>
#include "Correlation.h"
#include "ImageData.h"

#define OBS "-o"
#define SIM "-s"

namespace processing {
    boost::filesystem::path get_pair(boost::filesystem::path name);

    std::string get_prefix(const boost::filesystem::path &name);

    bool isObserved(const boost::filesystem::path &name);

    bool isSimulated(const boost::filesystem::path &name);

    std::vector<Correlation>
    compute_correlations(std::vector<std::pair<ImageData, ImageData>> &data_table);
};


#endif //STEREO_READER_NAMEPROCESSOR_H

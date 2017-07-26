//
// Created by Jean-Luc Thumm on 7/20/17.
//

#include "processing.h"
#include <boost/algorithm/string.hpp>

using namespace std;
using boost::filesystem::path;

boost::filesystem::path processing::get_pair(boost::filesystem::path name) {
    if (isObserved(name)) {
        string name_str = name.string();
        boost::replace_last(name_str, OBS, SIM);
        return path{name_str};
    } else if (isSimulated(name)) {
        string name_str = name.string();
        boost::replace_last(name_str, SIM, OBS);
        return path{name_str};
    } else {
        throw runtime_error("could not find pair for image: " + name.string());
    }
}

std::string processing::get_prefix(const boost::filesystem::path &name) {
    string stem = name.stem().string();

    vector<string> parts;
    boost::split(parts, stem, boost::is_any_of("-"));
    if (parts.size() != 2) {
        throw runtime_error("could not find prefix for image: " + name.string());
    }

    return parts[0];
}

bool processing::isObserved(const boost::filesystem::path &name) {
    return boost::contains(name.stem().string(), OBS);
}

bool processing::isSimulated(const boost::filesystem::path &name) {
    return boost::contains(name.stem().string(), SIM);
}

double processing::compute_angle(cv::Point point, cv::Point center) {
    double deltaX = point.x - center.x; // keep in mind openCV has 0,0 at top left
    double deltaY = point.y - center.y;

    if (deltaX == 0) {
        if (deltaY < 0) {
            return M_PI / 2;
        } else if (deltaY > 0) {
            return -M_PI / 2;
        } else {
            return 0;
        }
    }

    double arc = abs(atan(deltaY / deltaX));
    if (deltaY < 0) { // above origin
        return arc;
    } else if (deltaY > 0) {
        return -arc;
    } else {
        return 0;
    }
}

bool processing::validate_image_pair(ImageData &first, ImageData &second) {
    return first.streamer_clicks.size() == second.streamer_clicks.size() &&
            get_prefix(first.image_path) == get_prefix(second.image_path);
}


std::vector<Correlation>
processing::compute_correlations(std::vector<std::pair<ImageData, ImageData>> &data_table) {
    vector<Correlation> correlations;

    for (auto &entry : data_table) {
        ImageData &data1 = entry.first;
        ImageData &data2 = entry.second;

        // correlations map to same index in each vector -> must be same size
        string prefix = get_prefix(data1.image_path);
        if (data1.streamer_clicks.size() != data2.streamer_clicks.size() ||
            prefix != get_prefix(data2.image_path)) {
            throw runtime_error("found incompatible ImageData while computing correlations");
        }

        for (int i = 0; i < data1.streamer_clicks.size(); i++) {
            double angle1 = processing::compute_angle(data1.streamer_clicks[i], data1.center);
            double angle2 = processing::compute_angle(data2.streamer_clicks[i], data2.center);
            correlations.emplace_back(prefix, angle1, angle2);
        }
    }

    return correlations;
}


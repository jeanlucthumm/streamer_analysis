//
// Created by Jean-Luc Thumm on 7/18/17.
//

#ifndef STEREO_READER_IMAGE_H
#define STEREO_READER_IMAGE_H


#include <string>
#include <opencv2/core/mat.hpp>
#include <boost/filesystem/path.hpp>

class ImageData {
public:
    boost::filesystem::path image_path;
    std::string window_title;
    cv::Mat matrix;
    cv::Point center;
    std::vector<cv::Point> streamer_clicks;
    
    bool operator==(const ImageData &other) {
        return image_path == other.image_path;
    }
    
    bool operator!=(const ImageData &other) {
        return !(*this == other);
    }
};


#endif //STEREO_READER_IMAGE_H

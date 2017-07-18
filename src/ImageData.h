//
// Created by Jean-Luc Thumm on 7/18/17.
//

#ifndef STEREO_READER_IMAGE_H
#define STEREO_READER_IMAGE_H


#include <string>
#include <opencv2/core/mat.hpp>

class ImageData {
public:
    std::string path;
    std::string window_title;
    cv::Mat matrix;
    cv::Point center;
};


#endif //STEREO_READER_IMAGE_H

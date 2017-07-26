//
// Created by Jean-Luc Thumm on 7/26/17.
//

#ifndef STEREO_READER_IMAGEDATATEST_H
#define STEREO_READER_IMAGEDATATEST_H

#include <gtest/gtest.h>
#include "../src/ImageData.h"

TEST(ImageData, equality) {
    ImageData a, b;
    a.image_path = "data/image1.jpg";
    b.image_path = "data/image1.jpg";
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    
    b.image_path = "data/image2.jpg";
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

#endif //STEREO_READER_IMAGEDATATEST_H

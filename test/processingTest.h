//
// Created by Jean-Luc Thumm on 7/25/17.
//

#ifndef STEREO_READER_PROCESSINGTEST_H
#define STEREO_READER_PROCESSINGTEST_H

#include <gtest/gtest.h>
#include "../src/processing.h"

TEST(processing, get_pair) {
    EXPECT_EQ(processing::get_pair("a-s.jpg"), "a-o.jpg");
    EXPECT_EQ(processing::get_pair("data/a-s.jpg"), "data/a-o.jpg");

    EXPECT_EQ(processing::get_pair("a-o.jpg"), "a-s.jpg");
    EXPECT_EQ(processing::get_pair("data/a-o.jpg"), "data/a-s.jpg");

    ASSERT_THROW(processing::get_pair("fail"), std::runtime_error);
    ASSERT_THROW(processing::get_pair("data/fail"), std::runtime_error);
}

TEST(processing, get_prefix) {
    EXPECT_EQ(processing::get_prefix("a-s.jpg"), "a");
    EXPECT_EQ(processing::get_prefix("sdf-o.jpg"), "sdf");
    EXPECT_EQ(processing::get_prefix("hello_333-o.jpg"), "hello_333");
    EXPECT_EQ(processing::get_prefix("data/jean/hello_333-o.jpg"), "hello_333");

    ASSERT_THROW(processing::get_prefix("aa"), std::runtime_error);
    ASSERT_THROW(processing::get_prefix("example.jpg"), std::runtime_error);
}

TEST(processing, isObserved) {
    EXPECT_TRUE(processing::isObserved("helo-o.jpg"));
    EXPECT_TRUE(processing::isObserved("dir/helo-o.jpg"));
    EXPECT_TRUE(processing::isObserved("/dir/asdf_22-o.jpg"));

    EXPECT_FALSE(processing::isObserved("helo-s.jpg"));
    EXPECT_FALSE(processing::isObserved("dir/helo-s.jpg"));
    EXPECT_FALSE(processing::isObserved("/dir/asdf_22-s.jpg"));
}

TEST(processing, isSimulated) {
    EXPECT_TRUE(processing::isSimulated("helo-s.jpg"));
    EXPECT_TRUE(processing::isSimulated("dir/helo-s.jpg"));
    EXPECT_TRUE(processing::isSimulated("/dir/asdf_22-s.jpg"));

    EXPECT_FALSE(processing::isSimulated("helo-o.jpg"));
    EXPECT_FALSE(processing::isSimulated("dir/helo-o.jpg"));
    EXPECT_FALSE(processing::isSimulated("/dir/asdf_22-o.jpg"));
}

TEST(processing, computeAngle) {
    cv::Point center{256, 256};

    // Edge cases
    EXPECT_DOUBLE_EQ(processing::compute_angle(cv::Point{12, 256}, center), 0);
    EXPECT_DOUBLE_EQ(processing::compute_angle(cv::Point{300, 256}, center), 0);
    EXPECT_DOUBLE_EQ(processing::compute_angle(cv::Point{256, 200}, center), M_PI / 2);
    EXPECT_DOUBLE_EQ(processing::compute_angle(cv::Point{256, 400}, center), -M_PI / 2);

    // 45 degree cases
    EXPECT_DOUBLE_EQ(processing::compute_angle(cv::Point{128, 128}, center), M_PI / 4);
    EXPECT_DOUBLE_EQ(processing::compute_angle(cv::Point{384, 128}, center), M_PI / 4);

    EXPECT_DOUBLE_EQ(processing::compute_angle(cv::Point{128, 384}, center), -M_PI / 4);
    EXPECT_DOUBLE_EQ(processing::compute_angle(cv::Point{384, 384}, center), -M_PI / 4);
}

#endif //STEREO_READER_PROCESSINGTEST_H

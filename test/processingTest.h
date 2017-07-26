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

TEST(processing, processing_isSimulated_Test) {
    EXPECT_TRUE(processing::isSimulated("helo-s.jpg"));
    EXPECT_TRUE(processing::isSimulated("dir/helo-s.jpg"));
    EXPECT_TRUE(processing::isSimulated("/dir/asdf_22-s.jpg"));

    EXPECT_FALSE(processing::isSimulated("helo-o.jpg"));
    EXPECT_FALSE(processing::isSimulated("dir/helo-o.jpg"));
    EXPECT_FALSE(processing::isSimulated("/dir/asdf_22-o.jpg"));
}


#endif //STEREO_READER_PROCESSINGTEST_H

#include "image.h"

#include <gtest/gtest.h>

TEST(Image, toIndex) {
    auto image = Image(5, 7);
    EXPECT_EQ(0u, image.toIndex(0,0));
    EXPECT_EQ(4u, image.toIndex(0,1));
    EXPECT_EQ(20u, image.toIndex(1,0));
    EXPECT_EQ(24u, image.toIndex(1,1));
    EXPECT_EQ(52u, image.toIndex(2,3));
    // TODO: Test out of range
}
#ifndef EQUATION_TEST_H
#define EQUATION_TEST_H

#include <gtest/gtest.h>

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>

extern "C" {
#include "equation.h"
}

TEST(equationTest, size0) {
    double root1, root2;
    ASSERT_EQ(equation(1, -1, 5, &root1, &root2), 0);
    ASSERT_DOUBLE_EQ(root1, 0.5);
    ASSERT_DOUBLE_EQ(roundf(root2 * 100) / 100, roundf(2.18 * 100) / 100);
}

TEST(equationTest, size1) {
    double root1, root2;
    ASSERT_EQ(equation(1, -4, 4, &root1, &root2), 1);
    ASSERT_DOUBLE_EQ(root1, 2);
}

TEST(equationTest, size2) {
    double root1, root2;
    ASSERT_EQ(equation(1, -4, 3, &root1, &root2), 2);
    ASSERT_DOUBLE_EQ(root1, 3);
    ASSERT_DOUBLE_EQ(root2, 1);
}

#endif // EQUATION_TEST_H

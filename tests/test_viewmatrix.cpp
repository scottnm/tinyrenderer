#include "../viewmatrix.hpp"
#include "gtest/gtest.h"

TEST(ViewMatrixTests, MatrixInitializationAssumption)
{
    // test that we understand the ordering of glm matrices :: column major?
    glm::mat4 m1 = { glm::vec4(1, 0, 0, 1),
                     glm::vec4(0, 1, 0, 0),
                     glm::vec4(0, 1, 1, 0),
                     glm::vec4(0, 0, 0, 1) };

    glm::mat4 m2 = {1, 0, 0, 1,
                    0, 1, 0, 0,
                    0, 1, 1, 0,
                    0, 0, 0, 1};

    EXPECT_EQ(m1, m2);
}

TEST(ViewMatrixTests, TestProjectionMatrix1)
{
    auto m = perspective_proj_xform(1);
    auto exp = glm::mat4(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, -1,
                         0, 0, 0, 1);
    EXPECT_EQ(m, exp);
}

TEST(ViewMatrixTests, TestProjectionMatrix2)
{
    auto m = perspective_proj_xform(4);
    auto exp = glm::mat4(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, -0.25,
                         0, 0, 0, 1);
    EXPECT_EQ(m, exp);
}

TEST(ViewMatrixTests, TestScreenspaceMatrix1)
{
    auto m = screenspace_xform(100, 100, 100, 100);
    auto exp = glm::mat4(50,  0, 0, 0,
                          0, 50, 0, 0,
                          0,  0, 1, 0,
                         50, 50, 0, 1);
    EXPECT_EQ(m, exp);
}

TEST(ViewMatrixTests, TestScreenspaceMatrix2)
{
    auto m = screenspace_xform(1920, 1080, 100, 100);
    auto exp = glm::mat4( 50,   0, 0, 0,
                           0,  50, 0, 0,
                           0,   0, 1, 0,
                         960, 540, 0, 1);
    EXPECT_EQ(m, exp);
}

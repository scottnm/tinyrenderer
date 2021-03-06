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

TEST(ViewMatrixTests, Retroproject)
{
    auto world_space_coords = glm::mat3x4(1.0f, 2.0f, 0.0f, 1.0f,
                                          1.0f, 2.0f, 1.0f, 5.0f/4,
                                          1.0f, 2.0f, -3.0f, 5.0f/8);
    auto exp_proj_coords = glm::mat3(1.0f, 2.0f, 0.0f,
                                     4.0f/5, 8.0f/5, 4.0f/5,
                                     8.0f/5, 16.0f/5, -24.0f/5);
    EXPECT_EQ(retroproject(world_space_coords), exp_proj_coords);
}

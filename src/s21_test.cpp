#include <gtest/gtest.h>

#include "Model/affine_strategy.h"
#include "Model/file_reader.h"
#include "Model/s21_matrix_oop.h"
#include "point.h"
#include <cmath>

TEST(AffineTransform, Move) {
    s21::Point p(1, 1, 1);
    s21::Point p1(1, 1, 1);
    s21::Point centralPoint(0, 0, 0);
    s21::AffineTranslate t(&centralPoint);
    auto res = t.Transform(p, p1);

    s21::Point exp(2.0, 2.0, 2.0);
    ASSERT_TRUE(fabs(res.x() - exp.x()) < 1e-6);
    ASSERT_TRUE(fabs(res.y() - exp.y()) < 1e-6);
    ASSERT_TRUE(fabs(res.z() - exp.z()) < 1e-6);
}

TEST(AffineTransform, Scale) {
    s21::Point p(1, 1, 1);
    s21::Point p1(2, 2, 2);
    s21::Point centralPoint(0, 0, 0);
    s21::AffineScale t(&centralPoint);
    auto res = t.Transform(p, p1);

    s21::Point exp(2.0, 2.0, 2.0);
    ASSERT_TRUE(fabs(res.x() - exp.x()) < 1e-6);
    ASSERT_TRUE(fabs(res.y() - exp.y()) < 1e-6);
    ASSERT_TRUE(fabs(res.z() - exp.z()) < 1e-6);
}

TEST(AffineTransform, Rotate) {
    s21::Point p(1, 1, 1);
    s21::Point p1(1, 1, 1);
    s21::Point centralPoint(0, 0, 0);
    s21::AffineRotate t(&centralPoint);
    auto res = t.Transform(p, p1);

    s21::Point exp(-0.094896, 1.270323, 1.173573);
    ASSERT_TRUE(fabs(res.x() - exp.x()) < 1e-6);
    ASSERT_TRUE(fabs(res.y() - exp.y()) < 1e-6);
    ASSERT_TRUE(fabs(res.z() - exp.z()) < 1e-6);
}

TEST(FileReader, Read) {
    s21::FileReader reader;
    reader.Read("Objects/test.obj");
    std::vector<s21::Point> expVert = {{1.000000, -1.000000, -1.000000}, {1.000000, -1.000000, 1.000000},
                                       {-1.000000, -1.000000, 1.000000}, {-1.000000, -1.000000, -1.000000},
                                       {1.000000, 1.000000, -0.999999},  {0.999999, 1.000000, 1.000001},
                                       {-1.000000, 1.000000, 1.000000},  {-1.000000, 1.000000, -1.000000}};
    std::vector<s21::Point> expVertTex = {
        {1.000000, 0.333333, 0.000000}, {1.000000, 0.666667, 0.000000}, {0.666667, 0.666667, 0.000000},
        {0.666667, 0.333333, 0.000000}, {0.666667, 0.000000, 0.000000}, {0.000000, 0.333333, 0.000000},
        {0.000000, 0.000000, 0.000000}, {0.333333, 0.000000, 0.000000}, {0.333333, 1.000000, 0.000000},
        {0.000000, 1.000000, 0.000000}, {0.000000, 0.666667, 0.000000}, {0.333333, 0.333333, 0.000000},
        {0.333333, 0.666667, 0.000000}, {1.000000, 0.000000, 0.000000}};
    std::vector<s21::Point> expVertNorm = {
        {0.000000, -1.000000, 0.000000}, {0.000000, 1.000000, 0.000000},    {1.000000, 0.000000, 0.000000},
        {-0.000000, 0.000000, 1.000000}, {-1.000000, -0.000000, -0.000000}, {0.000000, 0.000000, -1.000000}};
    auto resVert = reader.vertices();
    auto resVertTex = reader.verticeTextures();
    auto resVertNorm = reader.verticeNormals();

    for (size_t i = 0; i < resVert.size(); i++) {
        ASSERT_TRUE(fabs(resVert[i].x() - expVert[i].x()) < 1e-6);
        ASSERT_TRUE(fabs(resVert[i].y() - expVert[i].y()) < 1e-6);
        ASSERT_TRUE(fabs(resVert[i].z() - expVert[i].z()) < 1e-6);
    }

    for (size_t i = 0; i < resVertTex.size(); i++) {
        ASSERT_TRUE(fabs(resVertTex[i].x() - expVertTex[i].x()) < 1e-6);
        ASSERT_TRUE(fabs(resVertTex[i].y() - expVertTex[i].y()) < 1e-6);
        ASSERT_TRUE(fabs(resVertTex[i].z() - expVertTex[i].z()) < 1e-6);
    }

    for (size_t i = 0; i < resVertNorm.size(); i++) {
        ASSERT_TRUE(fabs(resVertNorm[i].x() - expVertNorm[i].x()) < 1e-6);
        ASSERT_TRUE(fabs(resVertNorm[i].y() - expVertNorm[i].y()) < 1e-6);
        ASSERT_TRUE(fabs(resVertNorm[i].z() - expVertNorm[i].z()) < 1e-6);
    }
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

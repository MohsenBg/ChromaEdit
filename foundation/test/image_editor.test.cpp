#include "include/image_editor.hpp"
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include<filesystem>
#include <cstdlib>

namespace fs = std::filesystem;
using std::vector;
using std::string;
using namespace ImageEditor;

struct ImageData {
    int width;
    int height;
    fs::path path;
    fs::path name;
    ImageData(int width, int height, fs::path path, fs::path name) :width(width), height(height), path(path), name(name) {};
};

class ImageEditorTest : public ::testing::Test {
public:
    const fs::path DIST_DIR = fs::current_path() / "dist";
    const fs::path OUT_DIR = DIST_DIR / "output";

    vector<ImageData> images{
        { 1920, 1080, ImageEditorTest::DIST_DIR, "image.png" },
        { 1080, 1920, ImageEditorTest::DIST_DIR, "image.jpg" },
        { 1080, 1080, ImageEditorTest::DIST_DIR, "image.bmp" },
        { 1000, 1080, ImageEditorTest::DIST_DIR, "image.tiff" },
        { 1000, 1920, ImageEditorTest::DIST_DIR, "image.webp" },
        { 1920, 1080, ImageEditorTest::DIST_DIR, "image.jpeg" },
    };

    bool make_image(fs::path directory, fs::path name, int width, int height) {
        const fs::path file_path = directory / name;
        cv::Mat black_image(width, height, CV_8UC1, cv::Scalar(rand() % 256));
        if (!make_directory(directory)) {
            std::cerr << "Error creating directory: " << directory << std::endl;
            return false;
        }

        if (!cv::imwrite(file_path.string(), black_image))
            return false;
        return true;
    }


    bool make_directory(fs::path dir) {
        if (fs::is_directory(dir))
            return true;
        if (!fs::exists(dir.parent_path())) {
            if (!make_directory(dir.parent_path()))
                return false;
        }
        return fs::create_directory(dir);
    }

protected:
    void SetUp() override {
        fs::create_directory("dist");
        for (const auto& _image : images) {
            if (!make_image(_image.path, _image.name, _image.width, _image.height)) {
                std::cerr << "Failed to make image" << _image.path / _image.name << std::endl;
                exit(1);
            };
        }
    }

    void TearDown() override {
        fs::remove_all(DIST_DIR);
    };
};

// Test reading a valid image
TEST_F(ImageEditorTest, ReadValidImage) {
    for (auto& _image : images) {
        Result<cv::Mat> image = read_image(_image.path / _image.name);
        EXPECT_EQ(image.status, Status::SUCCESS);
        EXPECT_FALSE(image.data.empty());
    }
}

// Test reading an invalid image
TEST_F(ImageEditorTest, ReadInvalidImage) {
    fs::path image_path = "invalid_path/test.jpg";
    Result<cv::Mat> image = read_image(image_path);
    EXPECT_EQ(image.status, Status::FAILURE);
    EXPECT_TRUE(image.data.empty());
}

// Test cropping a square image from the center
TEST_F(ImageEditorTest, CropSquareFromCenter) {
    for (auto& _image : images) {
        PivotRect pivot_rect(HorizontalPivot::CENTER, VerticalPivot::CENTER);
        crop_square(_image.path / _image.name, pivot_rect, OUT_DIR / _image.name);

        // Verify that the cropped image exists and has the expected size
        Result<cv::Mat> cropped_image = read_image(OUT_DIR / _image.name);
        EXPECT_EQ(cropped_image.status, Status::SUCCESS);
        EXPECT_FALSE(cropped_image.data.empty());
        EXPECT_EQ(cropped_image.data.cols, cropped_image.data.rows);
    }
}

// Test saving an image
TEST_F(ImageEditorTest, SaveImage) {
    for (auto& _image : images) {
        cv::Mat image(50, 50, CV_8UC3, cv::Scalar(255, 255, 255));
        fs::path output_path = OUT_DIR / _image.name;
        bool success = save_image(image, output_path);
        EXPECT_TRUE(success);
        // Verify that the saved image exists and has the expected size
        Result<cv::Mat> saved_image = read_image(output_path);
        EXPECT_EQ(saved_image.status, Status::SUCCESS);
        EXPECT_FALSE(saved_image.data.empty());
        EXPECT_EQ(saved_image.data.cols, image.cols);
        EXPECT_EQ(saved_image.data.rows, image.rows);
    }
}

// Test getting the horizontal crop region
TEST_F(ImageEditorTest, GetHorizontalCropRegion) {
    int width = 100;
    int crop_size = 50;
    RectHorizontal rect_left = get_horizontal_crop_region(width, HorizontalPivot::LEFT, crop_size);
    RectHorizontal rect_right = get_horizontal_crop_region(width, HorizontalPivot::RIGHT, crop_size);
    RectHorizontal rect_center = get_horizontal_crop_region(width, HorizontalPivot::CENTER, crop_size);

    EXPECT_EQ(rect_left.x, 0);
    EXPECT_EQ(rect_left.width, crop_size);
    EXPECT_EQ(rect_right.x, crop_size);
    EXPECT_EQ(rect_right.width, crop_size);
}

// Test getting the vertical crop region
TEST_F(ImageEditorTest, GetVerticalCropRegion) {
    int height = 100;
    int crop_size = 50;
    RectVertical rect_left = get_vertical_crop_region(height, VerticalPivot::TOP, crop_size);
    RectVertical rect_right = get_vertical_crop_region(height, VerticalPivot::BOTTOM, crop_size);
    RectVertical rect_center = get_vertical_crop_region(height, VerticalPivot::CENTER, crop_size);
    EXPECT_EQ(rect_left.y, 0);
    EXPECT_EQ(rect_left.height, crop_size);
    EXPECT_EQ(rect_right.y, crop_size);
    EXPECT_EQ(rect_right.height, crop_size);
}
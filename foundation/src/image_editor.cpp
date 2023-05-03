#include "include/image_editor.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace ImageEditor {
  namespace fs = std::filesystem;

  void DebugLog(RectHorizontal horizontal, RectVertical vertical);

  Result<cv::Mat> read_image(const fs::path& image_path) {
    cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
    if (image.empty()) {
      std::cerr << "Failed to read image file: " << image_path << std::endl;
      return Result(cv::Mat(), Status::FAILURE);
    }
    return Result(image, Status::SUCCESS);
  }

  // Save image by specific filename and path. If the path directory does not exist, it is created.
  // If an image with the same name already exists, it is overwritten.
  // Example arg output: /home/user/picture/image.jpg
  // Returns true on success, false otherwise.
  bool save_image(const cv::Mat& image, const fs::path& output) {
    fs::create_directory(output.parent_path());
    bool success = cv::imwrite(output, image);
    if (!success) {
      std::cerr << "Failed to write image file: " << output << std::endl;
      return false;
    }
    return true;
  }

  // Crop an image square at the specified path using the given horizontal and vertical pivots
  // The cropped image is saved to the specified path with the given file name.
  // Example usage: crop_square("/path/to/image.jpg", PivotRect(HorizontalPivot::CENTER, VerticalPivot::BOTTOM), "/path/to/cropped_image.jpg");
  void crop_square(const fs::path& image_path, const PivotRect& pivot_rect, const fs::path& output_path) {
    Result<cv::Mat> image = read_image(image_path);
    if (image.status == Status::FAILURE)
      return;

    int width = image.data.cols;
    int height = image.data.rows;
    int size = std::min(height, width);

    RectHorizontal rect_horizontal = get_horizontal_crop_region(width, pivot_rect.horizontal_pivot, width - size);
    RectVertical rect_vertical = get_vertical_crop_region(height, pivot_rect.vertical_pivot, height - size);

    // DebugLog(rect_horizontal, rect_vertical);

    cv::Mat cropped_image = image.data(cv::Rect(rect_horizontal.x, rect_vertical.y, rect_horizontal.width, rect_vertical.height));
    if (!save_image(cropped_image, output_path))
      std::cerr << "Failed to write image file: " << output_path << std::endl;
  }

  // Get the horizontal crop region based on the given pivot and crop size
  RectHorizontal get_horizontal_crop_region(int width, HorizontalPivot horizontal_pivot, int crop_size) {
    switch (horizontal_pivot) {
    case HorizontalPivot::LEFT:
      return RectHorizontal(0, width - crop_size);
    case HorizontalPivot::RIGHT:
      return RectHorizontal(crop_size, width - crop_size);
    default:
      int half_crop = crop_size / 2;
      int half_width = width / 2;
      return RectHorizontal(half_crop, width - crop_size);
    }
  }

  // Get the vertical crop region based on the given pivot and crop size
  RectVertical get_vertical_crop_region(int height, VerticalPivot vertical_pivot, int crop_size) {
    switch (vertical_pivot) {
    case VerticalPivot::TOP:
      return RectVertical(0, height - crop_size);
    case VerticalPivot::BOTTOM:
      return RectVertical(crop_size, height - crop_size);
    default:
      int half_crop = crop_size / 2;
      int half_height = height / 2;
      return RectVertical(half_crop, height - crop_size);
    }
  }


  // Converts a character to a HorizontalPivot enum value. If the character is not a valid option,
// it returns the default_pivot.
  HorizontalPivot char_to_horizontal_pivot(char c, HorizontalPivot default_pivot) {
    auto iter = horizontal_pivot_map.find(c);
    if (iter != horizontal_pivot_map.end()) {
      return iter->second;
    }
    // default value when the character is not found
    return default_pivot;
  }

  // Converts a character to a VerticalPivot enum value. If the character is not a valid option,
    // it returns the default_pivot.
  VerticalPivot char_to_vertical_pivot(char c, VerticalPivot default_pivot) {
    auto iter = vertical_pivot_map.find(c);
    if (iter != vertical_pivot_map.end()) {
      return iter->second;
    }
    // default value when the character is not found
    return default_pivot;
  };

  void DebugLog(RectHorizontal horizontal, RectVertical vertical) {
    std::cout << "horizontal:{\n"
      << "\tx:" << horizontal.x << "\n\twidth:" << horizontal.width
      << "\n}" << std::endl;

    std::cout << "vertical:{\n"
      << "\ty:" << vertical.y << "\n\theight:" << vertical.height << "\n}"
      << std::endl;
  }
} // namespace ImageEditor

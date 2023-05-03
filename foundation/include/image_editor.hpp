#ifndef IMAGE_EDITOR_HPP
#define IMAGE_EDITOR_HPP

#include <filesystem>
#include <opencv2/opencv.hpp>

namespace ImageEditor {
  namespace fs = std::filesystem;

  // An enum to represent vertical pivot options
  enum class VerticalPivot: char {
    TOP = 't',
    CENTER = 'c',
    BOTTOM = 'b',
  };

  // An enum to represent horizontal pivot options
  enum class HorizontalPivot: char {
    LEFT = 'l',
    CENTER = 'c',
    RIGHT = 'r',
  };


  static std::map<char, VerticalPivot> vertical_pivot_map = {
        {'t', VerticalPivot::TOP},
        {'c', VerticalPivot::CENTER},
        {'b', VerticalPivot::BOTTOM}
  };

  static std::map<char, HorizontalPivot> horizontal_pivot_map = {
       {'l', HorizontalPivot::LEFT},
       {'c', HorizontalPivot::CENTER},
       {'r', HorizontalPivot::RIGHT}
  };

  enum class Status {
    SUCCESS,
    FAILURE
  };

  template <typename T>
  struct Result {
    T data;
    Status status;

    Result(T data, Status status)
      : data(data), status(status) {
    }
  };

  // A structure to represent a rectangle crop region with pivot points
  struct PivotRect {
    HorizontalPivot horizontal_pivot;
    VerticalPivot vertical_pivot;

    PivotRect(HorizontalPivot horizontal_pivot = HorizontalPivot::CENTER,
      VerticalPivot vertical_pivot = VerticalPivot::CENTER)
      : horizontal_pivot(horizontal_pivot), vertical_pivot(vertical_pivot) {
    }
  };

  // A structure to represent a horizontal rectangle crop region
  struct RectHorizontal {
    int x;      // The x-coordinate of the top-left corner of the rectangle
    int width;  // The width of the rectangle

    RectHorizontal(int x = 0, int width = 0): x(x), width(width) {}
  };

  // A structure to represent a vertical rectangle crop region
  struct RectVertical {
    int y;       // The y-coordinate of the top-left corner of the rectangle
    int height;  // The height of the rectangle

    RectVertical(int y = 0, int height = 0): y(y), height(height) {}
  };

  // Read image by specific path if can't read it exit with code 1
  Result<cv::Mat> read_image(const fs::path& image_path);

  // Save image by specific filename and path. If the path directory does not exist, it is created.
  // If an image with the same name already exists, it is overwritten.
  // Example arg output: /home/user/picture/image.jpg
  // Returns true on success, false otherwise.
  bool save_image(const cv::Mat& image, const fs::path& output);

  // Crop an image square at the specified path using the given horizontal and vertical pivots
  // The cropped image is saved to the specified path with the given file name.
  // Example usage: crop_square("/path/to/image.jpg", PivotRect(HorizontalPivot::CENTER, VerticalPivot::BOTTOM), "/path/to/cropped_image.jpg");
  void crop_square(const fs::path& image_path, const PivotRect& pivot_rect, const fs::path& output_path);

  // Get the horizontal crop region based on the given pivot and crop size
  RectHorizontal get_horizontal_crop_region(int width, HorizontalPivot pivot, int crop_size);

  // Get the vertical crop region based on the given pivot and crop size
  RectVertical get_vertical_crop_region(int height, VerticalPivot pivot, int crop_size);

  // Converts a character to a HorizontalPivot enum value. If the character is not a valid option,
  // it returns the default_pivot.
  HorizontalPivot char_to_horizontal_pivot(char c, HorizontalPivot default_pivot = HorizontalPivot::CENTER);

  // Converts a character to a VerticalPivot enum value. If the character is not a valid option,
  // it returns the default_pivot.
  VerticalPivot char_to_vertical_pivot(char c, VerticalPivot default_pivot = VerticalPivot::CENTER);

} // namespace ImageEditor

#endif // IMAGE_EDITOR_HPP

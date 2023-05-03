#include "include/image_editor.hpp"
#include "include/reader.hpp"
#include <filesystem>
#include <iostream>

using ImageEditor::PivotRect;
namespace fs = std::filesystem;
int main() {
  std::string path = "/home/Bagheri/Pictures/Screenshots";
  const auto files = Reader::find_image_files(path);
  // std::cout << "in path: " << files[0] << std::endl;

  for (const auto& file : files) {
    const std::string file_name = Reader::get_file_name(file);
    std::size_t index = file_name.rfind('_');
    char ch_pivot;
    char cv_pivot;
    bool has_prefix = std::string::npos != index;
    if (has_prefix && file_name.length() >= index + 2) {
      ch_pivot = file_name.substr(index + 1, index + 2)[0];
    }

    if (has_prefix && file_name.length() >= index + 3) {
      cv_pivot = file_name.substr(index + 2, index + 3)[0];
    }
    auto horizontal_pivot = ImageEditor::char_to_horizontal_pivot(ch_pivot);
    auto vertical_pivot = ImageEditor::char_to_vertical_pivot(cv_pivot);
    fs::path output = "./output" / fs::path(file).filename();
    std::cout << "crop: " << file_name << std::endl;
    ImageEditor::crop_square(file, PivotRect(horizontal_pivot, vertical_pivot), output);
  }

  return 0;
}

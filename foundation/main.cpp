#include <iostream>
#include <filesystem>
#include "include/reader.hpp"


int main() {
  std::string path = "/home/Bagheri/Pictures";

  for (const auto& path : Reader::find_image_files(path)) {
    std::cout << path << std::endl;
  }

  return 0;
}

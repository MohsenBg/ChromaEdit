#include "include/reader.hpp"
#include <filesystem>
#include <iostream>
#include <vector>

namespace Reader {
  namespace fs = std::filesystem;
  using std::string;
  using std::vector;

  vector<fs::path> find_image_files(string path) {
    vector<fs::path> image_paths;
    for (const auto& entry : fs::directory_iterator(path)) {
      if (is_file_image(entry.path())) {
        image_paths.push_back(entry.path());
      }
    }
    return image_paths;
  }

  bool is_file_image(const string& path) {
    string file_type = get_file_type(path);
    bool file_exists = fs::exists(path);
    return file_exists && image_type_map.count(file_type);
  }

  string get_file_type(const string& path) {
    std::size_t index_last_dot = path.rfind(".");
    if (index_last_dot == string::npos) {
      return "";
    }
    string file_type = path.substr(index_last_dot + 1);
    for (char& c : file_type) {
      c = std::tolower(c);
    }
    return file_type;
  }

  string get_file_name(const string& path) {
    bool file_exists = fs::exists(path);
    if (!file_exists) {
      return "";
    }

    string name = fs::path(path).filename().string();
    std::size_t index_last_dot = name.rfind(".");
    auto index = index_last_dot == string::npos ? name.length() : index_last_dot;
    return name.substr(0, index);
  }
} // namespace Reader

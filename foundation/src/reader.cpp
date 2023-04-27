#include "include/reader.hpp"
#include <filesystem>
#include <iostream>
#include <vector>

namespace Reader {
  namespace fs = std::filesystem;
  using std::vector;
  using std::string;

  vector<fs::path> find_image_files(string path) {
    vector<fs::path> image_paths;
    for (const auto& entry : fs::directory_iterator(path)) {
      if (is_file_image(entry.path()))
        image_paths.push_back(entry.path());
    }
    return image_paths;
  }

  bool is_file_image(const string& path) {
    string file_type = get_file_type(path);
    bool file_exist = fs::status(path).type() != fs::file_type::not_found;
    return file_exist && image_type_map.count(file_type);
  };

  string get_file_type(const string& path) {
    std::size_t index_last_dot = path.rfind(".");
    if (index_last_dot == string::npos) {
      return "";
    }

    string file_type = path.substr(index_last_dot + 1);

    for (int i = 0; i < file_type.length(); i++) {
      file_type[i] = tolower(file_type[i]);
    }

    return  file_type;
  };


} // namespace Reader

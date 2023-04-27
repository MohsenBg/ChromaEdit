#ifndef READER_H
#define READER_H
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>

namespace Reader {
    namespace fs = std::filesystem;
    using std::vector;
    using std::string;
    using std::map;


    enum class ImageType { BMP, GIF, JPEG, PNG, TIFF, WEBP };

    static const map<string, ImageType> image_type_map = {
        {"bmp", ImageType::BMP},
        {"gif", ImageType::GIF},
        {"jpg", ImageType::JPEG},
        {"png", ImageType::PNG},
        {"tiff", ImageType::TIFF},
        {"webp", ImageType::WEBP}
    };


    // Given a directory path as an argument, return the paths of all image files
    // supported formats include BMP, GIF, JPEG, PNG, TIFF, and WebP
    vector<fs::path> find_image_files(string path);

    // Given a file path as an argument, return true if the file is an image
    // supported formats include BMP, GIF, JPEG, PNG, TIFF, and WebP
    bool is_file_image(const string& path);

    // Given a file path as an argument, return the file type
    // For example, doc/document.txt => txt, image/familyPhoto.jpg => jpg
    string get_file_type(const string& path);

} // namespace Reader

#endif

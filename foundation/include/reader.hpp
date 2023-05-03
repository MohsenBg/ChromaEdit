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

    // Enumeration of image file types
    enum class ImageType { BMP, GIF, JPEG, PNG, TIFF, WEBP };

    // Map of file extensions to image types
    static const map<string, ImageType> image_type_map = {
        {"bmp", ImageType::BMP},
        {"gif", ImageType::GIF},
        {"jpg", ImageType::JPEG},
        {"jpeg", ImageType::JPEG},
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

    // Given a file path as argument, return the file name
    // For example, doc/document.txt => document , image/familyPhoto.jpg => FamilyPhoto
    string get_file_name(const string& path);
} // namespace Reader

#endif

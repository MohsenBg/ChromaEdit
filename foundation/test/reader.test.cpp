#include <gtest/gtest.h>
#include "include/reader.hpp"
#include <fstream>
#include <algorithm>

using std::vector;
using std::endl;
using std::string;
namespace fs = std::filesystem;

class ReaderTest: public ::testing::Test {
public:
    const fs::path DIST_DIR = fs::current_path() / "dist";

    vector<fs::path> files = {
        "image.bmp",
        "image.gif",
        "image.jpg",
        "image.png",
        "image.tiff",
        "image.webp",
        "document.pdf",
        "archive.zip"
    };

    void make_file(fs::path directory, fs::path name) {
        const fs::path file_path = directory / name;
        std::ofstream file(file_path);
        if (!file)
            std::cerr << "Error creating file: " << file_path << std::endl;
        file.close();
    }
protected:
    void SetUp() override {
        fs::create_directory("dist");
        for (const auto& _file : files)
            make_file(ReaderTest::DIST_DIR, _file);
    }

    void TearDown() override {
        fs::remove_all(DIST_DIR);
    }
};

TEST_F(ReaderTest, FindImageFiles) {
    vector<fs::path> expected_image_paths{
        ReaderTest::DIST_DIR / "image.bmp",
            ReaderTest::DIST_DIR / "image.gif",
            ReaderTest::DIST_DIR / "image.jpg",
            ReaderTest::DIST_DIR / "image.png",
            ReaderTest::DIST_DIR / "image.tiff",
            ReaderTest::DIST_DIR / "image.webp",
    };

    vector<fs::path> image_paths = Reader::find_image_files(ReaderTest::DIST_DIR);

    // sort vectors 
    std::sort(expected_image_paths.begin(), expected_image_paths.end());
    std::sort(image_paths.begin(), image_paths.end());

    ASSERT_EQ(expected_image_paths.size(), image_paths.size());
    for (int i = 0; i < expected_image_paths.size(); i++) {
        ASSERT_EQ(expected_image_paths[i], image_paths[i]);
    }
}

TEST_F(ReaderTest, IsFileImage) {
    ASSERT_TRUE(Reader::is_file_image(ReaderTest::DIST_DIR / "image.jpg"));
    ASSERT_TRUE(Reader::is_file_image(ReaderTest::DIST_DIR / "image.png"));
    ASSERT_TRUE(Reader::is_file_image(ReaderTest::DIST_DIR / "image.bmp"));
    ASSERT_FALSE(Reader::is_file_image(ReaderTest::DIST_DIR / "document.pdf"));
    ASSERT_FALSE(Reader::is_file_image(ReaderTest::DIST_DIR / "archive.zip"));
}

TEST_F(ReaderTest, GetFileType) {
    ASSERT_EQ("jpg", Reader::get_file_type(ReaderTest::DIST_DIR / "image.jpg"));
    ASSERT_EQ("png", Reader::get_file_type(ReaderTest::DIST_DIR / "image.png"));
    ASSERT_EQ("bmp", Reader::get_file_type(ReaderTest::DIST_DIR / "image.bmp"));
    ASSERT_EQ("pdf", Reader::get_file_type(ReaderTest::DIST_DIR / "document.pdf"));
    ASSERT_EQ("zip", Reader::get_file_type(ReaderTest::DIST_DIR / "archive.zip"));
}

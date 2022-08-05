#ifndef SRC_MODEL_FILE_READER_H_
#define SRC_MODEL_FILE_READER_H_

#include <string>
#include <fstream>
#include <vector>
#include "surface.h"
#include "../point.h"

namespace s21 { class FileReader; }

class s21::FileReader final {
    using StringsFromObjFile = std::vector<std::string>;
    using Points = std::vector<Point>;
    using Surfaces = std::vector<Surface>;

 public:
    void Read(const std::string &filename);
    void ClearData();
    // Getters
    Points vertices();
    Points verticeNormals();
    Points verticeTextures();
    Surfaces faces();

 private:
    StringsFromObjFile vertices_;
    StringsFromObjFile normals_;
    StringsFromObjFile textures_;
    StringsFromObjFile faces_;

    void ParsingFile(std::ifstream &&input) noexcept;
    inline bool FindSubstring(const std::string &s, const std::string &substr);
    std::vector<Point> points(StringsFromObjFile &&vectorOfString) noexcept;
    int FindStartPositionOfString(const StringsFromObjFile &vectorOfString);
    Point GetPoint(const std::string &s);
    Surface GetSurface(const std::string &s);
    int GetNumberFromString(std::string &&s, size_t *index);
};

#endif  // SRC_MODEL_FILE_READER_H_

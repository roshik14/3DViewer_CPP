#include "file_reader.h"
#include <clocale>
#include <cctype>

using s21::FileReader;
using s21::Point;
using s21::Surface;

void FileReader::Read(const std::string &filename) {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::ifstream input(filename);
    if (!input) {
        throw std::invalid_argument("There is no such file");
    }
    ParsingFile(std::move(input));
}

void FileReader::ParsingFile(std::ifstream &&input) noexcept {
    for (std::string line; std::getline(input, line);) {
        if (line.size()) {
            if (FindSubstring(line, "v "))
                vertices_.push_back(std::move(line));
            else if (FindSubstring(line, "vn"))
                normals_.push_back(std::move(line));
            else if (FindSubstring(line, "vt"))
                textures_.push_back(std::move(line));
            else if (FindSubstring(line, "f "))
                faces_.push_back(std::move(line));
        }
    }
}

inline bool FileReader::FindSubstring(const std::string &s, const std::string &substr) {
    return !s.compare(0, 2, substr);
}

std::vector<Point> FileReader::vertices() {
    return points(std::move(vertices_));
}

std::vector<Point> FileReader::verticeNormals() {
    return points(std::move(normals_));
}

std::vector<Point> FileReader::verticeTextures() {
    return points(std::move(textures_));
}

std::vector<Point> FileReader::points(StringsFromObjFile &&vectorOfString) noexcept {
    Points points;
    int startPosition = FindStartPositionOfString(vectorOfString);
    for (auto itb = vectorOfString.begin(), ite = vectorOfString.end(); itb != ite; ++itb) {
        points.push_back(GetPoint(itb->substr(startPosition)));
    }
    return points;
}

int FileReader::FindStartPositionOfString(const StringsFromObjFile &vectorOfString) {
    int startPosition = 0;
    if (vectorOfString.size()) {
        const std::string &s = vectorOfString[0];
        for (size_t i = 0, end = s.length(); i != end; ++i) {
            if (s[i] == ' ')
                return i;
        }
    }
    return startPosition;
}

Point FileReader::GetPoint(const std::string &s) {
    size_t pos_x = 0;
    size_t pos_y = 0;
    size_t pos_z = 0;
    float x = std::stof(s, &pos_x);
    float y = std::stof(s.substr(pos_x), &pos_y);
    if (pos_x + pos_y < s.length()) {
        float z = std::stof(s.substr(pos_x + pos_y), &pos_z);
        return Point(x, y, z);
    }
    return Point(x, y);
}

std::vector<Surface> FileReader::faces() {
    std::vector<Surface> indices;
    int startPosition = FindStartPositionOfString(faces_);
    for (auto itb = faces_.begin(), ite = faces_.end(); itb != ite; ++itb) {
        indices.push_back(GetSurface(itb->substr(startPosition)));
    }
    return indices;
}

Surface FileReader::GetSurface(const std::string &s) {
    int queue = 1;
    Surface sf;
    for (size_t i = 0; i != s.size(); ++i) {
        if (s[i] == ' ') {
            queue = 1;
        } else if (s[i] != '/') {
            int value = 0;
            if (std::isdigit(s[i]) && queue == 1) {
                value = GetNumberFromString(s.substr(i), &i);
                sf.AddVertex(value - 1);
            } else if (std::isdigit(s[i]) && queue == 2) {
                value = GetNumberFromString(s.substr(i), &i);
                sf.AddTexture(value - 1);
            } else if (std::isdigit(s[i]) && queue == 3) {
                value = GetNumberFromString(s.substr(i), &i);
                sf.AddNormal(value - 1);
            }
            // value - 1: because indices start from 0
            queue += 1;
        }
    }
    return sf;
}

int FileReader::GetNumberFromString(std::string &&s, size_t *index) {
    size_t numLength = 0;
    int coord = std::stoi(s, &numLength);
    *index += numLength - 1;
    return coord;
}

void FileReader::ClearData() {
    vertices_.clear();
    normals_.clear();
    textures_.clear();
    faces_.clear();
}

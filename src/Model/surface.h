#ifndef SRC_MODEL_SURFACE_H_
#define SRC_MODEL_SURFACE_H_

#include <vector>
#include <string>

namespace s21 {
class Surface final {
    using Points = std::vector<int>;

 public:
    void AddVertex(const int &value) {
        vertices_.push_back(value);
    }
    void AddNormal(const int &value) {
        vNormals_.push_back(value);
    }
    void AddTexture(const int &value) {
        vTextures_.push_back(value);
    }
    // Getters
    Points vertices() const {
        return vertices_;
    }
    Points verticeNormals() const {
        return vNormals_;
    }
    Points verticeTextures() const {
        return vTextures_;
    }

 private:
    Points vertices_;
    Points vNormals_;
    Points vTextures_;
};
}  // namespace s21

#endif  // SRC_MODEL_SURFACE_H_

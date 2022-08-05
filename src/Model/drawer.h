#ifndef SRC_MODEL_DRAWER_H_
#define SRC_MODEL_DRAWER_H_

// #include <GL/gl.h>

#include <QColor>
#include <QDebug>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

#include "../object_settings.h"
#include "../point.h"

constexpr float RGB_MIN = 1.0f;
constexpr float RGB_MAX = 255.0f;

namespace s21 {

class Drawer : public QOpenGLWidget, public QOpenGLFunctions {
    Q_OBJECT

 public:
    explicit Drawer(QWidget* parent = nullptr);
    ~Drawer() = default;
    void SetVertices(std::vector<Point>&& vertices) noexcept;
    void SetIndices(std::vector<std::vector<int>>&& indices) noexcept;
    void SetSettings(const ObjectSettings& settings);
    void UpdateScreen();

 protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

 private:
    QMatrix4x4 View;
    QMatrix4x4 Projection;
    QVector2D mousePressPosition;
    bool dragged = false;
    bool perspective = false;
    float colorVertex[3] = {1.0, 0.0, 0.0};
    float colorEdges[3] = {0.0, 1.0, 0.0};

    ObjectSettings settings_;

    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    int CountDigits(float n);
    void SetPerspective(float w, float h);

    void ReadShaderFromFile(GLuint* shaderId, const char* pathToShader);
    void CreateProgramWithShaders(GLuint vertexShaderId, GLuint fragmentShaderId);
    void CreateBuffer(GLuint* bufferID);
    void ConnectVectorWithBuffer(std::vector<Point> vertices, GLuint attribute);
    void DrawModel();
    void UpdateSettings();
    QMatrix4x4 CreateMVPMatrix();
    void SetColor();

    std::vector<Point> vertices_;
    std::vector<Point> normals_;
    std::vector<Point> texture_;

    std::vector<std::vector<int>> indices_;
    std::vector<std::vector<int>> indicesTex_;
    std::vector<std::vector<int>> indicesNorm_;

    GLint color_location;
    GLint attributeCoord3d, attributeNormals, attributeTex;
    GLuint program;
    GLuint vertexBufferObject, normalBufferObject, textureBufferObject;
    GLuint MatrixID;
    GLuint texID;
    GLuint image;
    GLuint tex;

 signals:
    void wheelResize(float value);
    void mouseMove(QVector3D vec);
};
}  // namespace s21

#endif  // SRC_MODEL_DRAWER_H_

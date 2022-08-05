#ifndef SRC_ENUMS_H_
#define SRC_ENUMS_H_
namespace s21 {

enum class ViewAction { ReadFile, SaveSettings };

enum class ObjectAction {
    Move,
    Rotate,
    Scale,
    ChangeEdgeColor,
    ChangeEdgeSize,
    ChangeEdgeType,
    ChangeVertexColor,
    ChangeVertexSize,
    ChangeVertexType
};

enum class SceneAction { Move, Rotate, Scale };

enum class CommandAction {
    OpenFile,
    SaveImage,
    RecordGif,
    CloseFile,
    ChangeSettings,
    LoadSettings,
    Transform
};

enum class Data {
    Vertex,
    VertexNormal,
    VertexTexture,
    SurfaceVertex,
    SurfaceVertexTexture,
    SurfaceVertexNormal
};

}  // namespace s21

#endif  // SRC_ENUMS_H_

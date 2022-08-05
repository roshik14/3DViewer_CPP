#ifndef SRC_OBJECT_SETTINGS_H_
#define SRC_OBJECT_SETTINGS_H_

namespace s21 {
struct ObjectSettings {
    QColor backgroundColor;
    QColor edgeColor;
    QColor vertexColor;
    int projectionType;
    int lineType;
    int vertexType;
    int edgeSize;
    int vertexSize;
};
}  // namespace s21

#endif  // SRC_OBJECT_SETTINGS_H_

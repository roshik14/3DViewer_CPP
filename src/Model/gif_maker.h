#ifndef SRC_MODEL_GIF_MAKER_H_
#define SRC_MODEL_GIF_MAKER_H_

#include <memory>
#include <QSize>
#include <QImage>
#include <vector>
#include "../3rdparty/QtGifImageLib/gifimage/qgifimage.h"

namespace s21 { class GifMaker; }

class s21::GifMaker final {
 public:
    GifMaker();
    void StartRecord(const QSize &size);
    void AddFrame(const QImage &image);
    void SaveGif(const QString &fileName);
 private:
    enum class GifStatus {
        kRecordStarted,
        kRecordStoped,
    };
    GifStatus recordGifStatus_;
    std::unique_ptr<QGifImage> gif_;
    std::vector<QImage> images_;
};

#endif  // SRC_MODEL_GIF_MAKER_H_

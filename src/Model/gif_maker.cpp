#include "gif_maker.h"

using s21::GifMaker;

GifMaker::GifMaker() : recordGifStatus_(GifStatus::kRecordStoped) {}

void GifMaker::StartRecord(const QSize &image_size) {
    gif_ = std::make_unique<QGifImage>(image_size);
    static const int delay = 100;
    gif_->setDefaultDelay(delay);
    recordGifStatus_ = GifStatus::kRecordStarted;
}

void GifMaker::AddFrame(const QImage &image) {
    if (recordGifStatus_ == GifStatus::kRecordStarted) {
        images_.push_back(std::move(image));
    }
}

void GifMaker::SaveGif(const QString &fileName) {
    for (size_t i = 0; i < images_.size(); ++i) {
        gif_->addFrame(images_[i]);
    }
    gif_->save(fileName);
    recordGifStatus_ = GifStatus::kRecordStoped;
    images_.clear();
}
